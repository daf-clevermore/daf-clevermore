<?php
require_once 'middleware/auth.php';
session_destroy();
header("Location: login.php");
exit();
?>
