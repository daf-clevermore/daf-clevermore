<?php
require_once 'middleware/auth.php';
require_once 'database.php';
requireLogin();

// cegah admin mengakses dashboard user
if (isAdmin()) {
    header("Location: admin.php");
    exit();
}

// mengambil data user
$stmt = $pdo->prepare("SELECT * FROM users WHERE id = ?");
$stmt->execute([$_SESSION['user_id']]);
$user = $stmt->fetch(PDO::FETCH_ASSOC);

// format tanggal
$bergabung = date('d F Y', strtotime($user['created_at']));
?>
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard Mahasiswa</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <nav class="navbar">
        <a href="#" class="navbar-brand">Dashboard User</a>
        <div>
            <span class="mr-2" style="color: var(--text-muted);">Halo, <strong><?= htmlspecialchars($user['username']) ?></strong></span>
            <a href="logout.php" onclick="return confirm('Apakah Anda yakin ingin keluar?')">Keluar</a>
        </div>
    </nav>

    <div class="main-content">
        <div class="card">
            <h1>Selamat Datang!</h1>
            <p>Halo, <strong><?= htmlspecialchars($user['username']) ?></strong>. Anda berhasil masuk ke sistem.</p>
            <p class="mt-4" style="font-size: 0.9rem; color: var(--text-muted);">
                Akun Anda dibuat pada: <strong><?= $bergabung ?></strong>
            </p>
        </div>
    </div>
</body>
</html>
