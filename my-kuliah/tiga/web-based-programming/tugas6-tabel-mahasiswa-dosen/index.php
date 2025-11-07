<?php 
include 'koneksi.php';
$table = isset($_GET['table']) ? $_GET['table'] : 'mahasiswa'; 
?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Data <?php echo ucfirst($table); ?></title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <div class="container">
    <h2>Data <?php echo ucfirst($table); ?></h2>

    <div class="nav">
      <a href="?table=mahasiswa">Mahasiswa</a>
      <a href="?table=dosen">Dosen</a>
      <a href="form_input.php?table=<?php echo $table; ?>" class="btn">+ Tambah Data</a>
    </div>

    <form method="GET" class="search-bar">
      <input type="hidden" name="table" value="<?php echo $table; ?>">
      <input type="text" name="search" placeholder="Cari nama...">
      <button type="submit">Cari</button>
    </form>

    <table>
      <tr>
        <th><a href="?table=<?php echo $table; ?>&sort=nama" class="header">Nama</a></th>
        <th><a href="?table=<?php echo $table; ?>&sort=<?php echo $table == 'mahasiswa' ? 'nim' : 'NIP'; ?>" class="header">
          <?php echo $table == 'mahasiswa' ? 'NIM' : 'NIP'; ?>
        </a></th>
        <th><a href="?table=<?php echo $table; ?>&sort=<?php echo $table == 'mahasiswa' ? 'jurusan' : 'prodi'; ?>" class="header">
          <?php echo $table == 'mahasiswa' ? 'Jurusan' : 'Prodi'; ?>
        </a></th>
        <th>Aksi</th>
      </tr>

      <?php
      $where = "";
      if (!empty($_GET['search'])) {
        $search = $_GET['search'];
        $where = "WHERE nama LIKE '%$search%'";
      }

      $order = "";
      if (!empty($_GET['sort'])) {
        $sort = $_GET['sort'];
        $order = "ORDER BY $sort ASC";
      }

      $sql = "SELECT * FROM $table $where $order";
      $result = mysqli_query($koneksi, $sql);

      while ($row = mysqli_fetch_assoc($result)) {
        $id = $row['id'];
        $col2 = $table == 'mahasiswa' ? $row['nim'] : $row['nip'];
        $col3 = $table == 'mahasiswa' ? $row['jurusan'] : $row['prodi'];

        echo "<tr>
          <td>{$row['nama']}</td>
          <td>{$col2}</td>
          <td>{$col3}</td>
          <td>
            <a href='edit.php?table=$table&id=$id' class='btn'>Edit</a>
            <a href='hapus.php?table=$table&id=$id' class='btn' style='background:#dc3545;' onclick='return confirm(\"Yakin mau hapus?\")'>Hapus</a>
          </td>
        </tr>";
      }
      ?>
    </table>
  </div>
</body>
</html>
