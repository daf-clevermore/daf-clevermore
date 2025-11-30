/*	Nama	: Haidar Khadafi
	NIM		: 24040700033
	Latihan 3: Simulasi ATM OOP dengan Exception Handling	*/

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// Fungsi helper untuk format rupiah
string formatRupiah(double jumlah) {
    stringstream ss;
    ss << fixed << setprecision(0) << jumlah;
    return ss.str();
}

// Exception untuk saldo tidak cukup
class SaldoTidakCukupException : public exception {
private:
    string message;
    double saldoTersedia;
    double jumlahDiminta;

public:
    SaldoTidakCukupException(double saldo, double jumlah) 
        : saldoTersedia(saldo), jumlahDiminta(jumlah) {
        message = "Saldo tidak cukup! Saldo: Rp" + formatRupiah(saldoTersedia) + 
                  ", Diminta: Rp" + formatRupiah(jumlahDiminta);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Exception untuk PIN salah
class PinSalahException : public exception {
private:
    string message;

public:
    PinSalahException() {
        message = "PIN yang Anda masukkan salah!";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Exception untuk jumlah tidak valid
class JumlahTidakValidException : public exception {
private:
    string message;

public:
    JumlahTidakValidException(const string& msg) {
        message = "Jumlah tidak valid: " + msg;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Struct untuk riwayat transaksi
struct RiwayatTransaksi {
    string jenis;
    double jumlah;
    double saldoSetelah;
    string waktu;

    RiwayatTransaksi(const string& j, double jml, double saldo) 
        : jenis(j), jumlah(jml), saldoSetelah(saldo) {
        time_t now = time(0);
        char* dt = ctime(&now);
        waktu = string(dt);
        if (!waktu.empty() && waktu[waktu.length()-1] == '\n') {
            waktu.erase(waktu.length()-1);
        }
    }
};

// Class Rekening ATM
class RekeningATM {
private:
    string nomorRekening;
    string namaPemilik;
    string pin;
    double saldo;
    vector<RiwayatTransaksi> riwayat;

    void validasiJumlah(double jumlah) const {
        if (jumlah <= 0) {
            throw JumlahTidakValidException("Jumlah harus lebih besar dari 0");
        }
        if (jumlah < 10000) {
            throw JumlahTidakValidException("Minimal transaksi Rp10.000");
        }
    }

public:
    RekeningATM(const string& noRek, const string& nama, 
                const string& pinAwal, double saldoAwal) 
        : nomorRekening(noRek), namaPemilik(nama), 
          pin(pinAwal), saldo(saldoAwal) {
        if (saldoAwal > 0) {
            riwayat.push_back(RiwayatTransaksi("SALDO AWAL", saldoAwal, saldo));
        }
    }

    // Verifikasi PIN
    bool verifikasiPin(const string& inputPin) const {
        if (inputPin != pin) {
            throw PinSalahException();
        }
        return true;
    }

    // Cek saldo
    double cekSaldo() const {
        return saldo;
    }

    // Tarik tunai
    void tarikTunai(double jumlah) {
        validasiJumlah(jumlah);
        
        if (saldo < jumlah) {
            throw SaldoTidakCukupException(saldo, jumlah);
        }

        saldo -= jumlah;
        riwayat.push_back(RiwayatTransaksi("TARIK TUNAI", jumlah, saldo));
    }

    // Setor tunai
    void setorTunai(double jumlah) {
        validasiJumlah(jumlah);
        saldo += jumlah;
        riwayat.push_back(RiwayatTransaksi("SETOR TUNAI", jumlah, saldo));
    }

    // Transfer
    void transfer(double jumlah, const string& tujuan) {
        validasiJumlah(jumlah);
        
        if (saldo < jumlah) {
            throw SaldoTidakCukupException(saldo, jumlah);
        }

        saldo -= jumlah;
        riwayat.push_back(
            RiwayatTransaksi("TRANSFER ke " + tujuan, jumlah, saldo)
        );
    }

    // Ubah PIN
    void ubahPin(const string& pinLama, const string& pinBaru) {
        if (pinLama != pin) {
            throw PinSalahException();
        }
        pin = pinBaru;
    }

    // Tampilkan info
    void tampilkanInfo() const {
        cout << "\n========================================\n";
        cout << "         INFORMASI REKENING\n";
        cout << "========================================\n";
        cout << "Nomor Rekening : " << nomorRekening << endl;
        cout << "Nama Pemilik   : " << namaPemilik << endl;
        cout << "Saldo          : Rp" << formatRupiah(saldo) << endl;
        cout << "========================================\n";
    }

    // Tampilkan riwayat
    void tampilkanRiwayat() const {
        cout << "\n========================================\n";
        cout << "       RIWAYAT TRANSAKSI\n";
        cout << "========================================\n";

        if (riwayat.empty()) {
            cout << "Belum ada transaksi.\n";
        } else {
            for (size_t i = 0; i < riwayat.size(); i++) {
                const RiwayatTransaksi& r = riwayat[i];
                cout << "\n" << (i + 1) << ". " << r.jenis << endl;
                cout << "   Jumlah : Rp" << formatRupiah(r.jumlah) << endl;
                cout << "   Saldo  : Rp" << formatRupiah(r.saldoSetelah) << endl;
                cout << "   Waktu  : " << r.waktu << endl;
            }
        }
        cout << "========================================\n";
    }

    string getNamaPemilik() const { return namaPemilik; }
};

// Class ATM
class ATM {
private:
    RekeningATM* rekeningAktif;
    bool sudahLogin;

public:
    ATM() : rekeningAktif(nullptr), sudahLogin(false) {}

    void setRekening(RekeningATM* rekening) {
        rekeningAktif = rekening;
        sudahLogin = false;
    }

    bool login(const string& pin) {
        if (rekeningAktif == nullptr) {
            cout << "Tidak ada rekening aktif!\n";
            return false;
        }

        try {
            rekeningAktif->verifikasiPin(pin);
            sudahLogin = true;
            cout << "\nLogin berhasil!\n";
            cout << "Selamat datang, " << rekeningAktif->getNamaPemilik() << "!\n";
            return true;
        }
        catch (const PinSalahException& e) {
            cout << "\n[EXCEPTION] " << e.what() << endl;
            return false;
        }
    }

    void tampilkanMenu() {
        if (!sudahLogin) {
            cout << "\nAnda belum login!\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "           MENU ATM\n";
        cout << "========================================\n";
        cout << "1. Cek Saldo\n";
        cout << "2. Tarik Tunai\n";
        cout << "3. Setor Tunai\n";
        cout << "4. Transfer\n";
        cout << "5. Ubah PIN\n";
        cout << "6. Riwayat Transaksi\n";
        cout << "0. Logout\n";
        cout << "========================================\n";
    }

    void prosesMenu(int pilihan) {
        if (!sudahLogin) {
            cout << "\nAnda belum login!\n";
            return;
        }

        try {
            switch (pilihan) {
                case 1: {
                    cout << "\nSaldo Anda: Rp" << formatRupiah(rekeningAktif->cekSaldo()) << endl;
                    break;
                }
                case 2: {
                    double jumlah;
                    cout << "Jumlah penarikan: Rp";
                    cin >> jumlah;
                    rekeningAktif->tarikTunai(jumlah);
                    cout << "\nPenarikan berhasil!\n";
                    cout << "Saldo sekarang: Rp" << formatRupiah(rekeningAktif->cekSaldo()) << endl;
                    break;
                }
                case 3: {
                    double jumlah;
                    cout << "Jumlah setoran: Rp";
                    cin >> jumlah;
                    rekeningAktif->setorTunai(jumlah);
                    cout << "\nSetoran berhasil!\n";
                    cout << "Saldo sekarang: Rp" << formatRupiah(rekeningAktif->cekSaldo()) << endl;
                    break;
                }
                case 4: {
                    double jumlah;
                    string tujuan;
                    cout << "Nomor rekening tujuan: ";
                    cin >> tujuan;
                    cout << "Jumlah transfer: Rp";
                    cin >> jumlah;
                    rekeningAktif->transfer(jumlah, tujuan);
                    cout << "\nTransfer berhasil!\n";
                    cout << "Saldo sekarang: Rp" << formatRupiah(rekeningAktif->cekSaldo()) << endl;
                    break;
                }
                case 5: {
                    string pinLama, pinBaru;
                    cout << "PIN lama: ";
                    cin >> pinLama;
                    cout << "PIN baru: ";
                    cin >> pinBaru;
                    rekeningAktif->ubahPin(pinLama, pinBaru);
                    cout << "\nPIN berhasil diubah!\n";
                    break;
                }
                case 6: {
                    rekeningAktif->tampilkanRiwayat();
                    break;
                }
                case 0: {
                    sudahLogin = false;
                    cout << "\nLogout berhasil. Terima kasih!\n";
                    break;
                }
                default: {
                    cout << "Pilihan tidak valid!\n";
                }
            }
        }
        catch (const SaldoTidakCukupException& e) {
            cout << "\n[EXCEPTION] " << e.what() << endl;
        }
        catch (const JumlahTidakValidException& e) {
            cout << "\n[EXCEPTION] " << e.what() << endl;
        }
        catch (const PinSalahException& e) {
            cout << "\n[EXCEPTION] " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "\n[ERROR] " << e.what() << endl;
        }
    }

    bool isSudahLogin() const { return sudahLogin; }
};

int main() {
    // Buat rekening contoh
    RekeningATM rekening("1234567890", "Haidar Khadafi", "123456", 1000000);
    
    ATM atm;
    atm.setRekening(&rekening);

    cout << "========================================\n";
    cout << "       SIMULASI ATM OOP\n";
    cout << "========================================\n";
    cout << "\nRekening contoh:\n";
    cout << "Nomor: 1234567890\n";
    cout << "PIN: 123456\n";
    cout << "Saldo: Rp1.000.000\n";

    // Login
    string pin;
    int percobaan = 0;
    while (percobaan < 3 && !atm.isSudahLogin()) {
        cout << "\nMasukkan PIN: ";
        cin >> pin;
        if (!atm.login(pin)) {
            percobaan++;
            cout << "Percobaan ke-" << percobaan << " dari 3\n";
        }
    }

    if (!atm.isSudahLogin()) {
        cout << "\nKartu Anda diblokir karena 3x salah PIN!\n";
        return 1;
    }

    // Menu utama
    int pilihan;
    do {
        atm.tampilkanMenu();
        cout << "Pilihan: ";
        cin >> pilihan;
        atm.prosesMenu(pilihan);
    } while (pilihan != 0 && atm.isSudahLogin());

    return 0;
}
