<?php
include 'koneksi.php';
$table = $_GET['table'];
$id = $_GET['id'];
$data = mysqli_query($koneksi, "SELECT * FROM $table WHERE id=$id");
$row = mysqli_fetch_assoc($data);
?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Edit Data <?php echo ucfirst($table); ?></title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <h2>Edit Data <?php echo ucfirst($table); ?></h2>
  <div class="form-box">
    <form method="POST" action="update.php">
        <input type="hidden" name="id" value="<?php echo $row['id']; ?>">
        <input type="hidden" name="table" value="<?php echo $table; ?>">

        <label>Nama:</label><br>
        <input type="text" name="nama" value="<?php echo $row['nama']; ?>"><br>

        <?php if ($table == 'mahasiswa'): ?>
        <label>NIM:</label><br>
        <input type="text" name="nim" value="<?php echo $row['nim']; ?>"><br>
        <label>Jurusan:</label><br>
        <input type="text" name="jurusan" value="<?php echo $row['jurusan']; ?>"><br>
        <?php else: ?>
        <label>NIP:</label><br>
        <input type="text" name="nip" value="<?php echo $row['nip']; ?>"><br>
        <label>Prodi:</label><br>
        <input type="text" name="prodi" value="<?php echo $row['prodi']; ?>"><br>
        <?php endif; ?>

        <br><button type="submit">Update</button>
    </form>
  </div>
</body>
</html>
