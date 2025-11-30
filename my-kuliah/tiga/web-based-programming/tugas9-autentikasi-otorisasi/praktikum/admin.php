<?php
require_once 'middleware/auth.php';
require_once 'database.php';
requireAdmin();

// Fetch all users
$stmt = $pdo->query("SELECT * FROM users ORDER BY created_at DESC");
$users = $stmt->fetchAll(PDO::FETCH_ASSOC);
?>
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard Admin</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <nav class="navbar">
        <a href="#" class="navbar-brand">Dashboard Admin</a>
        <div>
            <a href="logout.php" onclick="return confirm('Apakah Anda yakin ingin keluar?')">Keluar</a>
        </div>
    </nav>

    <div class="main-content">
        <div class="card">
            <h1>Daftar Pengguna</h1>
            <p>Berikut adalah daftar semua pengguna yang terdaftar di sistem.</p>
        </div>

        <div class="card mt-4">
            <table>
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Username</th>
                        <th>Role</th>
                        <th>Bergabung</th>
                    </tr>
                </thead>
                <tbody>
                    <?php if (empty($users)): ?>
                        <tr><td colspan="4" class="text-center">Tidak ada pengguna ditemukan.</td></tr>
                    <?php else: ?>
                        <?php foreach ($users as $user): ?>
                            <tr>
                                <td><?= htmlspecialchars($user['id']) ?></td>
                                <td><?= htmlspecialchars($user['username']) ?></td>
                                <td>
                                    <span style="padding: 0.25rem 0.5rem; border-radius: 4px; background: <?= $user['role'] === 'admin' ? '#fee2e2' : '#e0e7ff' ?>; color: <?= $user['role'] === 'admin' ? '#991b1b' : '#3730a3' ?>; font-size: 0.875rem;">
                                        <?= htmlspecialchars($user['role']) ?>
                                    </span>
                                </td>
                                <td><?= date('d F Y H:i', strtotime($user['created_at'])) ?></td>
                            </tr>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </tbody>
            </table>
        </div>
    </div>
</body>
</html>
