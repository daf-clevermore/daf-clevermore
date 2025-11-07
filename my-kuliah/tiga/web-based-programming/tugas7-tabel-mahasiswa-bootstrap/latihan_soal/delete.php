<!-- delete.php -->

<?php
include 'db.php';

$id = $_GET['id'];
$sql = "DELETE FROM mahasiswa WHERE id=$id";

if (mysqli_query($conn, $sql)) {
  header("Location: index.php?status=deleted");
  exit;
} else {
  header("Location: index.php?status=error");
}
?>
