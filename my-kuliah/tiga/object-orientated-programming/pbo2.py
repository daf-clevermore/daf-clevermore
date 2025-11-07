class Buku:
    def __init__(self, judul, penulis, tahun):
        self.judul = judul
        self.penulis = penulis
        self.tahun = tahun

    def tampilkanBuku(self):
        print(f"{self.judul} - {self.penulis} ({self.tahun})")

a1 = Buku("Laut Bercerita", "Leila S.Chudori", 2017)
a2 = Buku("Ronggeng Dukuh Paruk", "Ahmad Tohari", 1982)
a3 = Buku("Sang Pemimpi", "Andrea Hirata", 2006)

a1.tampilkanBuku()
a2.tampilkanBuku()
a3.tampilkanBuku()
