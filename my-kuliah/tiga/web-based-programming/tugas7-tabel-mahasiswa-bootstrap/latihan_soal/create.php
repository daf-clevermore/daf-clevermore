<!-- create.php -->

<?php include 'db.php'; ?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Tambah Mahasiswa</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body class="bg-light">

<div class="container mt-5">
  <div class="card shadow-sm">
    <div class="card-header bg-primary text-white">Tambah Mahasiswa</div>
    <div class="card-body">
      <form method="POST">
        <div class="mb-3">
          <label class="form-label">Nama</label>
          <input type="text" name="nama" class="form-control" required>
        </div>
        <div class="mb-3">
          <label class="form-label">NIM</label>
          <input type="text" name="nim" class="form-control" required>
        </div>
        <div class="mb-3">
          <label class="form-label">Jurusan</label>
          <input type="text" name="jurusan" class="form-control" required>
        </div>
        <button type="submit" name="simpan" class="btn btn-primary">Simpan</button>
        <a href="index.php" class="btn btn-secondary">Kembali</a>
      </form>
    </div>
  </div>
</div>

</body>
</html>

<?php
if (isset($_POST['simpan'])) {
  $nama = mysqli_real_escape_string($conn, $_POST['nama']);
  $nim = mysqli_real_escape_string($conn, $_POST['nim']);
  $jurusan = mysqli_real_escape_string($conn, $_POST['jurusan']);

  $sql = "INSERT INTO mahasiswa (nama, nim, jurusan) VALUES ('$nama', '$nim', '$jurusan')";
  if (mysqli_query($conn, $sql)) {
    header("Location: index.php?status=success");
    exit;
  } else {
    echo "<div class='alert alert-danger text-center mt-3'>Gagal menyimpan data!</div>";
  }
}
?>
