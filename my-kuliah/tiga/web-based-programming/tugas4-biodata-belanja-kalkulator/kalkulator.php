<!-- 
    Nama: Haidar Khadafi
    NIM: 24040708033
    Tugas 4 PBN
-->

<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Kalkulator Sederhana</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background: linear-gradient(135deg, #ff0044ff, #ff8347ff);
            height: 100vh;
            margin: 0;
            display: flex;
            justify-content: center;
            align-items: center;
        }

        .kalkulator {
            background: rgba(255, 255, 255, 0.8);
            backdrop-filter: blur(20px);
            padding: 25px;
            border-radius: 20px;
            box-shadow: 8px 25px rgba(0,0,0,0.3);
            width: 320px;
        }

        input[type="text"] {
            width: 100%;
            height: 50px;
            font-size: 24px;
            text-align: right;
            margin-bottom: 15px;
            border-radius: 10px;
            border: none;
            background: rgba(255,255,255,0.9);
            outline: none;
        }

        .tombol {
            display: grid;
            grid-template-columns: repeat(4, 1fr);
            gap: 10px;
        }

        button {
            padding: 15px;
            font-size: 20px;
            border: none;
            border-radius: 10px;
            cursor: pointer;
            background-color: #f72414ff;
            color: white;
            transition: 0.25s;
        }

        button:hover {
            background-color: #ef8c30ff;
        }

        .operator {
            background-color: #f32144ff;
        }

        .operator:hover {
            background-color: #d73f53ff;
        }

        .clear {
            background-color: #364cff4f;
        }

        .clear:hover {
            background-color: #f24dd3ff;
        }

        .equal {
            background-color: #a60fffff;
            grid-column: span 2;
        }

        .equal:hover {
            background-color: #c663daff;
        }
    </style>
</head>
<body>

<div class="kalkulator">
    <form method="post">
        <input type="text" id="layar" name="layar" value="<?php echo isset($_POST['layar']) ? $_POST['layar'] : ''; ?>" readonly>
        <div class="tombol">
            <?php
            $tombol = ['7','8','9','/','4','5','6','*','1','2','3','-','0','.','=','+'];
            foreach ($tombol as $btn) {
                if ($btn == '=') {
                    echo "<button class='equal' name='tombol' value='='>=</button>";
                } elseif (in_array($btn, ['/','*','-','+'])) {
                    echo "<button class='operator' name='tombol' value='$btn'>$btn</button>";
                } else {
                    echo "<button name='tombol' value='$btn'>$btn</button>";
                }
            }
            ?>
            <button class="clear" name="tombol" value="C">C</button>
        </div>
    </form>
</div>

<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $layar = $_POST['layar'];
    $tombol = $_POST['tombol'];

    if ($tombol == '=') {
        if ($layar == '') {
            $layar = '';
        } else {
            try {
                $layar = eval("return $layar;");
            } catch (Throwable $e) {
                $layar = 'Error';
            }
        }
    } elseif ($tombol == 'C') {
        $layar = '';
    } else {
        $layar .= $tombol;
    }

    echo "<script>
        document.addEventListener('DOMContentLoaded', () => {
            document.getElementById('layar').value = '$layar';
        });
    </script>";
}
?>

<script>
    const display = document.getElementById('layar');

    document.addEventListener('keydown', (e) => {
        const key = e.key;

        if (!isNaN(key) || '+-*/.'.includes(key)) {
            display.value += key;
        } else if (key === 'Enter' || key === '=') {
            e.preventDefault();
            try {
                // Aman tapi hati-hati, eval cuma dipakai untuk demo
                display.value = eval(display.value);
            } catch (e) {
                display.value = 'Error';
            }
        } else if (key === 'Backspace') {
            display.value = display.value.slice(0, -1);
        } else if (key.toLowerCase() === 'c') {
            display.value = '';
        }
    });
</script>

</body>
</html>
