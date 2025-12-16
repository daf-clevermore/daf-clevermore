// Mendapatkan elemen-elemen form
const contactForm = document.getElementById('contactForm');
const nameInput = document.getElementById('nameInput');
const emailInput = document.getElementById('emailInput');
const messageInput = document.getElementById('messageInput');
const errorMessage = document.getElementById('errorMessage');
const resultBox = document.getElementById('resultBox');
const resultName = document.getElementById('resultName');
const resultEmail = document.getElementById('resultEmail');
const resultMessage = document.getElementById('resultMessage');
const closeResult = document.getElementById('closeResult');

// Fungsi untuk menampilkan error
function showError(message) {
    errorMessage.textContent = message;
    errorMessage.classList.add('show');

    // Hapus error setelah 5 detik
    setTimeout(() => {
        errorMessage.classList.remove('show');
    }, 5000);
}

// Fungsi untuk menyembunyikan error
function hideError() {
    errorMessage.classList.remove('show');
}

// Fungsi validasi email
function validateEmail(email) {
    // Email harus mengandung "@" dan "."
    return email.includes('@') && email.includes('.');
}

// Fungsi untuk menampilkan hasil
function showResult(name, email, message) {
    resultName.textContent = name;
    resultEmail.textContent = email;
    resultMessage.textContent = message;
    resultBox.classList.remove('hidden');

    // Scroll ke hasil
    resultBox.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
}

// Fungsi untuk mereset form
function resetForm() {
    contactForm.reset();
    hideError();
}

// Event listener untuk submit form
contactForm.addEventListener('submit', function (event) {
    event.preventDefault();

    // Ambil nilai dari input
    const name = nameInput.value.trim();
    const email = emailInput.value.trim();
    const message = messageInput.value.trim();

    // Validasi nama tidak boleh kosong
    if (name === '') {
        showError('❌ Nama tidak boleh kosong!');
        nameInput.focus();
        return;
    }

    // Validasi email harus mengandung "@" dan "."
    if (!validateEmail(email)) {
        showError('❌ Email harus mengandung "@" dan "."');
        emailInput.focus();
        return;
    }

    // Validasi pesan minimal 10 karakter
    if (message.length < 10) {
        showError('❌ Pesan minimal harus 10 karakter!');
        messageInput.focus();
        return;
    }

    // Jika semua validasi berhasil
    hideError();
    showResult(name, email, message);
    resetForm();
});

// Event listener untuk tombol close pada result box
closeResult.addEventListener('click', function () {
    resultBox.classList.add('hidden');
});

// Hapus error message saat user mulai mengetik
nameInput.addEventListener('input', hideError);
emailInput.addEventListener('input', hideError);
messageInput.addEventListener('input', hideError);

// Animasi smooth untuk input focus
const inputs = document.querySelectorAll('input, textarea');
inputs.forEach(input => {
    input.addEventListener('focus', function () {
        this.parentElement.querySelector('label').style.color = 'var(--primaryColor)';
    });

    input.addEventListener('blur', function () {
        this.parentElement.querySelector('label').style.color = 'var(--textPrimary)';
    });
});
