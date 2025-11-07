<!-- create.php -->

<?php include 'db.php'; ?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Tambah Buku</title>
  <link rel="stylesheet" href="assets/style.css">
</head>
<body>
  <div class="form-box">
    <h2 style="text-align:center;">Tambah Buku Baru</h2>

    <form method="POST">
      <label>Judul:</label>
      <input type="text" name="judul" required>

      <label>Penulis:</label>
      <input type="text" name="penulis" required>

      <label>Tahun:</label>
      <input type="number" name="tahun" min="1000" max="9999" required>

      <label>Penerbit:</label>
      <input type="text" name="penerbit" required>

      <button type="submit" name="simpan">Simpan</button>
      <a href="index.php" class="btn" style="background:gray;">Kembali</a>
    </form>
  </div>
</body>
</html>

<?php
if (isset($_POST['simpan'])) {
  $judul = $_POST['judul'];
  $penulis = $_POST['penulis'];
  $tahun = $_POST['tahun'];
  $penerbit = $_POST['penerbit'];

  $sql = "INSERT INTO buku (judul, penulis, tahun, penerbit)
          VALUES ('$judul', '$penulis', '$tahun', '$penerbit')";
  mysqli_query($conn, $sql);

  echo "<script>window.location='index.php';</script>";
}
?>
