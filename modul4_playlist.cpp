#include <iostream>
#include <string>

struct Lagu {
    std::string judul;
    std::string penyanyi;
};

struct Node {
    Lagu data;
    Node* prev;
    Node* next;
};

bool judulTersedia(const Node* head, const std::string& judul) {
    return false;
}

bool tambahAkhir(Node*& head, Node*& tail, const Lagu& data) {
    return false;
}

Node* cariJudul(Node* head, const std::string& judul) {
    return nullptr;
}

bool hapusJudul(Node*& head, Node*& tail, const std::string& judul) {
    return false;
}

void tampilMaju(const Node* head) {

}

void tampilMundur(const Node* tail) {

}

int jumlahData(const Node* head) {
    return -1;
}

void clear(Node*& head, Node*& tail) {

}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int pilihan;

    do {
        std::cout << "\n1. Tambah lagu\n";
        std::cout << "2. Tampilkan maju\n";
        std::cout << "3. Tampilkan mundur\n";
        std::cout << "4. Cari lagu\n";
        std::cout << "5. Hapus lagu\n";
        std::cout << "6. Jumlah lagu\n";
        std::cout << "7. Keluar\n";
        std::cout << "Pilihan: ";
        std::cin >> pilihan;

        // panggil fungsi sesuai pilihan

    } while (pilihan != 7);

    clear(head, tail);
    return 0;
}