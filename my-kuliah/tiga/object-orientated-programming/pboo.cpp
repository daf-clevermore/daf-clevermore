#include <stdio.h>
#include <string.h>

using namespace std; 
class Buku { 
    private: 
    int id; 
    string judul; 
    string penulis; 
    bool dipinjam; 
    public: 
    Buku(int id, string judul, string penulis) { 
        this->id = id; 
        this->judul = judul; 
        this->penulis = penulis; 
        this->dipinjam = false; 
    } 
    
    void tampilkanInfo() { 
        cout << id << " - " << judul << " oleh " << penulis << (dipinjam ? " [Dipinjam]" : " [Tersedia]") << endl; 
    } 
    void pinjam() { 
        if (!dipinjam) { 
            dipinjam = true; cout << "Buku \"" << judul << "\" berhasil dipinjam.\n"; 
        } else { 
            cout << "Buku \"" << judul << "\" sedang dipinjam.\n"; 
        } 
    } 
}; 

int main() { 
    Buku b1(1, "Belajar C++", "Bjarne Stroustrup"); 
    Buku b2(2, "Pemrograman OOP", "Grady Booch"); 
    Buku b3(3, "Algoritma", "Donald Knuth"); 
    b1.tampilkanInfo(); 
    b2.tampilkanInfo(); 
    b3.tampilkanInfo(); 
    b2.pinjam(); 
    b1.tampilkanInfo(); 
    b2.tampilkanInfo(); 
    b3.tampilkanInfo(); 
    return 0; 
}