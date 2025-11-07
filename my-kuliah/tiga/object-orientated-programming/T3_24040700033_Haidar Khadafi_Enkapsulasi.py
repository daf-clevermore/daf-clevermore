class Buku:
    def __init__(self, judul, penulis, harga):
        self.__judul = judul
        self.__penulis = penulis
        self.__harga = None
        self.set_harga(harga)

    def get_judul(self):
        return self.__judul

    def get_penulis(self):
        return self.__penulis

    def get_harga(self):
        return self.__harga

    def set_harga(self, harga):
        if harga < 0:
            print("Harga tidak valid!")
        else:
            self.__harga = harga

    def tampilkan_info(self):
        print(f"Judul  : {self.__judul}")
        print(f"Penulis: {self.__penulis}")
        print(f"Harga  : Rp{self.__harga:,}")

class Ebook(Buku):
    def __init__(self, judul, penulis, harga, ukuran_file, format_file):
        super().__init__(judul, penulis, harga)
        self.__ukuran_file = None
        self.__format_file = format_file
        self.set_ukuran_file(ukuran_file)

    def get_ukuran_file(self):
        return self.__ukuran_file

    def get_format_file(self):
        return self.__format_file

    def set_ukuran_file(self, ukuran_file):
        if ukuran_file < 0:
            print("Ukuran file tidak valid!")
        else:
            self.__ukuran_file = ukuran_file

    def set_format_file(self, format_file):
        self.__format_file = format_file

    def tampilkan_info(self):
        super().tampilkan_info()
        print(f"Ukuran File: {self.__ukuran_file} MB")
        print(f"Format File: {self.__format_file}")

buku1 = Buku("MONOLOG", "Tan Malaka", 800000)
buku1.tampilkan_info()

print("\n---\n")

ebook1 = Ebook("Laskar Pelangi", "Andrea Hirata", 120000, 5, "PDF")
ebook1.tampilkan_info()

print("\n--- Contoh validasi ---")
ebook2 = Ebook("Invalid Ebook", "Unknown", -50000, -3, "EPUB")
