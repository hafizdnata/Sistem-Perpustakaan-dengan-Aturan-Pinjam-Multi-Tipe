# Sistem-Perpustakaan-dengan-Aturan-Pinjam-Multi-Tipe
=====================================================

Proyek ini merupakan sistem manajemen perpustakaan berbasis C++ yang menampilkan penerapan prinsip Object-Oriented Programming (OOP), termasuk pewarisan, overriding, overloading, dan penggunaan std::unique_ptr untuk pengelolaan memori yang aman.  
Sistem ini memungkinkan pengelolaan item perpustakaan (buku, majalah, DVD), anggota, serta katalog koleksi melalui antarmuka berbasis teks.  
Proyek ini dikembangkan secara kolaboratif dengan pembagian tanggung jawab yang jelas agar setiap anggota kelompok berkontribusi dalam aspek berbeda dari sistem.

-----------------------------------------------------
Pembagian Tugas Kelompok
-----------------------------------------------------

+-------------+-------------------------------------------------------------+
| Anggota     | Tugas dan Tanggung Jawab                                   |
+-------------+-------------------------------------------------------------+
| hafizh, Khansa| Arsitek dan core Item classes (Item, Book, Magazine, DVD,  |
|             | clone, operator).                                          |
+-------------+-------------------------------------------------------------+
| Dionisius   | Member management dan level rules (Member class,           |
|             | borrow/return overload).                                   |
+-------------+-------------------------------------------------------------+
|Octavia,Khansa| Catalogue dan persistence (search, sort, clone koleksi,    |
|             | save/load sederhana).                                      |
+-------------+-------------------------------------------------------------+
|      Judhis | CLI / orchestrator (menu, input handling, integrasi).      |
+-------------+-------------------------------------------------------------+

-----------------------------------------------------
Cara Kompilasi (Universal)
-----------------------------------------------------

Proyek ini dapat dijalankan pada Windows, Linux, dan macOS menggunakan compiler C++17.  
Pastikan file utama bernama `main.cpp` (atau sesuaikan dengan nama file program utama Anda).

1. Windows  
   Buka Command Prompt, lalu jalankan perintah:  
   g++ -std=c++17 -O2 -o library_app.exe main.cpp

2. Linux  
   Buka Terminal, lalu jalankan perintah:  
   g++ -std=c++17 -O2 -o library_app main.cpp

3. macOS  
   Gunakan Terminal, lalu jalankan perintah:  
   clang++ -std=c++17 -O2 -o library_app main.cpp

-----------------------------------------------------
Cara Menjalankan Program
-----------------------------------------------------

Setelah dikompilasi, jalankan program sesuai sistem operasi Anda.

- Windows:  
  library_app.exe  

- Linux / macOS:  
  ./library_app  

Program akan menampilkan antarmuka CLI untuk mengelola item perpustakaan, anggota, dan transaksi peminjaman.

-----------------------------------------------------
Contoh File Data
-----------------------------------------------------

BOOK: Clean Code | Robert C. Martin | 9780132350884  
MAGAZINE: AI Monthly | Vol.5 | 2025  
DVD: Robotics Documentary | 2023  

File ini digunakan untuk menyimpan koleksi item perpustakaan yang dimuat saat program dijalankan.

-----------------------------------------------------
Contoh Output Program
-----------------------------------------------------

===== Library Management System =====
1. Tambah Item Baru
2. Lihat Koleksi
3. Tambah Anggota
4. Pinjam Item
5. Kembalikan Item
6. Simpan & Keluar
Pilih menu: 1

Masukkan jenis item (Book/Magazine/DVD): Book
Judul: Clean Code
Penulis: Robert C. Martin
ISBN: 9780132350884
Item berhasil ditambahkan!

-----------------------------------------------------
Deskripsi Singkat
-----------------------------------------------------

Kelas `Item` menjadi dasar seluruh jenis koleksi perpustakaan dengan atribut umum seperti ID, judul, dan status ketersediaan.  
Kelas turunan seperti `Book`, `Magazine`, dan `DVD` menambahkan atribut serta perilaku spesifik.  
Kelas `Member` mengatur data anggota, hak pinjam, serta proses peminjaman dan pengembalian.  
Kelas `Catalogue` bertanggung jawab untuk penyimpanan koleksi, pencarian, pengurutan, dan penyimpanan ke file.  
CLI mengatur alur interaksi pengguna dan integrasi semua modul di atas.

-----------------------------------------------------
Konsep OOP yang Diterapkan
-----------------------------------------------------

- Abstraction & Inheritance : Item sebagai kelas dasar abstrak.  
- Polymorphism              : Fungsi virtual clone() dan display() diimplementasikan di setiap kelas turunan.  
- Overloading & Overriding  : Operator dan fungsi dengan perilaku khusus di tiap kelas.  
- Encapsulation             : Atribut privat dengan akses melalui getter/setter.  
- Smart Pointer             : Menggunakan std::unique_ptr untuk manajemen memori otomatis.  

-----------------------------------------------------
Struktur Folder (Opsional)
-----------------------------------------------------

library_project/
│
├── src/
│   ├── item.h
│   ├── book.h
│   ├── magazine.h
│   ├── dvd.h
│   ├── member.h
│   ├── catalogue.h
│   └── main.cpp
│
├── data/
│   └── library_data.txt
│
└── README.txt


TEKNIK ROBOTIKA DAN KECERDASAN BUATAN, UNIVERSITAS AIRLANGGA 
-----------------------------------------------------
