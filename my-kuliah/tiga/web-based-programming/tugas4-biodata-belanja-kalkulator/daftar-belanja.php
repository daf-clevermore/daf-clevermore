<!--    Nama: THORAS FAADIHILAH RAHMAN
        NIM : 24040700041   
        Tugas 4 PBW         -->

<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Daftar Belanja</title>
    <style>
        body {
            font-family: Arial, sans-serif;
           background: linear-gradient(135deg, #1e9d9bff, #daf843ff);
            height: 100vh;
            margin: 0;
            display: flex;
            justify-content: center;
            align-items: center;
        }

        .container {
            background: rgba(255, 255, 255, 0.8);
            backdrop-filter: blur(15px);
            padding: 30px;
            border-radius: 20px;
            width: 500px;
            text-align: center;
            box-shadow: 0 8px 25px rgba(0, 0, 0, 0.3);
        }

        h2 {
            color: #000;
            margin-bottom: 15px;
        }

        form {
            margin-bottom: 20px;
        }

        input[type="text"], input[type="number"] {
            width: 80%;
            padding: 10px;
            margin: 8px 0;
            border: none;
            border-radius: 8px;
            outline: none;
            text-align: center;
        }

        input[type="submit"] {
            background-color: #f27414ff;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 8px;
            cursor: pointer;
            font-weight: bold;
        }

        input[type="submit"]:hover {
            background-color: #ef8c30ff;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            background: rgba(255,255,255,0.9);
            border-radius: 10px;
            overflow: hidden;
        }

        th, td {
            padding: 10px;
            border-bottom: 1px solid #ddd;
        }

        th {
            background-color: #f32144ff;
            color: white;
        }

        .total {
            font-weight: bold;
        }
    </style>
</head>
<body>

<div class="container">
    <h2>Daftar Belanja</h2>

    <form method="post">
        <input type="text" name="nama" placeholder="Nama Barang" required><br>
        <input type="number" name="harga" placeholder="Harga (Rp)" required><br>
        <input type="number" name="jumlah" placeholder="Jumlah" required><br>
        <input type="submit" name="tambah" value="Tambahkan">
    </form>

    <?php
    session_start();
    if (!isset($_SESSION['belanja'])) {
        $_SESSION['belanja'] = [];
    }

    if (isset($_POST['tambah'])) {
        $nama = $_POST['nama'];
        $harga = $_POST['harga'];
        $jumlah = $_POST['jumlah'];

        $_SESSION['belanja'][] = [
            "nama" => $nama,
            "harga" => $harga,
            "jumlah" => $jumlah
        ];
    }

    if (isset($_POST['reset'])) {
        session_destroy();
        header("Location: " . $_SERVER['PHP_SELF']);
        exit;
    }

    if (!empty($_SESSION['belanja'])) {
        echo "<table>";
        echo "<tr>
                <th>No</th>
                <th>Nama Barang</th>
                <th>Harga (Rp)</th>
                <th>Jumlah</th>
                <th>Subtotal (Rp)</th>
              </tr>";

        $no = 1;
        $total = 0;

        foreach ($_SESSION['belanja'] as $item) {
            $subtotal = $item["harga"] * $item["jumlah"];
            $total += $subtotal;

            echo "<tr>
                    <td>$no</td>
                    <td>{$item['nama']}</td>
                    <td>" . number_format($item['harga'], 0, ',', '.') . "</td>
                    <td>{$item['jumlah']}</td>
                    <td>" . number_format($subtotal, 0, ',', '.') . "</td>
                  </tr>";
            $no++;
        }

        echo "<tr class='total'>
                <td colspan='4'>Total Belanja</td>
                <td>Rp " . number_format($total, 0, ',', '.') . "</td>
              </tr>";
        echo "</table>";

        echo '<form method="post" style="margin-top: 15px;">
                <input type="submit" name="reset" value="Reset Daftar" style="background-color:#f44336;">
              </form>';
    } else {
        echo "<p style='color:black;'>Belum ada barang dalam daftar.</p>";
    }
    ?>
</div>

</body>
</html>