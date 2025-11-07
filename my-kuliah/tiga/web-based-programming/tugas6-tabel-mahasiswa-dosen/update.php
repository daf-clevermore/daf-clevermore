<?php
include 'koneksi.php';
$table = $_POST['table'];
$id = $_POST['id'];
$nama = $_POST['nama'];

if ($table == 'mahasiswa') {
  $nim = $_POST['nim'];
  $jurusan = $_POST['jurusan'];
  mysqli_query($koneksi, "UPDATE mahasiswa SET nama='$nama', nim='$nim', jurusan='$jurusan' WHERE id=$id");
} else {
  $nip = $_POST['nip'];
  $prodi = $_POST['prodi'];
  mysqli_query($koneksi, "UPDATE dosen SET nama='$nama', nip='$nip', prodi='$prodi' WHERE id=$id");
}

header("Location: index.php?table=$table");
?>
