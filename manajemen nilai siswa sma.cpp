#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Siswa {
    int id;
    string nama;
    string kelas;
    float matematika;
    float fisika;
    float kimia;
    float biologi;
    float bahasa_indonesia;
    float bahasa_inggris;
    float total_nilai;
    float rata_rata;
    string grade;
};

class SistemNilai {
private:
    Siswa siswa[100];
    int counter;
    
public:
    SistemNilai() {
        counter = 0;
        initDataSiswa();
    }
    
    void initDataSiswa() {
        // Data awal 20 siswa
        string nama_siswa[20] = {
            "Ahmad Rizki", "Siti Nurhaliza", "Budi Santoso", "Dewi Sartika",
            "Eko Prasetyo", "Fitri Ramadhani", "Gilang Ramadhan", "Hana Pertiwi",
            "Indra Gunawan", "Joko Widodo", "Kartika Sari", "Lutfi Hakim",
            "Maya Sari", "Nanda Pratama", "Oki Setiana", "Putri Ayu",
            "Qori Subhan", "Rina Susanti", "Sandi Permana", "Tika Melati"
        };
        
        string kelas_siswa[20] = {
            "XI IPA 1", "XI IPA 1", "XI IPA 1", "XI IPA 1", "XI IPA 1",
            "XI IPA 2", "XI IPA 2", "XI IPA 2", "XI IPA 2", "XI IPA 2",
            "XI IPS 1", "XI IPS 1", "XI IPS 1", "XI IPS 1", "XI IPS 1",
            "XI IPS 2", "XI IPS 2", "XI IPS 2", "XI IPS 2", "XI IPS 2"
        };
        
        // Inisialisasi data siswa dengan nilai random
        for(int i = 0; i < 20; i++) {
            siswa[i].id = i + 1;
            siswa[i].nama = nama_siswa[i];
            siswa[i].kelas = kelas_siswa[i];
            siswa[i].matematika = 70 + (rand() % 31);
            siswa[i].fisika = 70 + (rand() % 31);
            siswa[i].kimia = 70 + (rand() % 31);
            siswa[i].biologi = 70 + (rand() % 31);
            siswa[i].bahasa_indonesia = 70 + (rand() % 31);
            siswa[i].bahasa_inggris = 70 + (rand() % 31);
            
            hitungTotalRataRata(i);
            tentukanGrade(i);
            counter++;
        }
    }
    
    void hitungTotalRataRata(int index) {
        siswa[index].total_nilai = siswa[index].matematika + siswa[index].fisika + 
                                   siswa[index].kimia + siswa[index].biologi + 
                                   siswa[index].bahasa_indonesia + siswa[index].bahasa_inggris;
        siswa[index].rata_rata = siswa[index].total_nilai / 6.0;
    }
    
    void tentukanGrade(int index) {
        float rata = siswa[index].rata_rata;
        if(rata >= 90) siswa[index].grade = "A";
        else if(rata >= 80) siswa[index].grade = "B";
        else if(rata >= 70) siswa[index].grade = "C";
        else if(rata >= 60) siswa[index].grade = "D";
        else siswa[index].grade = "E";
    }
    
    void tampilkanHeader() {
        cout << "\n" << string(120, '=') << endl;
        cout << setw(60) << "SISTEM MANAJEMEN NILAI SISWA SMA" << endl;
        cout << string(120, '=') << endl;
        cout << left << setw(5) << "ID" << setw(20) << "Nama" << setw(12) << "Kelas"
             << setw(8) << "MTK" << setw(8) << "FIS" << setw(8) << "KIM"
             << setw(8) << "BIO" << setw(8) << "B.IND" << setw(8) << "B.ING"
             << setw(10) << "Total" << setw(10) << "Rata2" << setw(8) << "Grade" << endl;
        cout << string(120, '-') << endl;
    }
    
    void tampilkanSiswa(int index) {
        cout << left << setw(5) << siswa[index].id
             << setw(20) << siswa[index].nama
             << setw(12) << siswa[index].kelas
             << setw(8) << fixed << setprecision(1) << siswa[index].matematika
             << setw(8) << siswa[index].fisika
             << setw(8) << siswa[index].kimia
             << setw(8) << siswa[index].biologi
             << setw(8) << siswa[index].bahasa_indonesia
             << setw(8) << siswa[index].bahasa_inggris
             << setw(10) << setprecision(1) << siswa[index].total_nilai
             << setw(10) << setprecision(2) << siswa[index].rata_rata
             << setw(8) << siswa[index].grade << endl;
    }
    
    void tampilkanSemuaSiswa() {
        tampilkanHeader();
        for(int i = 0; i < counter; i++) {
            tampilkanSiswa(i);
        }
        cout << string(120, '=') << endl;
        cout << "Total Siswa: " << counter << endl;
    }
    
    void inputNilaiSiswa() {
        if(counter >= 100) {
            cout << "Database penuh! Maksimal 100 siswa." << endl;
            return;
        }
        
        cout << "\n=== INPUT DATA SISWA BARU ===" << endl;
        siswa[counter].id = counter + 1;
        
        cout << "Nama Siswa: ";
        cin.ignore();
        getline(cin, siswa[counter].nama);
        
        cout << "Kelas: ";
        getline(cin, siswa[counter].kelas);
        
        cout << "Nilai Matematika: ";
        cin >> siswa[counter].matematika;
        
        cout << "Nilai Fisika: ";
        cin >> siswa[counter].fisika;
        
        cout << "Nilai Kimia: ";
        cin >> siswa[counter].kimia;
        
        cout << "Nilai Biologi: ";
        cin >> siswa[counter].biologi;
        
        cout << "Nilai Bahasa Indonesia: ";
        cin >> siswa[counter].bahasa_indonesia;
        
        cout << "Nilai Bahasa Inggris: ";
        cin >> siswa[counter].bahasa_inggris;
        
        hitungTotalRataRata(counter);
        tentukanGrade(counter);
        counter++;
        
        cout << "Data siswa berhasil ditambahkan!" << endl;
    }
    
    void editNilaiSiswa() {
        int id;
        cout << "\n=== EDIT NILAI SISWA ===" << endl;
        cout << "Masukkan ID Siswa: ";
        cin >> id;
        
        int index = -1;
        for(int i = 0; i < counter; i++) {
            if(siswa[i].id == id) {
                index = i;
                break;
            }
        }
        
        if(index == -1) {
            cout << "Siswa dengan ID " << id << " tidak ditemukan!" << endl;
            return;
        }
        
        cout << "Data saat ini untuk " << siswa[index].nama << ":" << endl;
        tampilkanHeader();
        tampilkanSiswa(index);
        
        cout << "\nMasukkan nilai baru:" << endl;
        cout << "Nilai Matematika: ";
        cin >> siswa[index].matematika;
        
        cout << "Nilai Fisika: ";
        cin >> siswa[index].fisika;
        
        cout << "Nilai Kimia: ";
        cin >> siswa[index].kimia;
        
        cout << "Nilai Biologi: ";
        cin >> siswa[index].biologi;
        
        cout << "Nilai Bahasa Indonesia: ";
        cin >> siswa[index].bahasa_indonesia;
        
        cout << "Nilai Bahasa Inggris: ";
        cin >> siswa[index].bahasa_inggris;
        
        hitungTotalRataRata(index);
        tentukanGrade(index);
        
        cout << "Nilai berhasil diupdate!" << endl;
    }
    
    void cariSiswa() {
        int pilihan;
        cout << "\n=== PENCARIAN SISWA ===" << endl;
        cout << "1. Cari berdasarkan Nama" << endl;
        cout << "2. Cari berdasarkan ID" << endl;
        cout << "3. Cari berdasarkan Kelas" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        bool ditemukan = false;
        
        switch(pilihan) {
            case 1: {
                string nama;
                cout << "Masukkan nama siswa: ";
                cin.ignore();
                getline(cin, nama);
                
                tampilkanHeader();
                for(int i = 0; i < counter; i++) {
                    if(siswa[i].nama.find(nama) != string::npos) {
                        tampilkanSiswa(i);
                        ditemukan = true;
                    }
                }
                break;
            }
            case 2: {
                int id;
                cout << "Masukkan ID siswa: ";
                cin >> id;
                
                tampilkanHeader();
                for(int i = 0; i < counter; i++) {
                    if(siswa[i].id == id) {
                        tampilkanSiswa(i);
                        ditemukan = true;
                        break;
                    }
                }
                break;
            }
            case 3: {
                string kelas;
                cout << "Masukkan kelas: ";
                cin.ignore();
                getline(cin, kelas);
                
                tampilkanHeader();
                for(int i = 0; i < counter; i++) {
                    if(siswa[i].kelas == kelas) {
                        tampilkanSiswa(i);
                        ditemukan = true;
                    }
                }
                break;
            }
            default:
                cout << "Pilihan tidak valid!" << endl;
                return;
        }
        
        if(!ditemukan) {
            cout << "Data tidak ditemukan!" << endl;
        }
    }
    
    void sortingSiswa() {
        int pilihan;
        cout << "\n=== SORTING DATA SISWA ===" << endl;
        cout << "1. Sort berdasarkan Nama (A-Z)" << endl;
        cout << "2. Sort berdasarkan Rata-rata (Tertinggi)" << endl;
        cout << "3. Sort berdasarkan Total Nilai (Tertinggi)" << endl;
        cout << "4. Sort berdasarkan ID" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                // Bubble sort berdasarkan nama
                for(int i = 0; i < counter - 1; i++) {
                    for(int j = 0; j < counter - i - 1; j++) {
                        if(siswa[j].nama > siswa[j + 1].nama) {
                            swap(siswa[j], siswa[j + 1]);
                        }
                    }
                }
                cout << "Data berhasil diurutkan berdasarkan nama!" << endl;
                break;
                
            case 2:
                // Bubble sort berdasarkan rata-rata (descending)
                for(int i = 0; i < counter - 1; i++) {
                    for(int j = 0; j < counter - i - 1; j++) {
                        if(siswa[j].rata_rata < siswa[j + 1].rata_rata) {
                            swap(siswa[j], siswa[j + 1]);
                        }
                    }
                }
                cout << "Data berhasil diurutkan berdasarkan rata-rata!" << endl;
                break;
                
            case 3:
                // Bubble sort berdasarkan total nilai (descending)
                for(int i = 0; i < counter - 1; i++) {
                    for(int j = 0; j < counter - i - 1; j++) {
                        if(siswa[j].total_nilai < siswa[j + 1].total_nilai) {
                            swap(siswa[j], siswa[j + 1]);
                        }
                    }
                }
                cout << "Data berhasil diurutkan berdasarkan total nilai!" << endl;
                break;
                
            case 4:
                // Bubble sort berdasarkan ID
                for(int i = 0; i < counter - 1; i++) {
                    for(int j = 0; j < counter - i - 1; j++) {
                        if(siswa[j].id > siswa[j + 1].id) {
                            swap(siswa[j], siswa[j + 1]);
                        }
                    }
                }
                cout << "Data berhasil diurutkan berdasarkan ID!" << endl;
                break;
                
            default:
                cout << "Pilihan tidak valid!" << endl;
                return;
        }
        
        tampilkanSemuaSiswa();
    }
    
    void laporanNilai() {
        cout << "\n=== LAPORAN NILAI SISWA ===" << endl;
        
        // Statistik umum
        float total_rata_rata = 0;
        int grade_A = 0, grade_B = 0, grade_C = 0, grade_D = 0, grade_E = 0;
        float nilai_tertinggi = 0, nilai_terendah = 100;
        
        for(int i = 0; i < counter; i++) {
            total_rata_rata += siswa[i].rata_rata;
            
            if(siswa[i].rata_rata > nilai_tertinggi) nilai_tertinggi = siswa[i].rata_rata;
            if(siswa[i].rata_rata < nilai_terendah) nilai_terendah = siswa[i].rata_rata;
            
            if(siswa[i].grade == "A") grade_A++;
            else if(siswa[i].grade == "B") grade_B++;
            else if(siswa[i].grade == "C") grade_C++;
            else if(siswa[i].grade == "D") grade_D++;
            else if(siswa[i].grade == "E") grade_E++;
        }
        
        cout << "\n=== STATISTIK UMUM ===" << endl;
        cout << "Total Siswa: " << counter << endl;
        cout << "Rata-rata Kelas: " << fixed << setprecision(2) << total_rata_rata / counter << endl;
        cout << "Nilai Tertinggi: " << nilai_tertinggi << endl;
        cout << "Nilai Terendah: " << nilai_terendah << endl;
        
        cout << "\n=== DISTRIBUSI GRADE ===" << endl;
        cout << "Grade A: " << grade_A << " siswa" << endl;
        cout << "Grade B: " << grade_B << " siswa" << endl;
        cout << "Grade C: " << grade_C << " siswa" << endl;
        cout << "Grade D: " << grade_D << " siswa" << endl;
        cout << "Grade E: " << grade_E << " siswa" << endl;
        
        tampilkanSemuaSiswa();
    }
    
    void riwayatNilai() {
        cout << "\n=== RIWAYAT NILAI SISWA ===" << endl;
        cout << "Menampilkan data nilai semester saat ini..." << endl;
        tampilkanSemuaSiswa();
        
        cout << "\nCatatan: Fitur riwayat semester sebelumnya akan tersedia pada versi mendatang." << endl;
    }
    
    void tampilkanMenu() {
        cout << "\n" << string(50, '=') << endl;
        cout << setw(35) << "SISTEM MANAJEMEN NILAI SISWA SMA" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Tampilkan Semua Siswa" << endl;
        cout << "2. Input Nilai Siswa Baru" << endl;
        cout << "3. Edit Nilai Siswa" << endl;
        cout << "4. Cari Siswa" << endl;
        cout << "5. Sorting Data" << endl;
        cout << "6. Laporan Nilai" << endl;
        cout << "7. Riwayat Nilai" << endl;
        cout << "0. Keluar" << endl;
        cout << string(50, '=') << endl;
        cout << "Total Siswa Terdaftar: " << counter << endl;
        cout << "Pilihan Anda: ";
    }
    
    void jalankan() {
        int pilihan;
        
        do {
            tampilkanMenu();
            cin >> pilihan;
            
            switch(pilihan) {
                case 1:
                    tampilkanSemuaSiswa();
                    break;
                case 2:
                    inputNilaiSiswa();
                    break;
                case 3:
                    editNilaiSiswa();
                    break;
                case 4:
                    cariSiswa();
                    break;
                case 5:
                    sortingSiswa();
                    break;
                case 6:
                    laporanNilai();
                    break;
                case 7:
                    riwayatNilai();
                    break;
                case 0:
                    cout << "\nTerima kasih telah menggunakan Sistem Manajemen Nilai Siswa SMA!" << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            }
            
            if(pilihan != 0) {
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
            }
            
        } while(pilihan != 0);
    }
};

int main() {
    SistemNilai sistem;
    sistem.jalankan();
    return 0;
}
