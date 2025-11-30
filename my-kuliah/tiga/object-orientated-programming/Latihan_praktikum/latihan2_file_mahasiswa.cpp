/*	Nama	: Haidar Khadafi
	NIM		: 24040700033
	Latihan 2: Pembaca File Mahasiswa dengan Exception Handling	*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <iomanip>

using namespace std;

// Exception untuk file tidak ditemukan
class FileNotFoundException : public exception {
private:
    string message;
    string namaFile;

public:
    FileNotFoundException(const string& filename) : namaFile(filename) {
        message = "Error: File '" + namaFile + "' tidak ditemukan!";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

    string getNamaFile() const {
        return namaFile;
    }
};

// Struct untuk data mahasiswa
struct Mahasiswa {
    string nim;
    string nama;
    string jurusan;
    double ipk;

    void tampilkan() const {
        cout << "NIM     : " << nim << endl;
        cout << "Nama    : " << nama << endl;
        cout << "Jurusan : " << jurusan << endl;
        cout << "IPK     : " << fixed << setprecision(2) << ipk << endl;
    }
};

// Class untuk membaca file mahasiswa
class PembacaFileMahasiswa {
private:
    vector<Mahasiswa> daftarMahasiswa;
    string namaFile;

public:
    PembacaFileMahasiswa(const string& filename) : namaFile(filename) {}

    // Baca file mahasiswa
    void bacaFile() {
        ifstream file(namaFile);

        if (!file.is_open()) {
            throw FileNotFoundException(namaFile);
        }

        daftarMahasiswa.clear();
        string line;

        // Skip header jika ada
        getline(file, line);

        while (getline(file, line)) {
            if (line.empty()) continue;

            Mahasiswa mhs;
            size_t pos = 0;
            
            // Parse NIM
            pos = line.find(',');
            mhs.nim = line.substr(0, pos);
            line = line.substr(pos + 1);

            // Parse Nama
            pos = line.find(',');
            mhs.nama = line.substr(0, pos);
            line = line.substr(pos + 1);

            // Parse Jurusan
            pos = line.find(',');
            mhs.jurusan = line.substr(0, pos);
            line = line.substr(pos + 1);

            // Parse IPK
            mhs.ipk = stod(line);

            daftarMahasiswa.push_back(mhs);
        }

        file.close();
        cout << "File berhasil dibaca! Total " << daftarMahasiswa.size() 
             << " mahasiswa.\n";
    }

    // Tambah mahasiswa manual
    void tambahMahasiswa() {
        Mahasiswa mhs;
        
        cout << "\n--- TAMBAH DATA MAHASISWA ---\n";
        cout << "NIM: ";
        cin >> mhs.nim;
        cin.ignore();
        
        cout << "Nama: ";
        getline(cin, mhs.nama);
        
        cout << "Jurusan: ";
        getline(cin, mhs.jurusan);
        
        cout << "IPK: ";
        cin >> mhs.ipk;

        daftarMahasiswa.push_back(mhs);
        cout << "Data mahasiswa berhasil ditambahkan!\n";
    }

    // Simpan ke file
    void simpanKeFile() {
        ofstream file(namaFile);
        
        if (!file.is_open()) {
            cout << "Gagal menyimpan file.\n";
            return;
        }

        file << "NIM,Nama,Jurusan,IPK\n";
        for (const auto& mhs : daftarMahasiswa) {
            file << mhs.nim << "," << mhs.nama << "," 
                 << mhs.jurusan << "," << fixed << setprecision(2) << mhs.ipk << "\n";
        }

        file.close();
        cout << "Data berhasil disimpan ke file '" << namaFile << "'!\n";
    }

    // Tampilkan semua mahasiswa
    void tampilkanSemuaMahasiswa() const {
        if (daftarMahasiswa.empty()) {
            cout << "Tidak ada data mahasiswa.\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "       DAFTAR MAHASISWA\n";
        cout << "========================================\n";

        for (size_t i = 0; i < daftarMahasiswa.size(); i++) {
            cout << "\nMahasiswa #" << (i + 1) << "\n";
            cout << "----------------------------------------\n";
            daftarMahasiswa[i].tampilkan();
        }
        cout << "========================================\n";
    }

    // Cari mahasiswa berdasarkan NIM
    void cariMahasiswa(const string& nim) const {
        for (const auto& mhs : daftarMahasiswa) {
            if (mhs.nim == nim) {
                cout << "\nMahasiswa ditemukan:\n";
                cout << "----------------------------------------\n";
                mhs.tampilkan();
                return;
            }
        }
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
};

int main() {
    string namaFile = "mahasiswa.txt";
    PembacaFileMahasiswa pembaca(namaFile);
    int pilihan;

    cout << "========================================\n";
    cout << "   PROGRAM PEMBACA FILE MAHASISWA\n";
    cout << "========================================\n\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Baca File Mahasiswa\n";
        cout << "2. Tambah Data Mahasiswa\n";
        cout << "3. Tampilkan Semua Mahasiswa\n";
        cout << "4. Cari Mahasiswa (berdasarkan NIM)\n";
        cout << "5. Simpan ke File\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        try {
            switch (pilihan) {
                case 1: {
                    pembaca.bacaFile();
                    break;
                }
                case 2: {
                    pembaca.tambahMahasiswa();
                    break;
                }
                case 3: {
                    pembaca.tampilkanSemuaMahasiswa();
                    break;
                }
                case 4: {
                    string nim;
                    cout << "Masukkan NIM: ";
                    cin >> nim;
                    pembaca.cariMahasiswa(nim);
                    break;
                }
                case 5: {
                    pembaca.simpanKeFile();
                    break;
                }
                case 0: {
                    cout << "\nTerima kasih!\n";
                    break;
                }
                default: {
                    cout << "Pilihan tidak valid!\n";
                }
            }
        }
        catch (const FileNotFoundException& e) {
            cout << "\n[EXCEPTION] " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "\n[ERROR] " << e.what() << endl;
        }
    } while (pilihan != 0);

    return 0;
}
