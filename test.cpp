#include <iostream>
#include <sstream>
#include <string>

// Trik: ubah fungsi main() mahasiswa menjadi student_main agar tidak konflik
#define main student_main
#if __has_include("modul4_playlist.cpp")
    #include "modul4_playlist.cpp"
#else
    #include "main.cpp" // antisipasi jika kamu menamai filenya main.cpp
#endif
#undef main

// Variabel penghitung skor
int totalPassed = 0;
int totalFailed = 0;

// Fungsi helper untuk mencetak PASS atau FAIL tanpa menghentikan program
void uji(int no, const std::string& namaSkenario, bool kondisi) {
    std::cout << (kondisi ? "[PASS] " : "[FAIL] ")
              << "Skenario " << (no < 10 ? " " : "") << no << ": "
              << namaSkenario << "\n";
    if (kondisi) {
        totalPassed++;
    } else {
        totalFailed++;
    }
}

// ===============================================================
// STRUKTUR & FUNGSI CIRCULAR SESUAI SUBBAB 3.5 & 3.6 (Halaman 34-35)
// ===============================================================
struct NodeCircular {
    int data;
    NodeCircular* next;
};

void tampilCircular(const NodeCircular* head) {
    if (head == nullptr) return;
    const NodeCircular* bantu = head;
    do {
        std::cout << bantu->data << ' ';
        bantu = bantu->next;
    } while (bantu != head);
    std::cout << '\n';
}

// ===============================================================
// PENGUJIAN 15 SKENARIO (Halaman 37 - 38)
// ===============================================================
void jalankan15Skenario() {
    std::cout << "============================================================\n";
    std::cout << "        PENGUJIAN MODUL 4: DOUBLY & CIRCULAR LINKED LIST    \n";
    std::cout << "============================================================\n\n";

    // -----------------------------------------------------------
    // PENGUJIAN DOUBLY LINKED LIST (Skenario 1 - 10)
    // -----------------------------------------------------------
    Node* head = nullptr;
    Node* tail = nullptr;

    // Skenario 1: Tampilkan DLL kosong -> Tidak ada data
    {
        std::stringstream ss;
        std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
        tampilMaju(head);
        std::cout.rdbuf(old);
        bool s1 = (head == nullptr && tail == nullptr);
        uji(1, "Tampilkan DLL kosong -> Tidak ada data", s1);
    }

    // Skenario 2: Tambah lagu pertama -> head == tail
    tambahAkhir(head, tail, {"Bohemian Rhapsody", "Queen"});
    bool s2 = (head != nullptr && tail != nullptr && head == tail);
    uji(2, "Tambah lagu pertama -> head == tail", s2);

    // Skenario 3: Periksa satu node -> head->prev == nullptr dan tail->next == nullptr
    bool s3 = (head != nullptr && tail != nullptr && head->prev == nullptr && tail->next == nullptr);
    uji(3, "Periksa satu node -> head->prev == nullptr dan tail->next == nullptr", s3);

    // Skenario 4: Tambah beberapa lagu -> Urutan maju benar
    tambahAkhir(head, tail, {"Imagine", "John Lennon"});
    tambahAkhir(head, tail, {"Hotel California", "Eagles"});
    bool s4 = (head != nullptr && head->data.judul == "Bohemian Rhapsody" &&
               head->next != nullptr && head->next->data.judul == "Imagine" &&
               tail != nullptr && tail->data.judul == "Hotel California");
    uji(4, "Tambah beberapa lagu -> Urutan maju benar", s4);

    // Skenario 5: Tampilkan mundur -> Urutan terbalik benar
    bool s5 = (tail != nullptr && tail->data.judul == "Hotel California" &&
               tail->prev != nullptr && tail->prev->data.judul == "Imagine" &&
               tail->prev->prev == head);
    uji(5, "Tampilkan mundur -> Urutan terbalik benar", s5);

    // Skenario 6: Hapus lagu pertama -> head diperbarui dan head->prev == nullptr
    hapusJudul(head, tail, "Bohemian Rhapsody");
    bool s6 = (head != nullptr && head->data.judul == "Imagine" && head->prev == nullptr);
    uji(6, "Hapus lagu pertama -> head diperbarui dan head->prev == nullptr", s6);

    // Skenario 7: Hapus lagu tengah -> Hubungan prev dan next diperbaiki
    tambahAkhir(head, tail, {"Yesterday", "The Beatles"}); // List: Imagine -> Hotel California -> Yesterday
    hapusJudul(head, tail, "Hotel California");           // Hapus tengah
    bool s7 = (head != nullptr && tail != nullptr && 
               head->next == tail && tail->prev == head &&
               head->data.judul == "Imagine" && tail->data.judul == "Yesterday");
    uji(7, "Hapus lagu tengah -> Hubungan prev dan next diperbaiki", s7);

    // Skenario 8: Hapus lagu terakhir -> tail diperbarui dan tail->next == nullptr
    hapusJudul(head, tail, "Yesterday"); // Sisa: Imagine
    bool s8 = (tail != nullptr && tail->data.judul == "Imagine" && tail->next == nullptr && head == tail);
    uji(8, "Hapus lagu terakhir -> tail diperbarui dan tail->next == nullptr", s8);

    // Skenario 9: Hapus satu-satunya lagu -> head dan tail menjadi nullptr
    hapusJudul(head, tail, "Imagine");
    bool s9 = (head == nullptr && tail == nullptr);
    uji(9, "Hapus satu-satunya lagu -> head dan tail menjadi nullptr", s9);

    // Skenario 10: Hapus judul tidak tersedia -> List tidak berubah
    tambahAkhir(head, tail, {"Lagu Tetap", "Artis"});
    hapusJudul(head, tail, "Judul Ngawur");
    bool s10 = (head != nullptr && tail != nullptr && head->data.judul == "Lagu Tetap" && head == tail);
    uji(10, "Hapus judul tidak tersedia -> List tidak berubah", s10);

    // -----------------------------------------------------------
    // PENGUJIAN CIRCULAR LINKED LIST (Skenario 11 - 14)
    // -----------------------------------------------------------
    NodeCircular* cHead = nullptr;
    NodeCircular* cLast = nullptr;

    // Skenario 11: Circular kosong -> head dan last nullptr
    bool s11 = (cHead == nullptr && cLast == nullptr);
    uji(11, "Circular kosong -> head dan last nullptr", s11);

    // Skenario 12: Circular satu node -> head == last dan head->next == head
    NodeCircular* c1 = new NodeCircular{10, nullptr};
    cHead = cLast = c1;
    c1->next = cHead;
    bool s12 = (cHead != nullptr && cHead == cLast && cHead->next == cHead);
    uji(12, "Circular satu node -> head == last dan head->next == head", s12);

    // Skenario 13: Circular beberapa node -> last->next == head
    NodeCircular* c2 = new NodeCircular{20, nullptr};
    c2->next = cHead;
    cLast->next = c2;
    cLast = c2;

    NodeCircular* c3 = new NodeCircular{30, nullptr};
    c3->next = cHead;
    cLast->next = c3;
    cLast = c3;

    bool s13 = (cLast != nullptr && cLast->next == cHead);
    uji(13, "Circular beberapa node -> last->next == head", s13);

    // Skenario 14: Traversal circular -> Setiap node tampil tepat satu kali
    int hitungNode = 0;
    NodeCircular* bantu = cHead;
    if (bantu != nullptr) {
        do {
            hitungNode++;
            bantu = bantu->next;
        } while (bantu != nullptr && bantu != cHead && hitungNode <= 10);
    }
    bool s14 = (hitungNode == 3);
    uji(14, "Traversal circular -> Setiap node tampil tepat satu kali", s14);

    // Bersihkan memori circular
    delete c1;
    delete c2;
    delete c3;
    cHead = cLast = nullptr;

    // -----------------------------------------------------------
    // PENGUJIAN CLEAR MEMORY (Skenario 15)
    // -----------------------------------------------------------
    // Skenario 15: clear playlist -> Seluruh node DLL dibebaskan
    clear(head, tail);
    bool s15 = (head == nullptr && tail == nullptr);
    uji(15, "clear playlist -> Seluruh node DLL dibebaskan", s15);

    // ===========================================================
    // RINGKASAN HASIL AKHIR
    // ===========================================================
    std::cout << "\n============================================================\n";
    std::cout << " TOTAL LOLOS (PASS) : " << totalPassed << " / 15\n";
    std::cout << " TOTAL GAGAL (FAIL) : " << totalFailed << " / 15\n";
    std::cout << "============================================================\n";
}

int main() {
    jalankan15Skenario();

    // Jika ada yang gagal, program keluar dengan kode error 1 agar GitHub Action tahu
    if (totalFailed > 0) {
        return 1;
    }
    return 0;
}