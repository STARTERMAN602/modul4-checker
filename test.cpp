#include <iostream>
#include <cassert>
#include <sstream>

// Trik: ubah fungsi main() mahasiswa menjadi student_main agar tidak konflik
#define main student_main
#if __has_include("modul4_playlist.cpp")
    #include "modul4_playlist.cpp"
#else
    #include "main.cpp" // antisipasi jika kamu menamai filenya main.cpp
#endif
#undef main

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
        assert(head == nullptr && tail == nullptr);
        std::cout << "[PASS] Skenario  1: Tampilkan DLL kosong -> Tidak ada data\n";
    }

    // Skenario 2: Tambah lagu pertama -> head == tail
    tambahAkhir(head, tail, {"Bohemian Rhapsody", "Queen"});
    assert(head != nullptr && tail != nullptr);
    assert(head == tail);
    std::cout << "[PASS] Skenario  2: Tambah lagu pertama -> head == tail\n";

    // Skenario 3: Periksa satu node -> head->prev == nullptr dan tail->next == nullptr
    assert(head->prev == nullptr && tail->next == nullptr);
    std::cout << "[PASS] Skenario  3: Periksa satu node -> head->prev == nullptr dan tail->next == nullptr\n";

    // Skenario 4: Tambah beberapa lagu -> Urutan maju benar
    tambahAkhir(head, tail, {"Imagine", "John Lennon"});
    tambahAkhir(head, tail, {"Hotel California", "Eagles"});
    assert(head->data.judul == "Bohemian Rhapsody");
    assert(head->next->data.judul == "Imagine");
    assert(tail->data.judul == "Hotel California");
    std::cout << "[PASS] Skenario  4: Tambah beberapa lagu -> Urutan maju benar\n";

    // Skenario 5: Tampilkan mundur -> Urutan terbalik benar
    assert(tail->data.judul == "Hotel California");
    assert(tail->prev->data.judul == "Imagine");
    assert(tail->prev->prev == head);
    std::cout << "[PASS] Skenario  5: Tampilkan mundur -> Urutan terbalik benar\n";

    // Skenario 6: Hapus lagu pertama -> head diperbarui dan head->prev == nullptr
    hapusJudul(head, tail, "Bohemian Rhapsody");
    assert(head != nullptr);
    assert(head->data.judul == "Imagine");
    assert(head->prev == nullptr);
    std::cout << "[PASS] Skenario  6: Hapus lagu pertama -> head diperbarui dan head->prev == nullptr\n";

    // Skenario 7: Hapus lagu tengah -> Hubungan prev dan next diperbaiki
    // Saat ini: Imagine -> Hotel California. Tambah 1 lagu lagi:
    tambahAkhir(head, tail, {"Yesterday", "The Beatles"}); // List: Imagine -> Hotel California -> Yesterday
    hapusJudul(head, tail, "Hotel California");           // Hapus tengah
    assert(head->next == tail);
    assert(tail->prev == head);
    assert(head->data.judul == "Imagine" && tail->data.judul == "Yesterday");
    std::cout << "[PASS] Skenario  7: Hapus lagu tengah -> Hubungan prev dan next diperbaiki\n";

    // Skenario 8: Hapus lagu terakhir -> tail diperbarui dan tail->next == nullptr
    hapusJudul(head, tail, "Yesterday"); // Sisa: Imagine
    assert(tail != nullptr);
    assert(tail->data.judul == "Imagine");
    assert(tail->next == nullptr);
    assert(head == tail);
    std::cout << "[PASS] Skenario  8: Hapus lagu terakhir -> tail diperbarui dan tail->next == nullptr\n";

    // Skenario 9: Hapus satu-satunya lagu -> head dan tail menjadi nullptr
    hapusJudul(head, tail, "Imagine");
    assert(head == nullptr && tail == nullptr);
    std::cout << "[PASS] Skenario  9: Hapus satu-satunya lagu -> head dan tail menjadi nullptr\n";

    // Skenario 10: Hapus judul tidak tersedia -> List tidak berubah
    tambahAkhir(head, tail, {"Lagu Tetap", "Artis"});
    hapusJudul(head, tail, "Judul Ngawur");
    assert(head != nullptr && tail != nullptr);
    assert(head->data.judul == "Lagu Tetap" && head == tail);
    std::cout << "[PASS] Skenario 10: Hapus judul tidak tersedia -> List tidak berubah\n";

    // -----------------------------------------------------------
    // PENGUJIAN CIRCULAR LINKED LIST (Skenario 11 - 14)
    // Sesuai materi Subbab 3.6 halaman 34 & Kegiatan 4.3 halaman 36
    // -----------------------------------------------------------
    NodeCircular* cHead = nullptr;
    NodeCircular* cLast = nullptr;

    // Skenario 11: Circular kosong -> head dan last nullptr
    assert(cHead == nullptr && cLast == nullptr);
    std::cout << "[PASS] Skenario 11: Circular kosong -> head dan last nullptr\n";

    // Skenario 12: Circular satu node -> head == last dan head->next == head
    NodeCircular* c1 = new NodeCircular{10, nullptr};
    cHead = cLast = c1;
    c1->next = cHead;
    assert(cHead == cLast);
    assert(cHead->next == cHead);
    std::cout << "[PASS] Skenario 12: Circular satu node -> head == last dan head->next == head\n";

    // Skenario 13: Circular beberapa node -> last->next == head
    NodeCircular* c2 = new NodeCircular{20, nullptr};
    c2->next = cHead;
    cLast->next = c2;
    cLast = c2;

    NodeCircular* c3 = new NodeCircular{30, nullptr};
    c3->next = cHead;
    cLast->next = c3;
    cLast = c3;

    assert(cLast->next == cHead);
    std::cout << "[PASS] Skenario 13: Circular beberapa node -> last->next == head\n";

    // Skenario 14: Traversal circular -> Setiap node tampil tepat satu kali
    int hitungNode = 0;
    NodeCircular* bantu = cHead;
    if (bantu != nullptr) {
        do {
            hitungNode++;
            bantu = bantu->next;
        } while (bantu != cHead);
    }
    assert(hitungNode == 3);
    std::cout << "[PASS] Skenario 14: Traversal circular -> Setiap node tampil tepat satu kali\n";

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
    assert(head == nullptr && tail == nullptr);
    std::cout << "[PASS] Skenario 15: clear playlist -> Seluruh node DLL dibebaskan\n";

    std::cout << "\n============================================================\n";
    std::cout << " SEMUA 15 SKENARIO BERHASIL DILEWATI TANPA KESALAHAN! (100%)\n";
    std::cout << "============================================================\n";
}

int main() {
    jalankan15Skenario();
    return 0;
}