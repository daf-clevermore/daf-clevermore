<!-- delete.php -->

<?php
include 'db.php';
$id = $_GET['id'];

mysqli_query($conn, "DELETE FROM buku WHERE id=$id");

echo "<script>window.location='index.php';</script>";
?>
