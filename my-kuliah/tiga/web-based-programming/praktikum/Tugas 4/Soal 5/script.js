// Ambil elemen-elemen DOM
const activityInput = document.getElementById('activityInput');
const addButton = document.getElementById('addButton');
const activityList = document.getElementById('activityList');
const itemCount = document.getElementById('itemCount');

// Key untuk LocalStorage
const storageKey = 'activities';

// Fungsi untuk menyimpan data ke LocalStorage
function saveToLocalStorage(activities) {
    localStorage.setItem(storageKey, JSON.stringify(activities));
}

// Fungsi untuk memuat data dari LocalStorage
function loadFromLocalStorage() {
    const data = localStorage.getItem(storageKey);
    return data ? JSON.parse(data) : [];
}

// Fungsi untuk mendapatkan semua aktivitas dari DOM
function getActivitiesFromDOM() {
    const items = activityList.querySelectorAll('.activityItem');
    const activities = [];
    items.forEach(item => {
        const text = item.querySelector('.activityText').textContent;
        activities.push(text);
    });
    return activities;
}

// Fungsi untuk update counter
function updateCounter() {
    const items = activityList.querySelectorAll('.activityItem');
    const count = items.length;
    itemCount.textContent = `${count} aktivitas`;
}

// Fungsi untuk menampilkan pesan "List kosong"
function showEmptyMessage() {
    const emptyMessage = document.createElement('li');
    emptyMessage.className = 'emptyMessage';
    emptyMessage.textContent = 'List kosong';
    activityList.appendChild(emptyMessage);
}

// Fungsi untuk menghapus pesan "List kosong"
function removeEmptyMessage() {
    const emptyMessage = activityList.querySelector('.emptyMessage');
    if (emptyMessage) {
        emptyMessage.remove();
    }
}

// Fungsi untuk membuat elemen aktivitas
function createActivityElement(activityText) {
    // Buat elemen list item baru
    const listItem = document.createElement('li');
    listItem.className = 'activityItem';

    // Buat elemen untuk teks aktivitas
    const textSpan = document.createElement('span');
    textSpan.className = 'activityText';
    textSpan.textContent = activityText;

    // Buat tombol hapus
    const deleteBtn = document.createElement('button');
    deleteBtn.className = 'deleteButton';
    deleteBtn.textContent = 'Hapus';

    // Event listener untuk tombol hapus
    deleteBtn.addEventListener('click', function () {
        deleteActivity(listItem);
    });

    // Tambahkan elemen ke list item
    listItem.appendChild(textSpan);
    listItem.appendChild(deleteBtn);

    return listItem;
}

// Fungsi untuk menambah aktivitas
function addActivity() {
    const activityText = activityInput.value.trim();

    // Validasi input tidak kosong
    if (activityText === '') {
        activityInput.focus();
        return;
    }

    // Hapus pesan "List kosong" jika ada
    removeEmptyMessage();

    // Buat dan tambahkan elemen aktivitas
    const listItem = createActivityElement(activityText);
    activityList.appendChild(listItem);

    // Kosongkan input dan focus kembali
    activityInput.value = '';
    activityInput.focus();

    // Update counter
    updateCounter();

    // Simpan ke LocalStorage
    const activities = getActivitiesFromDOM();
    saveToLocalStorage(activities);
}

// Fungsi untuk menghapus aktivitas
function deleteActivity(listItem) {
    // Hapus item dari list
    listItem.remove();

    // Cek apakah list kosong
    const items = activityList.querySelectorAll('.activityItem');
    if (items.length === 0) {
        showEmptyMessage();
    }

    // Update counter
    updateCounter();

    // Simpan ke LocalStorage
    const activities = getActivitiesFromDOM();
    saveToLocalStorage(activities);
}

// Fungsi untuk memuat aktivitas dari LocalStorage
function loadActivities() {
    const activities = loadFromLocalStorage();

    if (activities.length === 0) {
        showEmptyMessage();
    } else {
        removeEmptyMessage();
        activities.forEach(activityText => {
            const listItem = createActivityElement(activityText);
            activityList.appendChild(listItem);
        });
    }

    updateCounter();
}

// Event listener untuk tombol tambah
addButton.addEventListener('click', addActivity);

// Event listener untuk Enter key pada input
activityInput.addEventListener('keypress', function (event) {
    if (event.key === 'Enter') {
        addActivity();
    }
});

// Muat data saat halaman dimuat
document.addEventListener('DOMContentLoaded', function () {
    loadActivities();
});
