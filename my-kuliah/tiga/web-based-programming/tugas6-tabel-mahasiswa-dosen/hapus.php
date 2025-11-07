<?php
include 'koneksi.php';
$table = $_GET['table'];
$id = $_GET['id'];
mysqli_query($koneksi, "DELETE FROM $table WHERE id=$id");
header("Location: index.php?table=$table");
?>
