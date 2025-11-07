<!-- index.php -->

<?php include 'db.php'; ?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Data Mahasiswa</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body class="bg-light">

<div class="container mt-5">
  <h2 class="text-center mb-4">Data Mahasiswa</h2>

  <?php if (isset($_GET['status'])): ?>
    <?php if ($_GET['status'] == 'success'): ?>
      <div class="alert alert-success">Data berhasil disimpan!</div>
    <?php elseif ($_GET['status'] == 'deleted'): ?>
      <div class="alert alert-warning">Data berhasil dihapus!</div>
    <?php elseif ($_GET['status'] == 'updated'): ?>
      <div class="alert alert-info">Data berhasil diperbarui!</div>
    <?php else: ?>
      <div class="alert alert-danger">Terjadi kesalahan!</div>
    <?php endif; ?>
  <?php endif; ?>

  <div class="d-flex justify-content-between align-items-center mb-3">
    <a href="create.php" class="btn btn-primary">+ Tambah Mahasiswa</a>

    <form method="GET" class="d-flex gap-2">
      <input type="text" name="search" class="form-control" placeholder="Cari nama atau jurusan..." value="<?= $_GET['search'] ?? '' ?>">
      <button class="btn btn-outline-primary" type="submit">Cari</button>
    </form>
  </div>

  <table class="table table-bordered table-striped shadow-sm">
    <tr class="table-primary">
      <th>No</th>
      <th>Nama</th>
      <th>NIM</th>
      <th>Jurusan</th>
      <th>Aksi</th>
    </tr>

    <?php
    $no = 1;
    $search = $_GET['search'] ?? '';
    $query = "SELECT * FROM mahasiswa WHERE nama LIKE '%$search%' OR jurusan LIKE '%$search%'";
    $result = mysqli_query($conn, $query);

    if (!$result) {
  die("Query error: " . mysqli_error($conn));
}


    while ($row = mysqli_fetch_assoc($result)):
    ?>
      <tr>
        <td><?= $no++ ?></td>
        <td><?= $row['nama'] ?></td>
        <td><?= $row['nim'] ?></td>
        <td><?= $row['jurusan'] ?></td>
        <td>
          <a href="update.php?id=<?= $row['id'] ?>" class="btn btn-sm btn-info">Edit</a>
          <a href="delete.php?id=<?= $row['id'] ?>" class="btn btn-sm btn-danger" onclick="return confirm('Yakin ingin menghapus data ini?')">Hapus</a>
        </td>
      </tr>
    <?php endwhile; ?>
  </table>
</div>

</body>
</html>
