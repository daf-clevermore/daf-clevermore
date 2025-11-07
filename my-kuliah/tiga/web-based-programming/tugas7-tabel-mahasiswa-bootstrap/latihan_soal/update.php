<!-- update.php -->

<?php include 'db.php'; ?>

<?php
$id = $_GET['id'];
$result = mysqli_query($conn, "SELECT * FROM mahasiswa WHERE id = $id");
$row = mysqli_fetch_assoc($result);
?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Edit Mahasiswa</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body class="bg-light">

<div class="container mt-5">
  <div class="card shadow-sm">
    <div class="card-header bg-info text-white">Edit Mahasiswa</div>
    <div class="card-body">
      <form method="POST">
        <div class="mb-3">
          <label class="form-label">Nama</label>
          <input type="text" name="nama" class="form-control" value="<?= $row['nama'] ?>" required>
        </div>
        <div class="mb-3">
          <label class="form-label">NIM</label>
          <input type="text" name="nim" class="form-control" value="<?= $row['nim'] ?>" required>
        </div>
        <div class="mb-3">
          <label class="form-label">Jurusan</label>
          <input type="text" name="jurusan" class="form-control" value="<?= $row['jurusan'] ?>" required>
        </div>
        <button type="submit" name="update" class="btn btn-info">Update</button>
        <a href="index.php" class="btn btn-secondary">Kembali</a>
      </form>
    </div>
  </div>
</div>

</body>
</html>

<?php
if (isset($_POST['update'])) {
  $nama = mysqli_real_escape_string($conn, $_POST['nama']);
  $nim = mysqli_real_escape_string($conn, $_POST['nim']);
  $jurusan = mysqli_real_escape_string($conn, $_POST['jurusan']);

  $sql = "UPDATE mahasiswa SET nama='$nama', nim='$nim', jurusan='$jurusan' WHERE id=$id";
  if (mysqli_query($conn, $sql)) {
    header("Location: index.php?status=updated");
    exit;
  } else {
    echo "<div class='alert alert-danger text-center mt-3'>Gagal memperbarui data!</div>";
  }
}
?>
