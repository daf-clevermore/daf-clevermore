document.addEventListener("DOMContentLoaded", () => {
  const loadBtn = document.getElementById("loadBtn");
  const userList = document.getElementById("userList");
  const clearBtn = document.getElementById("clearBtn");

  loadBtn.addEventListener("click", () => {
    loadBtn.innerText = "Memuat...";
    loadBtn.disabled = true;

    fetch("users.json")
      .then(response => {
        if (!response.ok) throw new Error("Gagal mengambil data!");
        return response.json();
      })
      .then(users => {
        userList.innerHTML = "";
        users.forEach(user => {
          const div = document.createElement("div");
          div.className = "user-item";
          div.innerHTML = `<strong>${user.nama}</strong><br><small>${user.email}</small><br><small>${user.telepon}</small>`;

          div.addEventListener("click", () => {
            document.querySelectorAll(".user-item").forEach(el => el.classList.remove("highlight"));
            div.classList.add("highlight");
          });

          div.addEventListener("mouseover", () => {
            div.title = "Klik untuk memilih";
          });

          userList.appendChild(div);
        });
        loadBtn.innerText = "Data Berhasil Dimuat";
        loadBtn.disabled = false;
      })
      .catch(error => {
        userList.innerHTML = `<div class="alert alert-danger">${error.message}</div>`;
        loadBtn.innerText = "Coba Lagi";
        loadBtn.disabled = false;
      });
  });
  clearBtn.addEventListener("click", () => {
    userList.innerHTML = "";
    loadBtn.disabled = false;
    loadBtn.innerText = "Muat Data Pengguna";
  });
});
