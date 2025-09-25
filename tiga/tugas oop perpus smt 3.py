class Buku:
    def __init__(self, judul, penulis, tahun, isbn):
        self.judul = judul
        self.penulis = penulis
        self.tahun = tahun
        self.isbn = isbn
        self.dipinjam = False

    def tampilkan_info(self):
        status = "Dipinjam" if self.dipinjam else "Tersedia"
        print(f"[{self.isbn}] {self.judul} - {self.penulis} ({self.tahun}) | {status}")

class Anggota:
    def __init__(self, nama, nim, jurusan):
        self.nama = nama
        self.nim = nim
        self.jurusan = jurusan
        self.daftar_pinjaman = []

    def pinjam_buku(self, buku):
        if buku.dipinjam:
            print(f"Buku '{buku.judul}' sedang dipinjam oleh anggota lain!")
        else:
            buku.dipinjam = True
            self.daftar_pinjaman.append(buku)
            print(f"{self.nama} berhasil meminjam '{buku.judul}'!")

    def kembalikan_buku(self, buku):
        if buku in self.daftar_pinjaman:
            buku.dipinjam = False
            self.daftar_pinjaman.remove(buku)
            print(f"{self.nama} mengembalikan '{buku.judul}'")
        else:
            print(f"{self.nama} tidak meminjam buku ini.")

    def tampilkan_info(self):
        if not self.daftar_pinjaman:
            print(" Tidak ada buku yang dipinjam")
        else:
            print(" Daftar Pinjaman:")
        for b in self.daftar_pinjaman:
            print(f" - {b.judul} (ISBN: {b.isbn})")

class Mahasiswa(Anggota):
    def tampilkan_info(self):
        print(f"[Mahasiswa] {self.nama} - NIM: {self.nim} | Jurusan: {self.jurusan}")
        super().tampilkan_info()

class Dosen(Anggota):
    def tampilkan_info(self):
        print(f"[Dosen] {self.nama} - NIP: {self.nim} | Jurusan: {self.jurusan}")
        super().tampilkan_info()

class Petugas:
    def __init__(self, nama, id, jabatan):
        self.nama = nama
        self.id = id
        self.jabatan = jabatan

    def tampilkan_info(self):
        print(f"[{self.id}] {self.nama} | Jabatan: {self.jabatan}")

daftar_buku = []
daftar_anggota = []
daftar_petugas = []

def menu():
    while True:
        print("\n=== Sistem Perpustakaan ===")
        print("1. Tambah Buku")
        print("2. Lihat Semua Buku")
        print("3. Tambah Anggota")
        print("4. Lihat Semua Anggota")
        print("5. Pinjam Buku")
        print("6. Kembalikan Buku")
        print("7. Tambah Petugas")
        print("8. Lihat Semua Petugas")
        print("0. Keluar")

        pilihan = input("Pilih menu: ")

        if pilihan == "1":
            judul = input("Judul: ")
            penulis = input("Penulis: ")
            tahun = int(input("Tahun: "))
            isbn = input("ISBN: ")
            daftar_buku.append(Buku(judul, penulis, tahun, isbn))
            print("Buku berhasil ditambahkan!")

        elif pilihan == "2":
            print("\nDaftar Buku:")
            for b in daftar_buku:
                b.tampilkan_info()

        elif pilihan == "3":
            nama = input("Nama: ")
            tipe = input("Tipe (Mahasiswa/Dosen)? [M/D]: ")
            if tipe.upper() == "M":
                nim = input("NIM: ")
                jurusan = input("Jurusan: ")
                daftar_anggota.append(Mahasiswa(nama, nim, jurusan))
            else:
                nim = input("NIP: ")
                jurusan = input("Jurusan: ")
                daftar_anggota.append(Dosen(nama, nim, jurusan))
            print("Anggota berhasil ditambahkan!")

        elif pilihan == "4":
            print("\nDaftar Anggota:")
            for a in daftar_anggota:
                a.tampilkan_info()

        elif pilihan == "5":
            nim = input("NIM/NIP Anggota: ")
            isbn = input("ISBN Buku: ")
            anggota = next((a for a in daftar_anggota if a.nim == nim), None)
            buku = next((b for b in daftar_buku if b.isbn == isbn), None)
            if anggota and buku:
                anggota.pinjam_buku(buku)
            else:
                print("Data tidak ditemukan.")

        elif pilihan == "6":
            nim = input("NIM/NIP Anggota: ")
            isbn = input("ISBN Buku: ")
            anggota = next((a for a in daftar_anggota if a.nim == nim), None)
            buku = next((b for b in daftar_buku if b.isbn == isbn), None)
            if anggota and buku:
                anggota.kembalikan_buku(buku)
            else:
                print("Data tidak ditemukan.")

        elif pilihan == "7":
            nama = input("Nama: ")
            id = input("ID: ")
            jabatan = input("Jabatan: ")
            daftar_petugas.append(Petugas(nama, id, jabatan))
            print("Petugas berhasil ditambahkan!")

        elif pilihan == "8":
            print("\nDaftar Petugas")
            for c in daftar_petugas:
                c.tampilkan_info()

        elif pilihan == "0":
            print("Terima kasih sudah menggunakan sistem perpustakaan!")
            break
        else:
            print("Pilihan tidak valid.")

if __name__ == "__main__":
    menu()
