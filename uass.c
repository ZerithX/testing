#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 50
#define DATA_FILE "books.dat"

// Struktur untuk menyimpan data buku
typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    float price;
} Book;

// Deklarasi variabel global
Book books[MAX_BOOKS];
int bookCount = 0;

// Fungsi untuk memuat buku dari file
void loadBooks() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        // Jika file tidak ada, anggap sebagai pertama kali menjalankan program
        printf("Data buku tidak ditemukan. Memulai dengan daftar kosong.\n");
        return;
    }
    fread(&bookCount, sizeof(int), 1, file);
    fread(books, sizeof(Book), bookCount, file);
    fclose(file);
    printf("Data buku berhasil dimuat (%d buku).\n", bookCount);
}

// Fungsi untuk menyimpan buku ke file
void saveBooks() {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        printf("Gagal menyimpan data buku.\n");
        return;
    }
    fwrite(&bookCount, sizeof(int), 1, file);
    fwrite(books, sizeof(Book), bookCount, file);
    fclose(file);
    printf("Data buku berhasil disimpan.\n");
}

// Fungsi untuk menampilkan daftar buku
void displayBooks() {
    if (bookCount == 0) {
        printf("Tidak ada buku dalam katalog.\n");
        return;
    }
    printf("\nDaftar Buku:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d. Judul: %s, Penulis: %s, Harga: %.2f\n", i + 1, books[i].title, books[i].author, books[i].price);
    }
}

// Fungsi untuk menambah buku baru
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Katalog buku penuh.\n");
        return;
    }
    printf("\nMasukkan detail buku baru:\n");
    printf("Judul: ");
    getchar(); // Membersihkan buffer input
    fgets(books[bookCount].title, TITLE_LENGTH, stdin);
    strtok(books[bookCount].title, "\n"); // Menghapus newline

    printf("Penulis: ");
    fgets(books[bookCount].author, AUTHOR_LENGTH, stdin);
    strtok(books[bookCount].author, "\n");

    printf("Harga: ");
    scanf("%f", &books[bookCount].price);

    bookCount++;
    printf("Buku berhasil ditambahkan!\n");

    // Simpan data buku setiap kali ada perubahan
    saveBooks();
}

// Fungsi untuk mencari buku berdasarkan judul
void searchBook() {
    char searchTitle[TITLE_LENGTH];
    printf("\nMasukkan judul buku yang ingin dicari: ");
    getchar(); // Membersihkan buffer input
    fgets(searchTitle, TITLE_LENGTH, stdin);
    strtok(searchTitle, "\n");

    printf("\nHasil pencarian:\n");
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, searchTitle)) {
            printf("%d. Judul: %s, Penulis: %s, Harga: %.2f\n", i + 1, books[i].title, books[i].author, books[i].price);
            found = 1;
        }
    }
    if (!found) {
        printf("Buku dengan judul '%s' tidak ditemukan.\n", searchTitle);
    }
}

// Fungsi utama
int main() {
    int choice;

    // Muat data buku dari file
    loadBooks();

    do {
        printf("\n=== Aplikasi Toko Buku ===\n");
        printf("1. Tampilkan Daftar Buku\n");
        printf("2. Tambah Buku Baru\n");
        printf("3. Cari Buku\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBooks();
                break;
            case 2:
                addBook();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                printf("Keluar dari aplikasi. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 4);

    // Simpan data buku sebelum keluar
    saveBooks();

    return 0;
}

