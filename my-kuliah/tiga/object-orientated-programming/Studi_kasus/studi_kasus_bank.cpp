/*	Nama	: Haidar Khadafi
	NIM		: 24040700033	*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <ctime>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

// Fungsi helper untuk format rupiah
string formatRupiah(double jumlah) {
    stringstream ss;
    ss << fixed << setprecision(0) << jumlah;
    return ss.str();
}

// EXCEPTION CLASSES

// Exception untuk saldo tidak cukup
class InsufficientBalanceException : public exception {
private:
    string message;
    double saldoTersedia;
    double jumlahDiminta;

public:
    InsufficientBalanceException(double saldo, double jumlah) 
        : saldoTersedia(saldo), jumlahDiminta(jumlah) {
        message = "Saldo tidak cukup! Saldo tersedia: Rp" + 
                  formatRupiah(saldoTersedia) + 
                  ", Jumlah diminta: Rp" + formatRupiah(jumlahDiminta);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getSaldoTersedia() const { return saldoTersedia; }
    double getJumlahDiminta() const { return jumlahDiminta; }
};

// Exception untuk input tidak valid
class InvalidInputException : public exception {
private:
    string message;

public:
    InvalidInputException(const string& msg) {
        message = "Input tidak valid: " + msg;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Exception untuk file transaksi gagal dibaca
class FileReadException : public exception {
private:
    string message;
    string namaFile;

public:
    FileReadException(const string& filename) : namaFile(filename) {
        message = "Gagal membaca file transaksi: " + namaFile;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

    string getNamaFile() const { return namaFile; }
};

// Exception untuk transfer ke akun tak dikenal
class UnknownAccountException : public exception {
private:
    string message;
    string nomorRekening;

public:
    UnknownAccountException(const string& noRek) : nomorRekening(noRek) {
        message = "Akun tidak ditemukan: " + nomorRekening;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

    string getNomorRekening() const { return nomorRekening; }
};

// TRANSACTION STRUCT

struct Transaction {
    string jenisTransaksi;
    double jumlah;
    double saldoSetelahTransaksi;
    string waktu;
    string keterangan;

    Transaction(const string& jenis, double jml, double saldo, 
                const string& ket = "") 
        : jenisTransaksi(jenis), jumlah(jml), 
          saldoSetelahTransaksi(saldo), keterangan(ket) {
        time_t now = time(0);
        char* dt = ctime(&now);
        waktu = string(dt);
        if (!waktu.empty() && waktu[waktu.length()-1] == '\n') {
            waktu.erase(waktu.length()-1);
        }
    }
};

// BANK ACCOUNT CLASS

class BankAccount {
private:
    string nomorRekening;
    string namaPemilik;
    double saldo;
    vector<Transaction> riwayatTransaksi;

    void validasiJumlah(double jumlah) const {
        if (jumlah <= 0) {
            throw InvalidInputException("Jumlah harus lebih besar dari 0");
        }
    }

public:
    BankAccount(const string& noRek, const string& nama, double saldoAwal = 0) 
        : nomorRekening(noRek), namaPemilik(nama), saldo(saldoAwal) {
        if (noRek.empty()) {
            throw InvalidInputException("Nomor rekening tidak boleh kosong");
        }
        if (nama.empty()) {
            throw InvalidInputException("Nama pemilik tidak boleh kosong");
        }
        if (saldoAwal < 0) {
            throw InvalidInputException("Saldo awal tidak boleh negatif");
        }
        
        if (saldoAwal > 0) {
            riwayatTransaksi.push_back(
                Transaction("SALDO_AWAL", saldoAwal, saldo, "Pembukaan rekening")
            );
        }
    }

    string getNomorRekening() const { return nomorRekening; }
    string getNamaPemilik() const { return namaPemilik; }
    double getSaldo() const { return saldo; }
    const vector<Transaction>& getRiwayatTransaksi() const { 
        return riwayatTransaksi; 
    }

    void setorTunai(double jumlah) {
        validasiJumlah(jumlah);
        saldo += jumlah;
        riwayatTransaksi.push_back(
            Transaction("SETOR", jumlah, saldo, "Setor tunai")
        );
    }

    void tarikTunai(double jumlah) {
        validasiJumlah(jumlah);
        if (saldo < jumlah) {
            throw InsufficientBalanceException(saldo, jumlah);
        }
        saldo -= jumlah;
        riwayatTransaksi.push_back(
            Transaction("TARIK", jumlah, saldo, "Tarik tunai")
        );
    }

    void transferKeluar(double jumlah, const string& tujuan) {
        validasiJumlah(jumlah);
        if (saldo < jumlah) {
            throw InsufficientBalanceException(saldo, jumlah);
        }
        saldo -= jumlah;
        riwayatTransaksi.push_back(
            Transaction("TRANSFER_KELUAR", jumlah, saldo, 
                       "Transfer ke " + tujuan)
        );
    }

    void transferMasuk(double jumlah, const string& pengirim) {
        validasiJumlah(jumlah);
        saldo += jumlah;
        riwayatTransaksi.push_back(
            Transaction("TRANSFER_MASUK", jumlah, saldo, 
                       "Transfer dari " + pengirim)
        );
    }

    void tampilkanInfo() const {
        cout << "\n========================================\n";
        cout << "INFORMASI REKENING\n";
        cout << "========================================\n";
        cout << "Nomor Rekening : " << nomorRekening << "\n";
        cout << "Nama Pemilik   : " << namaPemilik << "\n";
        cout << "Saldo          : Rp" << formatRupiah(saldo) << "\n";
        cout << "========================================\n";
    }

    void tampilkanRiwayat() const {
        cout << "\n========================================\n";
        cout << "RIWAYAT TRANSAKSI - " << nomorRekening << "\n";
        cout << "========================================\n";
        
        if (riwayatTransaksi.empty()) {
            cout << "Belum ada transaksi.\n";
        } else {
            for (size_t i = 0; i < riwayatTransaksi.size(); i++) {
                const Transaction& t = riwayatTransaksi[i];
                cout << "\nTransaksi #" << (i + 1) << "\n";
                cout << "Jenis      : " << t.jenisTransaksi << "\n";
                cout << "Jumlah     : Rp" << formatRupiah(t.jumlah) << "\n";
                cout << "Saldo      : Rp" << formatRupiah(t.saldoSetelahTransaksi) << "\n";
                cout << "Waktu      : " << t.waktu << "\n";
                if (!t.keterangan.empty()) {
                    cout << "Keterangan : " << t.keterangan << "\n";
                }
                cout << "----------------------------------------\n";
            }
        }
        cout << "========================================\n";
    }
};

// BANK MANAGER CLASS

class BankManager {
private:
    map<string, shared_ptr<BankAccount>> daftarAkun;
    string namaFileTransaksi;

public:
    BankManager(const string& filename = "transaksi.txt") 
        : namaFileTransaksi(filename) {}

    void tambahAkun(const string& noRek, const string& nama, 
                    double saldoAwal = 0) {
        if (daftarAkun.find(noRek) != daftarAkun.end()) {
            throw InvalidInputException("Nomor rekening sudah terdaftar: " + noRek);
        }
        
        auto akun = make_shared<BankAccount>(noRek, nama, saldoAwal);
        daftarAkun[noRek] = akun;
        cout << "Akun berhasil ditambahkan!\n";
    }

    shared_ptr<BankAccount> cariAkun(const string& noRek) {
        auto it = daftarAkun.find(noRek);
        if (it == daftarAkun.end()) {
            throw UnknownAccountException(noRek);
        }
        return it->second;
    }

    void transferAntarAkun(const string& noRekPengirim, 
                          const string& noRekPenerima, 
                          double jumlah) {
        auto akunPengirim = cariAkun(noRekPengirim);
        auto akunPenerima = cariAkun(noRekPenerima);
        
        akunPengirim->transferKeluar(jumlah, noRekPenerima);
        akunPenerima->transferMasuk(jumlah, noRekPengirim);
        
        cout << "Transfer berhasil!\n";
        cout << "Dari: " << akunPengirim->getNamaPemilik() 
             << " (" << noRekPengirim << ")\n";
        cout << "Ke: " << akunPenerima->getNamaPemilik() 
             << " (" << noRekPenerima << ")\n";
        cout << "Jumlah: Rp" << formatRupiah(jumlah) << "\n";
    }

    void simpanTransaksiKeFile() {
        ofstream file(namaFileTransaksi);
        
        if (!file.is_open()) {
            throw FileReadException(namaFileTransaksi);
        }

        file << "========================================\n";
        file << "LAPORAN TRANSAKSI BANK\n";
        file << "========================================\n\n";

        for (const auto& pair : daftarAkun) {
            const auto& akun = pair.second;
            file << "Rekening: " << akun->getNomorRekening() << "\n";
            file << "Pemilik: " << akun->getNamaPemilik() << "\n";
            file << "Saldo Akhir: Rp" << formatRupiah(akun->getSaldo()) << "\n";
            file << "----------------------------------------\n";
            
            const auto& riwayat = akun->getRiwayatTransaksi();
            for (size_t i = 0; i < riwayat.size(); i++) {
                const Transaction& t = riwayat[i];
                file << "  " << (i + 1) << ". " << t.jenisTransaksi 
                     << " | Rp" << formatRupiah(t.jumlah) 
                     << " | Saldo: Rp" << formatRupiah(t.saldoSetelahTransaksi) 
                     << " | " << t.waktu << "\n";
                if (!t.keterangan.empty()) {
                    file << "     Ket: " << t.keterangan << "\n";
                }
            }
            file << "\n";
        }

        file.close();
        cout << "Transaksi berhasil disimpan ke file: " 
             << namaFileTransaksi << "\n";
    }

    void bacaTransaksiDariFile() {
        ifstream file(namaFileTransaksi);
        
        if (!file.is_open()) {
            throw FileReadException(namaFileTransaksi);
        }

        cout << "\n========================================\n";
        cout << "ISI FILE: " << namaFileTransaksi << "\n";
        cout << "========================================\n";

        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }

        file.close();
        cout << "========================================\n";
    }

    void tampilkanSemuaAkun() const {
        cout << "\n========================================\n";
        cout << "DAFTAR SEMUA AKUN\n";
        cout << "========================================\n";
        
        if (daftarAkun.empty()) {
            cout << "Belum ada akun terdaftar.\n";
        } else {
            int no = 1;
            for (const auto& pair : daftarAkun) {
                const auto& akun = pair.second;
                cout << no++ << ". " << akun->getNomorRekening() 
                     << " - " << akun->getNamaPemilik() 
                     << " (Saldo: Rp" << formatRupiah(akun->getSaldo()) << ")\n";
            }
        }
        cout << "========================================\n";
    }

    void hapusAkun(const string& noRek) {
        auto it = daftarAkun.find(noRek);
        if (it == daftarAkun.end()) {
            throw UnknownAccountException(noRek);
        }
        daftarAkun.erase(it);
        cout << "Akun " << noRek << " berhasil dihapus.\n";
    }
};

// UTILITY

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void tampilkanMenu() {
    cout << "\n========================================\n";
    cout << "   SISTEM PENGELOLAAN BANK ACCOUNT\n";
    cout << "========================================\n";
    cout << "1. Tambah Akun Baru\n";
    cout << "2. Setor Tunai\n";
    cout << "3. Tarik Tunai\n";
    cout << "4. Transfer Antar Akun\n";
    cout << "5. Lihat Info Akun\n";
    cout << "6. Lihat Riwayat Transaksi\n";
    cout << "7. Lihat Semua Akun\n";
    cout << "8. Simpan Transaksi ke File\n";
    cout << "9. Baca Transaksi dari File\n";
    cout << "10. Hapus Akun\n";
    cout << "0. Keluar\n";
    cout << "========================================\n";
    cout << "Pilihan Anda: ";
}

// MENU

void menuTambahAkun(BankManager& manager) {
    try {
        string noRek, nama;
        double saldoAwal;

        cout << "\n--- TAMBAH AKUN BARU ---\n";
        cout << "Nomor Rekening: ";
        cin >> noRek;
        clearInputBuffer();
        
        cout << "Nama Pemilik: ";
        getline(cin, nama);
        
        cout << "Saldo Awal: Rp";
        cin >> saldoAwal;

        if (cin.fail()) {
            clearInputBuffer();
            throw InvalidInputException("Saldo harus berupa angka");
        }

        manager.tambahAkun(noRek, nama, saldoAwal);
    }
    catch (const InvalidInputException& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

void menuSetorTunai(BankManager& manager) {
    try {
        string noRek;
        double jumlah;

        cout << "\n--- SETOR TUNAI ---\n";
        cout << "Nomor Rekening: ";
        cin >> noRek;
        
        cout << "Jumlah Setor: Rp";
        cin >> jumlah;

        if (cin.fail()) {
            clearInputBuffer();
            throw InvalidInputException("Jumlah harus berupa angka");
        }

        auto akun = manager.cariAkun(noRek);
        akun->setorTunai(jumlah);
        
        cout << "\nSetor tunai berhasil!\n";
        cout << "Saldo sekarang: Rp" << formatRupiah(akun->getSaldo()) << "\n";
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

void menuTarikTunai(BankManager& manager) {
    try {
        string noRek;
        double jumlah;

        cout << "\n--- TARIK TUNAI ---\n";
        cout << "Nomor Rekening: ";
        cin >> noRek;
        
        cout << "Jumlah Tarik: Rp";
        cin >> jumlah;

        if (cin.fail()) {
            clearInputBuffer();
            throw InvalidInputException("Jumlah harus berupa angka");
        }

        auto akun = manager.cariAkun(noRek);
        akun->tarikTunai(jumlah);
        
        cout << "\nTarik tunai berhasil!\n";
        cout << "Saldo sekarang: Rp" << formatRupiah(akun->getSaldo()) << "\n";
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

void menuTransfer(BankManager& manager) {
    try {
        string noRekPengirim, noRekPenerima;
        double jumlah;

        cout << "\n--- TRANSFER ANTAR AKUN ---\n";
        cout << "Nomor Rekening Pengirim: ";
        cin >> noRekPengirim;
        
        cout << "Nomor Rekening Penerima: ";
        cin >> noRekPenerima;
        
        cout << "Jumlah Transfer: Rp";
        cin >> jumlah;

        if (cin.fail()) {
            clearInputBuffer();
            throw InvalidInputException("Jumlah harus berupa angka");
        }

        manager.transferAntarAkun(noRekPengirim, noRekPenerima, jumlah);
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

void menuLihatInfo(BankManager& manager) {
    try {
        string noRek;

        cout << "\n--- INFORMASI AKUN ---\n";
        cout << "Nomor Rekening: ";
        cin >> noRek;

        auto akun = manager.cariAkun(noRek);
        akun->tampilkanInfo();
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

void menuLihatRiwayat(BankManager& manager) {
    try {
        string noRek;

        cout << "\n--- RIWAYAT TRANSAKSI ---\n";
        cout << "Nomor Rekening: ";
        cin >> noRek;

        auto akun = manager.cariAkun(noRek);
        akun->tampilkanRiwayat();
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

void menuSimpanFile(BankManager& manager) {
    try {
        manager.simpanTransaksiKeFile();
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

void menuBacaFile(BankManager& manager) {
    try {
        manager.bacaTransaksiDariFile();
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

void menuHapusAkun(BankManager& manager) {
    try {
        string noRek;

        cout << "\n--- HAPUS AKUN ---\n";
        cout << "Nomor Rekening: ";
        cin >> noRek;

        char konfirmasi;
        cout << "Apakah Anda yakin ingin menghapus akun " << noRek << "? (y/n): ";
        cin >> konfirmasi;

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            manager.hapusAkun(noRek);
        } else {
            cout << "Penghapusan dibatalkan.\n";
        }
    }
    catch (const exception& e) {
        cout << "\n[ERROR] " << e.what() << "\n";
    }
}

// MAIN

int main() {
    BankManager manager("transaksi.txt");
    int pilihan;

    cout << "========================================\n";
    cout << "  SELAMAT DATANG DI SISTEM BANK\n";
    cout << "========================================\n";

    // Membuat akun contoh
    try {
        cout << "\nMembuat akun contoh...\n";
        manager.tambahAkun("1001", "Haidar Khadafi", 5000000);
        cout << "Akun dibuat dengan nomor rekening: 1001\n";
        manager.tambahAkun("1002", "Lionel Messi", 3000000);
        cout << "Akun dibuat dengan nomor rekening: 1002\n";
        manager.tambahAkun("1003", "Ahmad Dahlan", 2000000);
        cout << "Akun dibuat dengan nomor rekening: 1003\n";
    }
    catch (const exception& e) {
        cout << "[ERROR] " << e.what() << "\n";
    }

    // Loop menu utama
    do {
        tampilkanMenu();
        cin >> pilihan;

        if (cin.fail()) {
            clearInputBuffer();
            cout << "\n[ERROR] Input tidak valid! Masukkan angka.\n";
            continue;
        }

        clearInputBuffer();

        switch (pilihan) {
            case 1: menuTambahAkun(manager); break;
            case 2: menuSetorTunai(manager); break;
            case 3: menuTarikTunai(manager); break;
            case 4: menuTransfer(manager); break;
            case 5: menuLihatInfo(manager); break;
            case 6: menuLihatRiwayat(manager); break;
            case 7: manager.tampilkanSemuaAkun(); break;
            case 8: menuSimpanFile(manager); break;
            case 9: menuBacaFile(manager); break;
            case 10: menuHapusAkun(manager); break;
            case 0:
                cout << "\n========================================\n";
                cout << "Terima kasih telah menggunakan sistem bank!\n";
                cout << "========================================\n";
                break;
            default:
                cout << "\n[ERROR] Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
