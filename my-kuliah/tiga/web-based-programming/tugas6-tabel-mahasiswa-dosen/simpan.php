<?php
include 'koneksi.php';
$table = $_POST['table'];

$nama = $_POST['nama'];

if ($table == 'mahasiswa') {
  $nim = $_POST['nim'];
  $jurusan = $_POST['jurusan'];
  mysqli_query($koneksi, "INSERT INTO mahasiswa (nama, nim, jurusan) VALUES ('$nama','$nim','$jurusan')");
} else {
  $nip = $_POST['nip'];
  $prodi = $_POST['prodi'];
  mysqli_query($koneksi, "INSERT INTO dosen (nama, nip, prodi) VALUES ('$nama','$nip', '$prodi')");
}

header("Location: index.php?table=$table");
?>
