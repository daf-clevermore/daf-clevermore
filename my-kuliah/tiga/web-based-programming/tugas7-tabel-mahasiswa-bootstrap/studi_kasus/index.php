<!-- index.php -->

<?php include 'db.php'; ?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Data Buku Perpustakaan</title>
  <link rel="stylesheet" href="assets/style.css">
</head>
<body>
  <div class="container">
    <h2>Data Buku Perpustakaan</h2>
    <div class="top-bar">
  <a href="create.php" class="btn">+ Tambah Buku</a>

  <form method="GET" class="search-bar">
    <input type="text" name="search" placeholder="Cari judul atau penulis...">
    <button type="submit">Cari</button>
  </form>
</div>


    <table>
      <tr>
        <th><a href="?sort=judul">Judul</a></th>
        <th><a href="?sort=penulis">Penulis</a></th>
        <th><a href="?sort=tahun">Tahun</a></th>
        <th><a href="?sort=penerbit">Penerbit</a></th>
        <th>Aksi</th>
      </tr>

      <?php
      $where = "";
      if (!empty($_GET['search'])) {
        $search = $_GET['search'];
        $where = "WHERE judul LIKE '%$search%' OR penulis LIKE '%$search%'";
      }

      $order = "";
      if (!empty($_GET['sort'])) {
        $sort = $_GET['sort'];
        $order = "ORDER BY $sort ASC";
      }

      $sql = "SELECT * FROM buku $where $order";
      $result = mysqli_query($conn, $sql);

      while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>
          <td>{$row['judul']}</td>
          <td>{$row['penulis']}</td>
          <td>{$row['tahun']}</td>
          <td>{$row['penerbit']}</td>
          <td>
            <a href='update.php?id={$row['id']}' class='btn'>Edit</a>
            <a href='delete.php?id={$row['id']}' class='btn' style='background:#dc3545;' onclick='return confirm(\"Yakin hapus buku ini?\")'>Hapus</a>
          </td>
        </tr>";
      }
      ?>
    </table>
  </div>
</body>
</html>
