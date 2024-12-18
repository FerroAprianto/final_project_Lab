#include <stdio.h>
#include <string.h>
#include <time.h>

#define ANSI_BLUE "\x1b[34m" //mengubah warna teks menjadi biru
#define ANSI_RESET "\x1b[0m" //untuk mengembalikan teks ke warna default terminal


#include "text.c"

// Struct Penjualan
typedef struct {
    char tanggal[11];
    char nama_pelanggan[50];
    char jenis_tiket[20];
    char nama_event[50];
    int jumlah_tiket;
    float harga_tiket;
    float total_pembayaran;
} Penjualan;

// Struct StokTiket
typedef struct {
    char nama_event[50];
    char jenis_tiket[20];
    int stok_tiket;
} StokTiket;

// Global array untuk stok tiket
#define MAX_EVENTS 6
StokTiket stok[MAX_EVENTS];

// Fungsi untuk menyimpan data stok tiket ke file
void simpanStokTiket() {
    FILE *file = fopen("stok_tiket.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan stok tiket!\n");
        return;
    }

    for (int i = 0; i < MAX_EVENTS; i++) {
        fprintf(file, "%s,%s,%d\n", 
                stok[i].nama_event, 
                stok[i].jenis_tiket, 
                stok[i].stok_tiket);
    }
    fclose(file);
    printf("Data stok tiket berhasil disimpan!\n");
}

// Fungsi untuk membaca data stok tiket dari file
void bacaStokTiket() {
    FILE *file = fopen("stok_tiket.txt", "r");
    if (file == NULL) {
        // Jika file tidak ada, gunakan data default
        stok[0] = (StokTiket){"Beni Rockstars", "VIP", 100};
        stok[1] = (StokTiket){"Beni Rockstars", "Regular", 100};
        stok[2] = (StokTiket){"Sheren Koplo", "VIP", 100};
        stok[3] = (StokTiket){"Sheren Koplo", "Regular", 100};
        stok[4] = (StokTiket){"Turen Bergoyang", "VIP", 100};
        stok[5] = (StokTiket){"Turen Bergoyang", "Regular", 100};
        return;
    }

    int count = 0;
    while (fscanf(file, "%49[^,],%19[^,],%d\n", 
                  stok[count].nama_event, 
                  stok[count].jenis_tiket, 
                  &stok[count].stok_tiket) != EOF) {
        count++;
        if (count >= MAX_EVENTS) break;
    }
    fclose(file);
}

// Fungsi untuk menyimpan data penjualan ke file
void simpanData(Penjualan data[], int n) {
    FILE *file = fopen("sales.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%s,%s,%s,%d,%.2f,%.2f\n",
                data[i].tanggal,
                data[i].nama_pelanggan,
                data[i].jenis_tiket,
                data[i].nama_event,
                data[i].jumlah_tiket,
                data[i].harga_tiket,
                data[i].total_pembayaran);
    }
    fclose(file);
    printf("Data penjualan berhasil disimpan!\n");
}

// Membaca data dari file
int bacaData(Penjualan data[]) {
    FILE *file = fopen("sales.txt", "r");
    if (file == NULL) {
        printf("File tidak ditemukan atau belum ada data!\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%10[^,],%49[^,],%19[^,],%49[^,],%d,%f,%f\n",
                  data[count].tanggal,
                  data[count].nama_pelanggan,
                  data[count].jenis_tiket,
                  data[count].nama_event,
                  &data[count].jumlah_tiket,
                  &data[count].harga_tiket,
                  &data[count].total_pembayaran) != EOF) {
        count++;
        if (count >= 100) break; // Prevent buffer overflow
    }
    fclose(file);
    return count;
}

// Menampilkan data penjualan
void tampilkanData(Penjualan data[], int n) {
    if (n == 0) {
        printf("Tidak ada data penjualan.\n");
        return;
    }
    
    printf("=================================================================================================================\n");
    printf("| Tanggal      | Nama Pelanggan          | Jenis Tiket     | Nama Event           | Jumlah | Harga    | Total    |\n");
    printf("=================================================================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("| %-12s | %-22s | %-15s | %-20s | %-6d | %-8.2f | %-8.2f |\n",
               data[i].tanggal, 
               data[i].nama_pelanggan, 
               data[i].jenis_tiket, 
               data[i].nama_event,
               data[i].jumlah_tiket, 
               data[i].harga_tiket, 
               data[i].total_pembayaran);
    }
    printf("=================================================================================================================\n");
}

// Sorting data berdasarkan total pembayaran (descending)
void sortData(Penjualan data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (data[i].total_pembayaran < data[j].total_pembayaran) {
                Penjualan temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    printf("Data berhasil diurutkan berdasarkan total pembayaran (terbesar ke terkecil).\n");
}

// Pencarian data berdasarkan nama pelanggan
void searchData(Penjualan data[], int n) {
    char keyword[50];
    printf("Masukkan nama pelanggan yang ingin dicari: ");
    scanf(" %[^\n]s", keyword);

    printf("Hasil pencarian:\n");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(data[i].nama_pelanggan, keyword)) {
            printf("| %-12s | %-22s | %-15s | %-20s | %-6d | %-8.2f | %-8.2f |\n",
                   data[i].tanggal, 
                   data[i].nama_pelanggan, 
                   data[i].jenis_tiket, 
                   data[i].nama_event,
                   data[i].jumlah_tiket, 
                   data[i].harga_tiket, 
                   data[i].total_pembayaran);
            found = 1;
        }
    }
    if (!found) {
        printf("Data tidak ditemukan!\n");
    }
}

// Login admin
int loginAdmin() {
    char username[10] = "rudi";
    char password[10] = "rudi123";
    char inputUsername[10], inputPwd[10];

    printf("\nMasukkan username admin: ");
    scanf("%s", inputUsername);
    printf("Masukkan password admin: ");
    scanf("%s", inputPwd);

    if (strcmp(inputPwd, password) != 0 || strcmp(inputUsername, username) != 0) {
        printf("Username atau password salah!\n");
        return 0;
    }
    return 1;
}

// Proses pembelian tiket
void daftarKonser(Penjualan data[], int *n) {
    bacaStokTiket(); // Pastikan stok tiket terbaru dimuat
    int inputEvent;
    char lanjut[10] = "yes";

    while (strcmp(lanjut, "yes") == 0) {
        printf("\nDaftar Konser:\n");
        printf("1. Beni Rockstars\n");
        printf("2. Sheren Koplo\n");
        printf("3. Turen Bergoyang\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &inputEvent);

        if (inputEvent == 4) {
            printf("Keluar dari pembelian tiket.\n");
            break;
        }

        char nama_event[50];
        switch (inputEvent) {
            case 1: strcpy(nama_event, "Beni Rockstars"); break;
            case 2: strcpy(nama_event, "Sheren Koplo"); break;
            case 3: strcpy(nama_event, "Turen Bergoyang"); break;
            default:
                printf("Pilihan tidak valid!\n");
                continue;
        }

        // Menampilkan detail tiket berdasarkan event
        printf("\nDetails Event\n");
        for (int i = 0; i < MAX_EVENTS; i++) {
            if (strcmp(stok[i].nama_event, nama_event) == 0) {
                printf("Jenis Tiket     : %s\n", stok[i].jenis_tiket);
                printf("Harga Tiket     : Rp %s\n", 
                       strcmp(stok[i].jenis_tiket, "VIP") == 0 ? "5.000.000" : "1.500.000");
                printf("Stok Tiket      : %d\n\n", stok[i].stok_tiket);
            }
        }

        // Proses pembelian
        char name[50], ticketType[20];
        int ticketAmount, valid = 0, hargaTiket;
        float totalHarga;

        printf("Masukkan nama pembeli : ");
        scanf(" %[^\n]s", name);

        do {
            printf("Masukkan jenis tiket (VIP/Regular): ");
            scanf("%s", ticketType);
        
            for (int i = 0; i < MAX_EVENTS; i++) {
                if (strcmp(stok[i].nama_event, nama_event) == 0 &&
                    strcmp(stok[i].jenis_tiket, ticketType) == 0) {
                    valid = 1;
                    hargaTiket = strcmp(ticketType, "VIP") == 0 ? 5000000 : 1500000;
                    printf("Masukkan jumlah tiket: ");
                    scanf("%d", &ticketAmount);
        
                    if (ticketAmount > stok[i].stok_tiket) {
                        printf("Stok tidak mencukupi! Maksimal %d tiket tersedia.\n", stok[i].stok_tiket);
                        valid = 0;
                        continue;
                    } 

                    totalHarga = hargaTiket * ticketAmount;
                    printf("\nOrder Details:\n");
                    printf("Nama Pembeli   : %s\n", name);
                    printf("Jenis Tiket    : %s\n", ticketType);
                    printf("Jumlah Tiket   : %d\n", ticketAmount);
                    printf("Total Harga    : Rp %.2f\n", totalHarga);
        
                    // Konfirmasi pembayaran
                    char confirmPayment[10];
                    do {
                        printf("Lanjut ke pembayaran? [yes/no]: ");
                        scanf("%s", confirmPayment);
                    } while (strcmp(confirmPayment, "yes") != 0 && strcmp(confirmPayment, "no") != 0);
        
                    if (strcmp(confirmPayment, "yes") == 0) {
                        char paymentMethod[10];
                        do {
                            printf("Pilih metode pembayaran (cash/credit): ");
                            scanf("%s", paymentMethod);
                        } while (strcmp(paymentMethod, "cash") != 0 && strcmp(paymentMethod, "credit") != 0);
        
                        if (strcmp(paymentMethod, "cash") == 0) {
                            float cash;
                            do {
                                printf("Masukkan jumlah uang: Rp ");
                                scanf("%f", &cash);
                                if (cash < totalHarga) {
                                    printf("Uang tidak cukup! Masukkan jumlah yang sesuai.\n");
                                }
                            } while (cash < totalHarga);
        
                            printf("Payment berhasil! Kembalian Anda: Rp %.2f\n", cash - totalHarga);
                        } else if (strcmp(paymentMethod, "credit") == 0) {
                            char cardNumber[20];
                            do {
                                printf("Masukkan nomor kartu kredit (19 digit): ");
                                scanf("%s", cardNumber);
                                if (strlen(cardNumber) != 19) {
                                    printf("Nomor kartu kredit harus 19 digit!\n");
                                }
                            } while (strlen(cardNumber) != 19);
        
                            printf("Payment berhasil dengan kartu kredit!\n");
                        }
        
                        // Update stok
                        stok[i].stok_tiket -= ticketAmount;
                        // Simpan stok tiket setelah setiap transaksi
                        simpanStokTiket();

                        // Menambahkan data penjualan ke dalam array Penjualan
                        // Gunakan fungsi waktu standar untuk tanggal yang konsisten
                        time_t t = time(NULL);
                        struct tm *tm = localtime(&t);
                        char tanggal[20];  // Perbesar buffer untuk mengantisipasi masalah
                        strftime(tanggal, sizeof(tanggal), "%b %d %y", tm);
                        
                        // Pastikan panjang tanggal tidak melebihi batas
                        if (strlen(tanggal) >= sizeof(data[*n].tanggal)) {
                            strncpy(data[*n].tanggal, tanggal, sizeof(data[*n].tanggal) - 1);
                            data[*n].tanggal[sizeof(data[*n].tanggal) - 1] = '\0';
                        } else {
                            strcpy(data[*n].tanggal, tanggal);
                        }
                        
                        strcpy(data[*n].nama_pelanggan, name);
                        strcpy(data[*n].jenis_tiket, ticketType);
                        strcpy(data[*n].nama_event, nama_event);
                        data[*n].jumlah_tiket = ticketAmount;
                        data[*n].harga_tiket = hargaTiket;
                        data[*n].total_pembayaran = totalHarga;
                        (*n)++;

                        // Simpan data ke file setelah setiap transaksi
                        simpanData(data, *n);

                        printf("Tiket tersisa untuk %s (%s): %d\n", nama_event, ticketType, stok[i].stok_tiket);
                        break;
                    } else {
                        printf("Pembelian dibatalkan.\n");
                    }
                }
            }
        
            if (!valid) {
                printf("Jenis tiket tidak valid!\n");
            } else {
                break;
            }
        } while (1);

        // Konfirmasi lanjut atau keluar
        do {
            printf("\nIngin melakukan transaksi lagi? [yes/no]: ");
            scanf("%s", lanjut);
        } while (strcmp(lanjut, "yes") != 0 && strcmp(lanjut, "no") != 0);
    }
}

// Tambahkan fungsi untuk menampilkan stok tiket
void tampilkanStokTiket() {
    printf("\nStok Tiket Saat Ini:\n");
    printf("===========================================\n");
    printf("| Nama Event         | Jenis Tiket | Stok |\n");
    printf("===========================================\n");
    
    for (int i = 0; i < MAX_EVENTS; i++) {
        printf("| %-19s | %-11s | %-4d |\n", 
               stok[i].nama_event, 
               stok[i].jenis_tiket, 
               stok[i].stok_tiket);
    }
    printf("===========================================\n");
}

// Fungsi untuk menghapus data penjualan berdasarkan nama pelanggan
void hapusData(Penjualan data[], int *n) {
    char nama[50];
    printf("Masukkan nama pelanggan yang datanya ingin dihapus: ");
    scanf(" %[^\n]s", nama);

    int found = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(data[i].nama_pelanggan, nama) == 0) {
            found = 1;
            
            // Kembalikan stok tiket
            for (int j = 0; j < MAX_EVENTS; j++) {
                if (strcmp(data[i].nama_event, stok[j].nama_event) == 0 && 
                    strcmp(data[i].jenis_tiket, stok[j].jenis_tiket) == 0) {
                    stok[j].stok_tiket += data[i].jumlah_tiket;
                    break;
                }
            }

            // Geser elemen array
            for (int j = i; j < *n - 1; j++) {
                data[j] = data[j + 1];
            }
            (*n)--;
            i--; // Adjust index after shifting elements
        }
    }

    if (found) {
        // Simpan data penjualan yang diperbarui
        simpanData(data, *n);
        
        // Simpan stok tiket yang diperbarui
        simpanStokTiket();
        
        printf("Data berhasil dihapus dan file diperbarui.\n");
    } else {
        printf("Data dengan nama pelanggan '%s' tidak ditemukan!\n", nama);
    }
}

// Menu admin
void roleAdmin(Penjualan data[], int *jumlah_data) {
    if (!loginAdmin()) {
        return;
    }

    int pilihan;
    do {
        printf("\nMenu Admin:\n");
        printf("1. Tampilkan Semua Data Penjualan\n");
        printf("2. Urutkan Data Penjualan\n");
        printf("3. Cari Data Penjualan\n");
        printf("4. Hapus Data Penjualan\n");
        printf("5. Tampilkan Stok Tiket\n");
        printf("6. Keluar\n");

        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                *jumlah_data = bacaData(data);
                tampilkanData(data, *jumlah_data);
                break;
            }
            case 2: {
                *jumlah_data = bacaData(data);
                sortData(data, *jumlah_data);
                tampilkanData(data, *jumlah_data);
                break;
            }
            case 3: {
                *jumlah_data = bacaData(data);
                searchData(data, *jumlah_data);
                break;
            }
            case 4: {
                *jumlah_data = bacaData(data);
                hapusData(data, jumlah_data);
                break;
            }
            case 5: {
                tampilkanStokTiket();
                break;
            }
            case 6:
                printf("Keluar dari menu admin.\n");
                return;
            default:
                printf("Pilihan tidak valid! Silakan coba lagi.\n");
                break;
        }
    } while (pilihan != 6);
}

// Fungsi utama
int main() {
    Penjualan data[100];
    int inputRole, jumlah_data = 0;
    
    printf(ANSI_BLUE); // Warna terminal menjadi biru	
    DisplayTitle();

    // Muat stok tiket saat program dimulai
    bacaStokTiket();

    do {
        printf("\nSelamat Datang!\n");
        printf("Masuk sebagai:\n");
        printf("1. Admin\n");
        printf("2. User\n");
        printf("3. Keluar\n");
    
        printf("Pilih: ");
        scanf("%d", &inputRole);

        switch(inputRole) {
            case 1: {
                roleAdmin(data, &jumlah_data);
                break;
            }
            case 2: {
                daftarKonser(data, &jumlah_data);
                break;
            }
            case 3: {
                printf("Terima kasih. Keluar dari program.\n");
                return 0;
            }
            default: {
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
            }
        }
    } while (1); // Tambahkan loop untuk memungkinkan kembali ke menu utama

    return 0;
}
