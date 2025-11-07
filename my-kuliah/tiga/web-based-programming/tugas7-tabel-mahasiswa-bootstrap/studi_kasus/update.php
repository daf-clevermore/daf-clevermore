<!-- update.php -->

<?php 
include 'db.php';
$id = $_GET['id'];
$data = mysqli_query($conn, "SELECT * FROM buku WHERE id=$id");
$row = mysqli_fetch_assoc($data);
?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Edit Buku</title>
  <link rel="stylesheet" href="assets/style.css">
</head>
<body>
  <div class="form-box">
    <h2 style="text-align:center;">Edit Buku</h2>

    <form method="POST">
      <input type="hidden" name="id" value="<?php echo $row['id']; ?>">

      <label>Judul:</label>
      <input type="text" name="judul" value="<?php echo $row['judul']; ?>" required>

      <label>Penulis:</label>
      <input type="text" name="penulis" value="<?php echo $row['penulis']; ?>" required>

      <label>Tahun:</label>
      <input type="number" name="tahun" value="<?php echo $row['tahun']; ?>" required>

      <label>Penerbit:</label>
      <input type="text" name="penerbit" value="<?php echo $row['penerbit']; ?>" required>

      <button type="submit" name="update">Update</button>
      <a href="index.php" class="btn" style="background:gray;">Kembali</a>
    </form>
  </div>
</body>
</html>

<?php
if (isset($_POST['update'])) {
  $id = $_POST['id'];
  $judul = $_POST['judul'];
  $penulis = $_POST['penulis'];
  $tahun = $_POST['tahun'];
  $penerbit = $_POST['penerbit'];

  mysqli_query($conn, "UPDATE buku SET 
    judul='$judul', penulis='$penulis', tahun='$tahun', penerbit='$penerbit'
    WHERE id=$id");

  echo "<script>window.location='index.php';</script>";
}
?>
