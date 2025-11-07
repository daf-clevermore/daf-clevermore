<!-- 
    Nama: Haidar Khadafi
    NIM: 24040700033
    Tugas 4 PBW
-->

<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Form Biodata</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background: linear-gradient(135deg, #ff0044ff, #f8437fff);
            background-size: cover;
        }

        .container {
            background: rgba(255, 255, 255, 0.6);
            backdrop-filter: blur(15px);
            padding: 25px 30px;
            border-radius: 20px;
            box-shadow: 0 4px 15px rgba(0,0,0,0.1);
            width: 400px;
        }

        h2 {
            text-align: center;
            color: #000;
        }

        label {
            font-weight: bold;
        }

        input[type="text"], input[type="date"] {
            width: 100%;
            padding: 8px;
            margin: 6px 0 15px 0;
            border: 1px solid #ccc;
            border-radius: 5px;
        }

        input[type="submit"], button[type="reset"] {
            width: 48%;
            color: white;
            border: none;
            padding: 10px;
            font-size: 16px;
            border-radius: 5px;
            cursor: pointer;
            transition: .25s;
        }

        input[type="submit"] {
            background-color: #f72414ff;
        }

        input[type="submit"]:hover {
            background-color: #ef8c30ff;
        }

        button[type="reset"] {
            background-color: #364cff4f;
        }

        button[type="reset"]:hover {
            background-color: #f24dd3ff;
        }

        .btn-group {
            display: flex;
            justify-content: space-between;
        }

        .biodata {
            margin-top: 20px;
            padding: 15px;
            background-color: #f8f8f8;
            border-radius: 8px;
            border: 1px solid #dddd;
        }

        .biodata h3 {
            text-align: center;
        }
    </style>
</head>
<body>

<div class="container">
    <h2>Biodata</h2>
    <form method="post" action="">
        <label for="nama">Nama Lengkap:</label>
        <input type="text" name="nama" required>

        <label for="tempat">Tempat Lahir:</label>
        <input type="text" name="tempat" required>

        <label for="tanggal">Tanggal Lahir:</label>
        <input type="date" name="tanggal" required>

        <label for="kelamin">Jenis Kelamin:</label>
        <input type="radio" name="kelamin" value="Laki-laki" required> Laki-Laki
        <input type="radio" name="kelamin" value="Perempuan" required> Perempuan<br><br>

        <label for="hobi">Hobi:</label>
        <input type="text" name="hobi" required>

        <div class="btn-group">
            <input type="submit" name="submit" value="Simpan">
            <button type="reset">Reset</button>
        </div>
    </form>

    <?php
    session_start();

    if (isset($_POST['submit'])) {
        $nama = htmlspecialchars($_POST['nama']);
        $tempat = htmlspecialchars($_POST['tempat']);
        $tanggal = htmlspecialchars($_POST['tanggal']);
        $kelamin = htmlspecialchars($_POST['kelamin']);
        $hobi = htmlspecialchars($_POST['hobi']);

        // simpan data ke session
        $_SESSION['biodata'] = compact('nama', 'tempat', 'tanggal', 'kelamin', 'hobi');

        // redirect biar POST hilang
        header("Location: " . $_SERVER['PHP_SELF']);
        exit;
    }

    if (isset($_SESSION['biodata'])) {
        $b = $_SESSION['biodata'];
        echo "<div class='biodata'>";
        echo "<h3>Biodata Anda</h3>";
        echo "<p><strong>Nama Lengkap:</strong> {$b['nama']}</p>";
        echo "<p><strong>Tempat Lahir:</strong> {$b['tempat']}</p>";
        echo "<p><strong>Tanggal Lahir:</strong> {$b['tanggal']}</p>";
        echo "<p><strong>Jenis Kelamin:</strong> {$b['kelamin']}</p>";
        echo "<p><strong>Hobi:</strong> {$b['hobi']}</p>";
        echo "</div>";
    }
    ?>

    <script>
        // Bersihkan biodata saat tombol Reset diklik
        document.querySelector('button[type="reset"]').addEventListener('click', () => {
            fetch(window.location.href, { 
                method: 'POST', 
                body: new URLSearchParams({ clear: 1 }) 
            });
            document.querySelector('.biodata')?.remove();
        });
    </script>

    <?php
    // Hapus session biodata jika ada request clear
    if (isset($_POST['clear'])) {
        unset($_SESSION['biodata']);
        exit;
    }
    ?>
</div>

</body>
</html>
