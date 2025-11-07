CREATE DATABASE db_perpustakaan;
USE db_perpustakaan;

CREATE TABLE buku (
  id INT AUTO_INCREMENT PRIMARY KEY,
  judul VARCHAR(150) NOT NULL,
  penulis VARCHAR(100) NOT NULL,
  tahun YEAR NOT NULL,
  penerbit VARCHAR(100) NOT NULL
);
