     <?php
     $servername = "localhost";
     $username = "root";
     $password = "";
     $dbname = "registrasi";

     if ($_SERVER["REQUEST_METHOD"] == "POST") {
         $nama = $_POST['nama'];
         $email = $_POST['email'];
         $pass = $_POST['password'];

         if (empty($nama) || empty($email) || empty($pass)) {
             die("Semua field harus diisi!");
         }

         $hashed_pass = password_hash($pass, PASSWORD_DEFAULT);

         try {
             $pdo = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
             $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

             $stmt = $pdo->prepare("INSERT INTO users (nama, email, password) VALUES (?, ?, ?)");
             $stmt->execute([$nama, $email, $hashed_pass]);

             echo "Registrasi berhasil! <a href='index.html'>Kembali ke form</a>";

         } catch(PDOException $e) {
             if ($e->getCode() == 23000) {
                 echo "Email sudah terdaftar! Gunakan email lain.";
             } else {
                 echo "Error: " . $e->getMessage();
             }
         }
     } else {
         header("Location: index.html");
         exit();
     }
     ?>
     