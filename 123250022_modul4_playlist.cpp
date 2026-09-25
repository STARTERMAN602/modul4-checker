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
    if (head == nullptr) {
        return false;
    }
    const Node* current = head;
    do {
        if (current->data.judul == judul) {
            return true;
        }
        current = current->next;
    } while (current != head);
    return false;
}

bool tambahAkhir(Node*& head, Node*& tail, const Lagu& data) {
    if (judulTersedia(head, data.judul)) {
        return false;
    }
    Node* newNode = new Node{data, nullptr, nullptr};
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        head->next = head;
        head->prev = head;
        return true;
    }
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;

    tail = newNode;
    return true;
}

Node* cariJudul(Node* head, const std::string& judul) {
    if (head == nullptr) {
        return nullptr;
    }
    Node* current = head;
    do {
        if (current->data.judul == judul) {
            return current;
        }
        current = current-> next;
    } while (current != head);
    return nullptr;
}

bool hapusJudul(Node*& head, Node*& tail, const std::string& judul) {
    Node* target = cariJudul(head, judul);
    if (target == nullptr) {
        return false;
    }
    if (head == tail) {
        delete target;
        head = nullptr;
        tail = nullptr;
        return true;
    }
    target->prev->next = target->next;
    target->next->prev = target->prev;

    if (target == head) {
        head = target->next;
    }
    if (target == tail) {
        tail = target->prev;
    }
    delete target;
    return true;
}

void tampilMaju(const Node* head) {
    if (head == nullptr) {
        std::cout << "Playlist is empty!\n";
        return;
    }
    const Node* current = head;
    int no = 1;

    do {
        std::cout << no++ << ". " << current->data.judul 
                  << " - " << current->data.penyanyi << "\n";
        current = current->next;
    } while (current != head);
}

void tampilMundur(const Node* tail) {
    if (tail == nullptr) {
        std::cout << "Playlist is empty!\n";
        return;
    }
    const Node* current = tail;
    int no = 1;

    do {
        std::cout << no++ << ". " << current->data.judul 
                  << " - " << current->data.penyanyi << "\n";
        current = current->prev;
    } while (current != tail);
}

int jumlahData(const Node* head) {
    if (head == nullptr) {
        return 0;
    }
    int count = 0;
    const Node* current = head;

    do {
        count++;
        current = current->next;
    } while (current != head);
    return count;
}

void clear(Node*& head, Node*& tail) {
    if (head == nullptr) {
        return;
    }
    tail->next = nullptr;
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
    head = nullptr;
    tail = nullptr;
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int pilihan;

    do {
        std::cout << "\n=========================\n";
        std::cout << "   MENU PLAYLIST MUSIK   \n";
        std::cout << "=========================\n";
        std::cout << "1. Tambah lagu\n";
        std::cout << "2. Tampilkan maju\n";
        std::cout << "3. Tampilkan mundur\n";
        std::cout << "4. Cari lagu\n";
        std::cout << "5. Hapus lagu\n";
        std::cout << "6. Jumlah lagu\n";
        std::cout << "7. Keluar\n";
        std::cout << "Pilihan: ";

        if (!(std::cin >> pilihan)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Input number 1 - 7.\n";
            continue;
        }
        std::cin.ignore();
        // panggil fungsi sesuai pilihan
        switch (pilihan) {
            case 1: {
                std::string judul, penyanyi;
                std::cout << "Masukkan judul lagu   : ";
                std::getline(std::cin, judul);
                std::cout << "Masukkan nama penyanyi: ";
                std::getline(std::cin, penyanyi);

                if (tambahAkhir(head, tail, {judul, penyanyi})) {
                    std::cout << "-> Lagu \"" << judul << "\" berhasil ditambahkan!\n";
                } else {
                    std::cout << "-> Gagal! Lagu dengan judul \"" << judul << "\" sudah ada di playlist.\n"; 
                }
                break;
            }

            case 2: 
                std::cout << "\n--- DAFTAR LAGU (MAJU) ---\n";
                tampilMaju(head);
                break;

            case 3:
                std::cout << "\n--- DAFTAR LAGU (MUNDUR) ---\n";
                tampilMundur(tail);
                break;

            case 4: {
                std::string judul;
                std::cout << "Masukkan judul lagu yang dicari: ";
                std::getline(std::cin, judul);
                Node* hasil = cariJudul(head, judul);
                if (hasil != nullptr) {
                    std::cout << "-> Lagu Ditemukan!\n";
                    std::cout << "   Judul   : " << hasil->data.judul << "\n";
                    std::cout << "   Penyanyi: " << hasil->data.penyanyi << "\n";
                } else {
                    std::cout << "-> Lagu \"" << judul << "\" tidak ditemukan.\n";
                }
                break;
            }

            case 5: {
                std::string judul;
                std::cout << "Masukkan judul lagu yang ingin dihapus: ";
                std::getline(std::cin, judul);

                if (hapusJudul(head, tail, judul)) {
                    std::cout << "-> Lagu \"" << judul << "\" berhasil dihapus!\n";
                } else {
                    std::cout << "-> Gagal! Lagiu \"" << judul << "\" tidak ditemukan.\n";
                }
                break;
            }

            case 6:
                std::cout << "-> Total lagu di playlist: " << jumlahData(head) << " lagu.\n";
                break;

                case 7:
                    std::cout << "keluar dari program. Membersihkan playlist...\n";
                    break;

                default: 
                    std::cout << "Pilihan tidak valid! Silahkan pilih menu 1 - 7.\n";
                    break;
        }

    } while (pilihan != 7);

    clear(head, tail);
    return 0;
}