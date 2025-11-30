<?php
require_once 'database.php';
require_once 'middleware/auth.php';

redirectIfLoggedIn();

$error = '';
$success = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'] ?? '';
    $password = $_POST['password'] ?? '';
    $role = $_POST['role'] ?? 'user'; // For testing, allowing role selection. In real app, usually defaults to user.

    if (empty($username) || empty($password)) {
        $error = "Username dan password wajib diisi.";
    } else {
        // Check if username exists
        $stmt = $pdo->prepare("SELECT id FROM users WHERE username = ?");
        $stmt->execute([$username]);
        if ($stmt->rowCount() > 0) {
            $error = "Username sudah terdaftar.";
        } else {
            $hashedPassword = password_hash($password, PASSWORD_DEFAULT);
            $stmt = $pdo->prepare("INSERT INTO users (username, password, role) VALUES (?, ?, ?)");
            if ($stmt->execute([$username, $hashedPassword, $role])) {
                $success = "Registrasi berhasil! Anda sekarang dapat <a href='login.php'>masuk</a>.";
            } else {
                $error = "Registrasi gagal.";
            }
        }
    }
}
?>
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Daftar</title>
    <link rel="stylesheet" href="style.css">
</head>
<body class="auth-page">
    <div class="container">
        <h2 class="text-center mb-4">Daftar</h2>
        
        <?php if ($error): ?>
            <div class="alert alert-error"><?= htmlspecialchars($error) ?></div>
        <?php endif; ?>
        <?php if ($success): ?>
            <div class="alert alert-success"><?= $success ?></div>
        <?php endif; ?>

        <form method="POST">
            <div class="form-group">
                <input type="text" name="username" placeholder="Username" required>
            </div>
            <div class="form-group">
                <input type="password" name="password" placeholder="Password" required minlength="8">
            </div>
            <div class="form-group">
                <select name="role">
                    <option value="user">User (Mahasiswa)</option>
                    <option value="admin">Admin</option>
                </select>
            </div>
            <button type="submit">Daftar</button>
        </form>
        
        <p class="text-center mt-4">
            Sudah punya akun? <a href="login.php">Masuk</a>
        </p>
    </div>
</body>
</html>
