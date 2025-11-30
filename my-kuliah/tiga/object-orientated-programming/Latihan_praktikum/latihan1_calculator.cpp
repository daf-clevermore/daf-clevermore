/*	Nama	: Haidar Khadafi
	NIM		: 24040700033
	Latihan 1: Calculator dengan Exception Handling	*/

#include <iostream>
#include <exception>
#include <string>

using namespace std;

// Exception untuk pembagian dengan nol
class DivideByZeroException : public exception {
private:
    string message;

public:
    DivideByZeroException() {
        message = "Error: Pembagian dengan nol tidak diperbolehkan!";
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Class Calculator
class Calculator {
public:
    // Operasi tambah
    double tambah(double a, double b) {
        return a + b;
    }

    // Operasi kurang
    double kurang(double a, double b) {
        return a - b;
    }

    // Operasi kali
    double kali(double a, double b) {
        return a * b;
    }

    // Operasi bagi dengan exception handling
    double bagi(double a, double b) {
        if (b == 0) {
            throw DivideByZeroException();
        }
        return a / b;
    }

    // Tampilkan hasil
    void tampilkanHasil(const string& operasi, double hasil) {
        cout << "Hasil " << operasi << ": " << hasil << endl;
    }
};

int main() {
    Calculator calc;
    double angka1, angka2;
    int pilihan;

    cout << "========================================\n";
    cout << "       PROGRAM CALCULATOR OOP\n";
    cout << "========================================\n\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah\n";
        cout << "2. Kurang\n";
        cout << "3. Kali\n";
        cout << "4. Bagi\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 0) break;

        if (pilihan >= 1 && pilihan <= 4) {
            cout << "Masukkan angka pertama: ";
            cin >> angka1;
            cout << "Masukkan angka kedua: ";
            cin >> angka2;

            try {
                double hasil;
                string operasi;

                switch (pilihan) {
                    case 1:
                        hasil = calc.tambah(angka1, angka2);
                        operasi = "penjumlahan";
                        calc.tampilkanHasil(operasi, hasil);
                        break;
                    case 2:
                        hasil = calc.kurang(angka1, angka2);
                        operasi = "pengurangan";
                        calc.tampilkanHasil(operasi, hasil);
                        break;
                    case 3:
                        hasil = calc.kali(angka1, angka2);
                        operasi = "perkalian";
                        calc.tampilkanHasil(operasi, hasil);
                        break;
                    case 4:
                        hasil = calc.bagi(angka1, angka2);
                        operasi = "pembagian";
                        calc.tampilkanHasil(operasi, hasil);
                        break;
                }
            }
            catch (const DivideByZeroException& e) {
                cout << "\n[EXCEPTION] " << e.what() << endl;
            }
            catch (const exception& e) {
                cout << "\n[ERROR] " << e.what() << endl;
            }
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    cout << "\nTerima kasih telah menggunakan calculator!\n";
    return 0;
}
