<!-- 
    Nama: Haidar Khadafi
    NIM: 24040700033
    Tugas 5 PBW

    index.php
-->

<?php
session_start();

$theme = isset($_COOKIE['theme']) ? $_COOKIE['theme'] : 'light';

$bg_gradient = $theme === 'dark'
    ? 'linear-gradient(135deg, #1a1c24, #2a2f3b)'
    : 'linear-gradient(135deg, #dae1f3, #f3f5fa)';
?>
<!DOCTYPE html>
<html lang="id">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Form Biodata</title>

    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            display: flex;
            justify-content: center;
            align-items: flex-start;
            min-height: 100vh;
            padding: 60px 0;
            background:
                <?= $bg_gradient ?>
            ;
            color:
                <?= $theme === 'dark' ? '#f1f1f1' : '#222' ?>
            ;
            margin: 0;
        }

        .container {
            background:
                <?= $theme === 'dark'
                    ? 'rgba(38, 41, 54, 0.9)'
                    : 'rgba(255, 255, 255, 0.95)' ?>
            ;
            backdrop-filter: blur(12px);
            padding: 35px 40px;
            border-radius: 25px;
            box-shadow: 0 8px 24px rgba(0, 0, 0, 0.15);
            width: 420px;
            border: 1px solid
                <?= $theme === 'dark' ? '#444' : '#ccc' ?>
            ;
        }

        h2 {
            text-align: center;
            color:
                <?= $theme === 'dark' ? '#f1f1f1' : '#2a2a2a' ?>
            ;
        }

        label {
            font-weight: 600;
            color:
                <?= $theme === 'dark' ? '#ddd' : '#222' ?>
            ;
        }

        input[type="text"], input[type="email"], 
        input[type="date"],
        select {
            width: 100%;
            padding: 10px 12px;
            margin: 8px 0 18px 0;
            border: 1px solid
                <?= $theme === 'dark' ? '#666' : '#bbb' ?>
            ;
            border-radius: 6px;
            font-size: 15px;
            background:
                <?= $theme === 'dark' ? '#2d2d2d' : '#fff' ?>
            ;
            color:
                <?= $theme === 'dark' ? '#f1f1f1' : '#222' ?>
            ;
        }

        input[type="submit"] {
            width: 100%;
            color: #fff;
            border: none;
            padding: 12px;
            font-size: 17px;
            font-weight: 600;
            border-radius: 8px;
            cursor: pointer;
            transition: background-color 0.3s, transform 0.1s;
            margin-top: 10px;
            background-color:
                <?= $theme === 'dark' ? '#3e7bfa' : '#3f51b5' ?>
            ;
        }

        input[type="submit"]:hover {
            background-color:
                <?= $theme === 'dark' ? '#6289ff' : '#5f6ff0' ?>
            ;
            transform: translateY(-2px);
        }

        hr {
            border: none;
            border-top: 1px solid
                <?= $theme === 'dark' ? '#444' : '#ccc' ?>
            ;
            margin: 25px 0;
        }
    </style>
</head>

<body>
    <div class="container">
        <h2>Input Biodata</h2>

        <!-- FORM INPUT MODE -->
        <form method="post" action="proses.php">
            <label for="nama">Nama Lengkap:</label>
            <input type="text" name="nama" required>

            <label for="email">Email:</label>
            <input type="email" name="email" required>

            <label for="tanggal">Tanggal Lahir:</label>
            <input type="date" name="tanggal" required>

            <label for="kelamin">Jenis Kelamin:</label>
            <input type="radio" name="kelamin" value="Laki-laki" required> Laki-Laki
            <input type="radio" name="kelamin" value="Perempuan" required> Perempuan<br><br>

            <label for="hobi">Hobi:</label>
            <input type="text" name="hobi" required>

            <input type="submit" name="submit" value="Simpan Data">
        </form>

        <hr>
        <form method="post" action="proses.php">
            <label for="theme">Pilih Tema:</label>
            <select name="theme" onchange="this.form.submit()">
                <option value="light" <?= $theme === 'light' ? 'selected' : '' ?>>Terang</option>
                <option value="dark" <?= $theme === 'dark' ? 'selected' : '' ?>>Gelap</option>
            </select>
        </form>
    </div>
</body>

</html>