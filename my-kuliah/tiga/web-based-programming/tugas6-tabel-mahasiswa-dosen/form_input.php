<?php 
$table = isset($_GET['table']) ? $_GET['table'] : 'mahasiswa';
$isMahasiswa = ($table == 'mahasiswa');
?>

<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8">
  <title>Tambah Data <?php echo ucfirst($table); ?></title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <h2>Tambah Data <?php echo ucfirst($table); ?></h2>

  <div class="form-box">
    <form method="POST" action="simpan.php">
        <input type="hidden" name="table" value="<?php echo $table; ?>">

        <label>Nama:</label><br>
        <input type="text" name="nama" required><br>

        <label><?php echo $isMahasiswa ? 'NIM:' : 'NIP:'; ?></label><br>
        <input type="text" name="<?php echo $isMahasiswa ? 'nim' : 'nip'; ?>" required><br>

        <label><?php echo $isMahasiswa ? 'Jurusan:' : 'Prodi:'; ?></label><br>
        <input type="text" name="<?php echo $isMahasiswa ? 'jurusan' : 'prodi'; ?>" required><br><br>

        <button type="submit">Simpan</button>
    </form>
  </div>
</body>
</html>
