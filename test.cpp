#include <iostream>
#include <sstream>
#include <string>

// Trik: ubah fungsi main() mahasiswa menjadi student_main agar tidak konflik
#define main student_main
#if __has_include("modul4_playlist.cpp")
    #include "modul4_playlist.cpp"
#else
    #include "main.cpp" // antisipasi jika filenya bernama main.cpp
#endif
#undef main

int totalPassed = 0;
int totalFailed = 0;

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

void jalankan13Skenario() {
    std::cout << "============================================================\n";
    std::cout << "       PENGUJIAN CIRCULAR DOUBLY LINKED LIST PLAYLIST       \n";
    std::cout << "============================================================\n\n";

    Node* head = nullptr;
    Node* tail = nullptr;

    // Skenario 1: Tampilkan Circular kosong
    {
        std::stringstream ss;
        std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
        tampilMaju(head);
        std::cout.rdbuf(old);
        bool s1 = (head == nullptr && tail == nullptr);
        uji(1, "Tampilkan Circular kosong", s1);
    }

    // Skenario 2: Tambah lagu pertama
    tambahAkhir(head, tail, {"Bohemian Rhapsody", "Queen"});
    bool s2 = (head != nullptr && tail != nullptr && head == tail);
    uji(2, "Tambah lagu pertama", s2);

    // Skenario 3: Circular satu node
    // Pada circular 1 node: next dan prev harus menunjuk ke dirinya sendiri
    bool s3 = (head != nullptr && tail != nullptr && 
               head->next == head && head->prev == head &&
               tail->next == tail && tail->prev == tail);
    uji(3, "Circular satu node", s3);

    // Skenario 4: Circular beberapa node
    tambahAkhir(head, tail, {"Imagine", "John Lennon"});
    tambahAkhir(head, tail, {"Hotel California", "Eagles"});
    // tail->next harus kembali ke head, dan head->prev harus menunjuk ke tail
    bool s4 = (head != nullptr && tail != nullptr && 
               tail->next == head && head->prev == tail);
    uji(4, "Circular beberapa node", s4);

    // Skenario 5: Tampilkan maju
    // Urutan: Bohemian Rhapsody -> Imagine -> Hotel California
    bool s5 = (head != nullptr && head->data.judul == "Bohemian Rhapsody" &&
               head->next != nullptr && head->next->data.judul == "Imagine" &&
               head->next->next == tail && tail->data.judul == "Hotel California");
    uji(5, "Tampilkan maju", s5);

    // Skenario 6: Tampilkan mundur
    // Urutan mundur: Hotel California -> Imagine -> Bohemian Rhapsody
    bool s6 = (tail != nullptr && tail->data.judul == "Hotel California" &&
               tail->prev != nullptr && tail->prev->data.judul == "Imagine" &&
               tail->prev->prev == head && head->data.judul == "Bohemian Rhapsody");
    uji(6, "Tampilkan mundur", s6);

    // Skenario 7: Hapus lagu pertama
    // Hapus head ("Bohemian Rhapsody"), head baru -> "Imagine", circular terjaga
    hapusJudul(head, tail, "Bohemian Rhapsody");
    bool s7 = (head != nullptr && tail != nullptr &&
               head->data.judul == "Imagine" &&
               head->prev == tail && tail->next == head);
    uji(7, "Hapus lagu pertama", s7);

    // Skenario 8: Hapus lagu tengah
    // Tambah Yesterday -> list: Imagine <-> Hotel California <-> Yesterday
    tambahAkhir(head, tail, {"Yesterday", "The Beatles"});
    hapusJudul(head, tail, "Hotel California"); // Hapus node tengah
    bool s8 = (head != nullptr && tail != nullptr &&
               head->data.judul == "Imagine" && tail->data.judul == "Yesterday" &&
               head->next == tail && tail->prev == head &&
               tail->next == head && head->prev == tail);
    uji(8, "Hapus lagu tengah", s8);

    // Skenario 9: Hapus lagu terakhir
    // Hapus tail ("Yesterday"), tail baru -> "Imagine"
    hapusJudul(head, tail, "Yesterday");
    bool s9 = (head != nullptr && tail != nullptr && head == tail &&
               head->data.judul == "Imagine" &&
               head->next == head && head->prev == head);
    uji(9, "Hapus lagu terakhir", s9);

    // Skenario 10: Hapus satu-satunya lagu
    // Hapus lagu terakhir yang tersisa ("Imagine"), list harus kembali kosong
    hapusJudul(head, tail, "Imagine");
    bool s10 = (head == nullptr && tail == nullptr);
    uji(10, "Hapus satu-satunya lagu", s10);

    // Skenario 11: Hapus judul tidak tersedia
    tambahAkhir(head, tail, {"Lagu Tetap", "Artis"});
    hapusJudul(head, tail, "Judul Ngawur");
    bool s11 = (head != nullptr && tail != nullptr && 
                head->data.judul == "Lagu Tetap" && head == tail &&
                head->next == head && head->prev == head);
    uji(11, "Hapus judul tidak tersedia", s11);

    // Skenario 12: Traversal circular
    // Tambah lagu lagi, lalu traversal 1 siklus penuh, pastikan tepat jumlahnya dan tidak infinite loop
    tambahAkhir(head, tail, {"Lagu Dua", "Artis"});
    tambahAkhir(head, tail, {"Lagu Tiga", "Artis"});
    int hitungNode = 0;
    Node* current = head;
    if (current != nullptr) {
        do {
            hitungNode++;
            current = current->next;
        } while (current != nullptr && current != head && hitungNode <= 10);
    }
    bool s12 = (hitungNode == 3 && current == head);
    uji(12, "Traversal circular", s12);

    // Skenario 13: clear playlist
    clear(head, tail);
    bool s13 = (head == nullptr && tail == nullptr);
    uji(13, "clear playlist", s13);

    // ===========================================================
    // RINGKASAN HASIL
    // ===========================================================
    std::cout << "\n============================================================\n";
    std::cout << " TOTAL LOLOS (PASS) : " << totalPassed << " / 13\n";
    std::cout << " TOTAL GAGAL (FAIL) : " << totalFailed << " / 13\n";
    std::cout << "============================================================\n";
}

int main() {
    jalankan13Skenario();
    if (totalFailed > 0) {
        return 1;
    }
    return 0;
}