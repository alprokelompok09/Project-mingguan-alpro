#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct NilaiMataPelajaran {
    float uk1, uk2, uk3;  // Ulangan Kecil 1, 2, 3
    float uts;            // Ulangan Tengah Semester
    float uas;            // Ulangan Akhir Semester
    float rata_rata_uk;   // Rata-rata UK
    float nilai_akhir;    // Nilai akhir mata pelajaran
};

struct JamPelajaran {
    string waktu;
    string mata_pelajaran;
    string guru;
    string ruang;
};

struct JadwalHarian {
    string hari;
    JamPelajaran jam[8];  // Maksimal 8 jam pelajaran per hari
    int jumlah_jam;
};

struct JadwalKelas {
    string nama_kelas;
    JadwalHarian jadwal_mingguan[6];  // Senin-Sabtu
    bool jadwal_tersedia;
};

struct Siswa {
    int id;
    string nama;
    string kelas;
    
    // Nilai per mata pelajaran dengan komponen UK, UTS, UAS
    NilaiMataPelajaran matematika;
    NilaiMataPelajaran fisika;
    NilaiMataPelajaran kimia;
    NilaiMataPelajaran biologi;
    NilaiMataPelajaran bahasa_indonesia;
    NilaiMataPelajaran bahasa_inggris;
    NilaiMataPelajaran agama_islam;
    NilaiMataPelajaran pendidikan_kewarganegaraan;
    NilaiMataPelajaran seni_budaya;
    NilaiMataPelajaran prakarya;
    
    
    float total_nilai_akhir;
    float rata_rata_keseluruhan;
    string grade;
};

class SistemNilai {
private:
    Siswa siswa[100];
    int counter;
    JadwalKelas jadwal_kelas[10];  // Maksimal 10 kelas berbeda
    int jumlah_kelas_jadwal;
    
    // Fungsi untuk menghitung nilai akhir mata pelajaran
    float hitungNilaiAkhir(NilaiMataPelajaran &mapel) {
        // Rata-rata UK (bobot 30%)
        mapel.rata_rata_uk = (mapel.uk1 + mapel.uk2 + mapel.uk3) / 3.0;
        
        // Nilai Akhir = (Rata-rata UK × 30%) + (UTS × 35%) + (UAS × 35%)
        mapel.nilai_akhir = (mapel.rata_rata_uk * 0.3) + (mapel.uts * 0.35) + (mapel.uas * 0.35);
        
        return mapel.nilai_akhir;
    }
    
public:
    SistemNilai() {
        counter = 0;
        jumlah_kelas_jadwal = 0;
        initDataSiswa();
        initJadwalKelas();
    }
    
    void initDataSiswa() {
        // Data awal 20 siswa
        string nama_siswa[20] = {
            "Ahmad Rizki", "Siti Nurhaliza", "Risky Ramadhani", "Dewi Sartika",
            "Eko Prasetyo", "Fitri Ramadhani", "Gilang Ramadhan", "Hana Pertiwi",
            "Ahmad Alfianto", "Duta Satria", "Kartika Sari", "Lutfi Hakim",
            "Maya Sari", "Nanda Pratama", "Oki Setiana", "Putri Ayu",
            "Qori Subhan","Rina Susanti", "Sandi Permana", "Tika Melati"
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
            
            // Generate nilai random untuk setiap komponen
            initNilaiMataPelajaran(siswa[i].matematika);
            initNilaiMataPelajaran(siswa[i].fisika);
            initNilaiMataPelajaran(siswa[i].kimia);
            initNilaiMataPelajaran(siswa[i].biologi);
            initNilaiMataPelajaran(siswa[i].bahasa_indonesia);
            initNilaiMataPelajaran(siswa[i].bahasa_inggris);
            initNilaiMataPelajaran(siswa[i].agama_islam);
            initNilaiMataPelajaran(siswa[i].pendidikan_kewarganegaraan);
            initNilaiMataPelajaran(siswa[i].seni_budaya);
            initNilaiMataPelajaran(siswa[i].prakarya);
            
            hitungTotalRataRata(i);
            tentukanGrade(i);
            counter++;
        }
    }
    
    void initJadwalKelas() {
        // Inisialisasi jadwal untuk kelas-kelas yang ada
        string kelas_list[4] = {"XI IPA 1", "XI IPA 2", "XI IPS 1", "XI IPS 2"};
        string hari_list[6] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
        
        for(int k = 0; k < 4; k++) {
            jadwal_kelas[k].nama_kelas = kelas_list[k];
            jadwal_kelas[k].jadwal_tersedia = true;
            
            for(int h = 0; h < 6; h++) {
                jadwal_kelas[k].jadwal_mingguan[h].hari = hari_list[h];
                
                if(kelas_list[k].find("IPA") != string::npos) {
                    initJadwalIPA(jadwal_kelas[k].jadwal_mingguan[h], h);
                } else {
                    initJadwalIPS(jadwal_kelas[k].jadwal_mingguan[h], h);
                }
            }
        }
        jumlah_kelas_jadwal = 4;
    }
    
    void initJadwalIPA(JadwalHarian &jadwal, int hari_index) {
        string waktu_list[8] = {
            "07.00-07.45", "07.45-08.30", "08.30-09.15", "09.30-10.15",
            "10.15-11.00", "11.00-11.45", "12.30-13.15", "13.15-14.00"
        };
        
        // Jadwal berbeda untuk setiap hari
        switch(hari_index) {
            case 0: // Senin
                jadwal.jumlah_jam = 8;
                jadwal.jam[0] = {waktu_list[0], "Upacara/Pembina", "Pembina", "Lapangan"};
                jadwal.jam[1] = {waktu_list[1], "Matematika", "Pak Budi", "R.101"};
                jadwal.jam[2] = {waktu_list[2], "Matematika", "Pak Budi", "R.101"};
                jadwal.jam[3] = {waktu_list[3], "Fisika", "Bu Sari", "Lab Fisika"};
                jadwal.jam[4] = {waktu_list[4], "Fisika", "Bu Sari", "Lab Fisika"};
                jadwal.jam[5] = {waktu_list[5], "B. Indonesia", "Bu Dewi", "R.101"};
                jadwal.jam[6] = {waktu_list[6], "B. Inggris", "Mr. John", "R.101"};
                jadwal.jam[7] = {waktu_list[7], "Kimia", "Bu Rita", "Lab Kimia"};
                break;
            case 1: // Selasa
                jadwal.jumlah_jam = 7;
                jadwal.jam[0] = {waktu_list[0], "Kimia", "Bu Rita", "Lab Kimia"};
                jadwal.jam[1] = {waktu_list[1], "Kimia", "Bu Rita", "Lab Kimia"};
                jadwal.jam[2] = {waktu_list[2], "Biologi", "Pak Anton", "Lab Bio"};
                jadwal.jam[3] = {waktu_list[3], "Biologi", "Pak Anton", "Lab Bio"};
                jadwal.jam[4] = {waktu_list[4], "Matematika", "Pak Budi", "R.101"};
                jadwal.jam[5] = {waktu_list[5], "B. Indonesia", "Bu Dewi", "R.101"};
                jadwal.jam[6] = {waktu_list[6], "Olahraga", "Pak Edi", "Lapangan"};
                break;
            case 2: // Rabu
                jadwal.jumlah_jam = 8;
                jadwal.jam[0] = {waktu_list[0], "B. Inggris", "Mr. John", "R.101"};
                jadwal.jam[1] = {waktu_list[1], "B. Inggris", "Mr. John", "R.101"};
                jadwal.jam[2] = {waktu_list[2], "Fisika", "Bu Sari", "Lab Fisika"};
                jadwal.jam[3] = {waktu_list[3], "Matematika", "Pak Budi", "R.101"};
                jadwal.jam[4] = {waktu_list[4], "Matematika", "Pak Budi", "R.101"};
                jadwal.jam[5] = {waktu_list[5], "PKN", "Bu Lina", "R.101"};
                jadwal.jam[6] = {waktu_list[6], "Agama", "Pak Hasan", "R.102"};
                jadwal.jam[7] = {waktu_list[7], "Seni Budaya", "Bu Maya", "R.Seni"};
                break;
            case 3: // Kamis
                jadwal.jumlah_jam = 7;
                jadwal.jam[0] = {waktu_list[0], "Biologi", "Pak Anton", "Lab Bio"};
                jadwal.jam[1] = {waktu_list[1], "Kimia", "Bu Rita", "Lab Kimia"};
                jadwal.jam[2] = {waktu_list[2], "Fisika", "Bu Sari", "Lab Fisika"};
                jadwal.jam[3] = {waktu_list[3], "Fisika", "Bu Sari", "Lab Fisika"};
                jadwal.jam[4] = {waktu_list[4], "B. Indonesia", "Bu Dewi", "R.101"};
                jadwal.jam[5] = {waktu_list[5], "B. Indonesia", "Bu Dewi", "R.101"};
                jadwal.jam[6] = {waktu_list[6], "Matematika", "Pak Budi", "R.101"};
                break;
            case 4: // Jumat
                jadwal.jumlah_jam = 6;
                jadwal.jam[0] = {waktu_list[0], "Senam/Jalan Sehat", "Pak Edi", "Lapangan"};
                jadwal.jam[1] = {waktu_list[1], "B. Inggris", "Mr. John", "R.101"};
                jadwal.jam[2] = {waktu_list[2], "Matematika", "Pak Budi", "R.101"};
                jadwal.jam[3] = {waktu_list[3], "Biologi", "Pak Anton", "Lab Bio"};
                jadwal.jam[4] = {waktu_list[4], "TIK", "Pak Rendi", "Lab Komp"};
                jadwal.jam[5] = {waktu_list[5], "TIK", "Pak Rendi", "Lab Komp"};
                break;
            case 5: // Sabtu
                jadwal.jumlah_jam = 6;
                jadwal.jam[0] = {waktu_list[0], "Konseling", "Bu Psikolog", "R.BK"};
                jadwal.jam[1] = {waktu_list[1], "Agama", "Pak Hasan", "R.102"};
                jadwal.jam[2] = {waktu_list[2], "PKN", "Bu Lina", "R.101"};
                jadwal.jam[3] = {waktu_list[3], "Seni Budaya", "Bu Maya", "R.Seni"};
                jadwal.jam[4] = {waktu_list[4], "Ekstrakurikuler", "Berbagai", "Berbagai"};
                jadwal.jam[5] = {waktu_list[5], "Ekstrakurikuler", "Berbagai", "Berbagai"};
                break;
        }
    }
    
    void initJadwalIPS(JadwalHarian &jadwal, int hari_index) {
        string waktu_list[8] = {
            "07.00-07.45", "07.45-08.30", "08.30-09.15", "09.30-10.15",
            "10.15-11.00", "11.00-11.45", "12.30-13.15", "13.15-14.00"
        };
        
        // Jadwal IPS lebih fokus pada mata pelajaran sosial
        switch(hari_index) {
            case 0: // Senin
                jadwal.jumlah_jam = 8;
                jadwal.jam[0] = {waktu_list[0], "Upacara/Pembina", "Pembina", "Lapangan"};
                jadwal.jam[1] = {waktu_list[1], "Matematika", "Pak Budi", "R.201"};
                jadwal.jam[2] = {waktu_list[2], "Sejarah", "Bu Indah", "R.201"};
                jadwal.jam[3] = {waktu_list[3], "Sejarah", "Bu Indah", "R.201"};
                jadwal.jam[4] = {waktu_list[4], "Geografi", "Pak Tomo", "R.201"};
                jadwal.jam[5] = {waktu_list[5], "B. Indonesia", "Bu Dewi", "R.201"};
                jadwal.jam[6] = {waktu_list[6], "B. Inggris", "Mr. John", "R.201"};
                jadwal.jam[7] = {waktu_list[7], "Ekonomi", "Bu Susan", "R.201"};
                break;
            case 1: // Selasa
                jadwal.jumlah_jam = 7;
                jadwal.jam[0] = {waktu_list[0], "Ekonomi", "Bu Susan", "R.201"};
                jadwal.jam[1] = {waktu_list[1], "Ekonomi", "Bu Susan", "R.201"};
                jadwal.jam[2] = {waktu_list[2], "Sosiologi", "Pak Wawan", "R.201"};
                jadwal.jam[3] = {waktu_list[3], "Sosiologi", "Pak Wawan", "R.201"};
                jadwal.jam[4] = {waktu_list[4], "Matematika", "Pak Budi", "R.201"};
                jadwal.jam[5] = {waktu_list[5], "B. Indonesia", "Bu Dewi", "R.201"};
                jadwal.jam[6] = {waktu_list[6], "Olahraga", "Pak Edi", "Lapangan"};
                break;
            case 2: // Rabu
                jadwal.jumlah_jam = 8;
                jadwal.jam[0] = {waktu_list[0], "B. Inggris", "Mr. John", "R.201"};
                jadwal.jam[1] = {waktu_list[1], "B. Inggris", "Mr. John", "R.201"};
                jadwal.jam[2] = {waktu_list[2], "Geografi", "Pak Tomo", "R.201"};
                jadwal.jam[3] = {waktu_list[3], "Matematika", "Pak Budi", "R.201"};
                jadwal.jam[4] = {waktu_list[4], "Matematika", "Pak Budi", "R.201"};
                jadwal.jam[5] = {waktu_list[5], "PKN", "Bu Lina", "R.201"};
                jadwal.jam[6] = {waktu_list[6], "Agama", "Pak Hasan", "R.202"};
                jadwal.jam[7] = {waktu_list[7], "Seni Budaya", "Bu Maya", "R.Seni"};
                break;
            case 3: // Kamis
                jadwal.jumlah_jam = 7;
                jadwal.jam[0] = {waktu_list[0], "Sejarah", "Bu Indah", "R.201"};
                jadwal.jam[1] = {waktu_list[1], "Ekonomi", "Bu Susan", "R.201"};
                jadwal.jam[2] = {waktu_list[2], "Geografi", "Pak Tomo", "R.201"};
                jadwal.jam[3] = {waktu_list[3], "Geografi", "Pak Tomo", "R.201"};
                jadwal.jam[4] = {waktu_list[4], "B. Indonesia", "Bu Dewi", "R.201"};
                jadwal.jam[5] = {waktu_list[5], "B. Indonesia", "Bu Dewi", "R.201"};
                jadwal.jam[6] = {waktu_list[6], "Matematika", "Pak Budi", "R.201"};
                break;
            case 4: // Jumat
                jadwal.jumlah_jam = 6;
                jadwal.jam[0] = {waktu_list[0], "Senam/Jalan Sehat", "Pak Edi", "Lapangan"};
                jadwal.jam[1] = {waktu_list[1], "B. Inggris", "Mr. John", "R.201"};
                jadwal.jam[2] = {waktu_list[2], "Matematika", "Pak Budi", "R.201"};
                jadwal.jam[3] = {waktu_list[3], "Sosiologi", "Pak Wawan", "R.201"};
                jadwal.jam[4] = {waktu_list[4], "TIK", "Pak Rendi", "Lab Komp"};
                jadwal.jam[5] = {waktu_list[5], "TIK", "Pak Rendi", "Lab Komp"};
                break;
            case 5: // Sabtu
                jadwal.jumlah_jam = 6;
                jadwal.jam[0] = {waktu_list[0], "Konseling", "Bu Psikolog", "R.BK"};
                jadwal.jam[1] = {waktu_list[1], "Agama", "Pak Hasan", "R.202"};
                jadwal.jam[2] = {waktu_list[2], "PKN", "Bu Lina", "R.201"};
                jadwal.jam[3] = {waktu_list[3], "Seni Budaya", "Bu Maya", "R.Seni"};
                jadwal.jam[4] = {waktu_list[4], "Ekstrakurikuler", "Berbagai", "Berbagai"};
                jadwal.jam[5] = {waktu_list[5], "Ekstrakurikuler", "Berbagai", "Berbagai"};
                break;
        }
    }
    
    void initNilaiMataPelajaran(NilaiMataPelajaran &mapel) {
        mapel.uk1 = 70 + (rand() % 31);
        mapel.uk2 = 70 + (rand() % 31);
        mapel.uk3 = 70 + (rand() % 31);
        mapel.uts = 70 + (rand() % 31);
        mapel.uas = 70 + (rand() % 31);
        hitungNilaiAkhir(mapel);
    }
    
    void hitungTotalRataRata(int index) {
        siswa[index].total_nilai_akhir = 
            siswa[index].matematika.nilai_akhir + 
            siswa[index].fisika.nilai_akhir + 
            siswa[index].kimia.nilai_akhir + 
            siswa[index].biologi.nilai_akhir + 
            siswa[index].bahasa_indonesia.nilai_akhir + 
            siswa[index].bahasa_inggris.nilai_akhir;
            siswa[index].agama_islam.nilai_akhir +
            siswa[index].pendidikan_kewarganegaraan.nilai_akhir +
            siswa[index].seni_budaya.nilai_akhir +
            siswa[index].prakarya.nilai_akhir ;
            
        siswa[index].rata_rata_keseluruhan = siswa[index].total_nilai_akhir / 6.0;
    }
    
    void tentukanGrade(int index) {
        float rata = siswa[index].rata_rata_keseluruhan;
        if(rata >= 90) siswa[index].grade = "A";
        else if(rata >= 80) siswa[index].grade = "B";
        else if(rata >= 70) siswa[index].grade = "C";
        else if(rata >= 60) siswa[index].grade = "D";
        else siswa[index].grade = "E";
    }
    
    // FUNGSI JADWAL
    void tampilkanJadwalKelas() {
        string nama_kelas;
        cout << "\n=== JADWAL PELAJARAN KELAS ===" << endl;
        cout << "Pilih Kelas:" << endl;
        for(int i = 0; i < jumlah_kelas_jadwal; i++) {
            cout << i + 1 << ". " << jadwal_kelas[i].nama_kelas << endl;
        }
        cout << "Pilihan: ";
        
        int pilihan;
        cin >> pilihan;
        
        if(pilihan < 1 || pilihan > jumlah_kelas_jadwal) {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }
        
        int index = pilihan - 1;
        
        cout << "\n" << string(80, '=') << endl;
        cout << setw(45) << "JADWAL PELAJARAN KELAS " << jadwal_kelas[index].nama_kelas << endl;
        cout << string(80, '=') << endl;
        
        for(int h = 0; h < 6; h++) {
            cout << "\n" << jadwal_kelas[index].jadwal_mingguan[h].hari << ":" << endl;
            cout << string(80, '-') << endl;
            cout << left << setw(12) << "Waktu" << setw(18) << "Mata Pelajaran" 
                 << setw(15) << "Guru" << setw(15) << "Ruang" << endl;
            cout << string(80, '-') << endl;
            
            for(int j = 0; j < jadwal_kelas[index].jadwal_mingguan[h].jumlah_jam; j++) {
                JamPelajaran jam = jadwal_kelas[index].jadwal_mingguan[h].jam[j];
                cout << left << setw(12) << jam.waktu 
                     << setw(18) << jam.mata_pelajaran
                     << setw(15) << jam.guru 
                     << setw(15) << jam.ruang << endl;
            }
        }
        cout << string(80, '=') << endl;
    }
    
    void tampilkanJadwalSiswa() {
        int id;
        cout << "\n=== JADWAL PELAJARAN SISWA ===" << endl;
        cout << "Masukkan ID Siswa: ";
        cin >> id;
        
        int index_siswa = -1;
        for(int i = 0; i < counter; i++) {
            if(siswa[i].id == id) {
                index_siswa = i;
                break;
            }
        }
        
        if(index_siswa == -1) {
            cout << "Siswa dengan ID " << id << " tidak ditemukan!" << endl;
            return;
        }
        
        // Cari jadwal kelas siswa
        int index_kelas = -1;
        for(int i = 0; i < jumlah_kelas_jadwal; i++) {
            if(jadwal_kelas[i].nama_kelas == siswa[index_siswa].kelas) {
                index_kelas = i;
                break;
            }
        }
        
        if(index_kelas == -1) {
            cout << "Jadwal untuk kelas " << siswa[index_siswa].kelas << " belum tersedia!" << endl;
            return;
        }
        
        cout << "\n" << string(80, '=') << endl;
        cout << "JADWAL PELAJARAN - " << siswa[index_siswa].nama << " (" << siswa[index_siswa].kelas << ")" << endl;
        cout << string(80, '=') << endl;
        
        for(int h = 0; h < 6; h++) {
            cout << "\n" << jadwal_kelas[index_kelas].jadwal_mingguan[h].hari << ":" << endl;
            cout << string(80, '-') << endl;
            cout << left << setw(12) << "Waktu" << setw(18) << "Mata Pelajaran" 
                 << setw(15) << "Guru" << setw(15) << "Ruang" << endl;
            cout << string(80, '-') << endl;
            
            for(int j = 0; j < jadwal_kelas[index_kelas].jadwal_mingguan[h].jumlah_jam; j++) {
                JamPelajaran jam = jadwal_kelas[index_kelas].jadwal_mingguan[h].jam[j];
                cout << left << setw(12) << jam.waktu 
                     << setw(18) << jam.mata_pelajaran
                     << setw(15) << jam.guru 
                     << setw(15) << jam.ruang << endl;
            }
        }
        cout << string(80, '=') << endl;
    }
    
    void cariJadwalMapel() {
        string mata_pelajaran;
        cout << "\n=== CARI JADWAL MATA PELAJARAN ===" << endl;
        cout << "Masukkan nama mata pelajaran: ";
        cin.ignore();
        getline(cin, mata_pelajaran);
        
        cout << "\n=== HASIL PENCARIAN: " << mata_pelajaran << " ===" << endl;
        cout << string(90, '=') << endl;
        cout << left << setw(12) << "Kelas" << setw(10) << "Hari" << setw(12) << "Waktu" 
             << setw(15) << "Guru" << setw(15) << "Ruang" << endl;
        cout << string(90, '-') << endl;
        
        bool ditemukan = false;
        
        for(int k = 0; k < jumlah_kelas_jadwal; k++) {
            for(int h = 0; h < 6; h++) {
                for(int j = 0; j < jadwal_kelas[k].jadwal_mingguan[h].jumlah_jam; j++) {
                    JamPelajaran jam = jadwal_kelas[k].jadwal_mingguan[h].jam[j];
                    
                    if(jam.mata_pelajaran.find(mata_pelajaran) != string::npos) {
                        cout << left << setw(12) << jadwal_kelas[k].nama_kelas
                             << setw(10) << jadwal_kelas[k].jadwal_mingguan[h].hari
                             << setw(12) << jam.waktu
                             << setw(15) << jam.guru
                             << setw(15) << jam.ruang << endl;
                        ditemukan = true;
                    }
                }
            }
        }
        
        if(!ditemukan) {
            cout << "Mata pelajaran '" << mata_pelajaran << "' tidak ditemukan dalam jadwal!" << endl;
        }
        cout << string(90, '=') << endl;
    }
    
    void editJadwalKelas() {
        cout << "\n=== EDIT JADWAL KELAS ===" << endl;
        cout << "Pilih Kelas:" << endl;
        for(int i = 0; i < jumlah_kelas_jadwal; i++) {
            cout << i + 1 << ". " << jadwal_kelas[i].nama_kelas << endl;
        }
        cout << "Pilihan: ";
        
        int pilihan_kelas;
        cin >> pilihan_kelas;
        
        if(pilihan_kelas < 1 || pilihan_kelas > jumlah_kelas_jadwal) {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }
        
        int index_kelas = pilihan_kelas - 1;
        
        cout << "\nPilih Hari:" << endl;
        for(int i = 0; i < 6; i++) {
            cout << i + 1 << ". " << jadwal_kelas[index_kelas].jadwal_mingguan[i].hari << endl;
        }
        cout << "Pilihan: ";
        
        int pilihan_hari;
        cin >> pilihan_hari;
        
        if(pilihan_hari < 1 || pilihan_hari > 6) {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }
        
        int index_hari = pilihan_hari - 1;
        
        cout << "\nJadwal " << jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].hari << ":" << endl;
        cout << string(80, '-') << endl;
        
        for(int j = 0; j < jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jumlah_jam; j++) {
            JamPelajaran jam = jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[j];
            cout << j + 1 << ". " << jam.waktu << " - " << jam.mata_pelajaran 
                 << " (" << jam.guru << ", " << jam.ruang << ")" << endl;
        }
        
        cout << "\nPilih jam yang akan diedit: ";
        int pilihan_jam;
        cin >> pilihan_jam;
        
        if(pilihan_jam < 1 || pilihan_jam > jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jumlah_jam) {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }
        
        int index_jam = pilihan_jam - 1;
        
        cout << "\n=== EDIT JAM PELAJARAN ===" << endl;
        cout << "Data saat ini:" << endl;
        cout << "Waktu: " << jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[index_jam].waktu << endl;
        cout << "Mata Pelajaran: " << jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[index_jam].mata_pelajaran << endl;
        cout << "Guru: " << jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[index_jam].guru << endl;
        cout << "Ruang: " << jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[index_jam].ruang << endl;
        
        cin.ignore();
        cout << "\nMasukkan data baru:" << endl;
        cout << "Waktu: ";
        getline(cin, jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[index_jam].waktu);
        cout << "Mata Pelajaran: ";
        getline(cin, jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[index_jam].mata_pelajaran);
        cout << "Guru: ";
        getline(cin, jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[index_jam].guru);
        cout << "Ruang: ";
        getline(cin, jadwal_kelas[index_kelas].jadwal_mingguan[index_hari].jam[index_jam].ruang);
        
        cout << "\nJadwal berhasil diupdate!" << endl;
    }
    
    void laporanJadwal() {
        cout << "\n=== LAPORAN JADWAL PELAJARAN ===" << endl;
        
        // Statistik jam pelajaran per mata pelajaran
        int total_jam_matematika = 0, total_jam_fisika = 0, total_jam_kimia = 0;
        int total_jam_biologi = 0, total_jam_bindonesia = 0, total_jam_binggris = 0;
        int total_jam_sejarah = 0, total_jam_geografi = 0, total_jam_ekonomi = 0, total_jam_sosiologi = 0;
        
        for(int k = 0; k < jumlah_kelas_jadwal; k++) {
            for(int h = 0; h < 6; h++) {
                for(int j = 0; j < jadwal_kelas[k].jadwal_mingguan[h].jumlah_jam; j++) {
                    string mapel = jadwal_kelas[k].jadwal_mingguan[h].jam[j].mata_pelajaran;
                    
                    if(mapel.find("Matematika") != string::npos) total_jam_matematika++;
                    else if(mapel.find("Fisika") != string::npos) total_jam_fisika++;
                    else if(mapel.find("Kimia") != string::npos) total_jam_kimia++;
                    else if(mapel.find("Biologi") != string::npos) total_jam_biologi++;
                    else if(mapel.find("B. Indonesia") != string::npos) total_jam_bindonesia++;
                    else if(mapel.find("B. Inggris") != string::npos) total_jam_binggris++;
                    else if(mapel.find("Sejarah") != string::npos) total_jam_sejarah++;
                    else if(mapel.find("Geografi") != string::npos) total_jam_geografi++;
                    else if(mapel.find("Ekonomi") != string::npos) total_jam_ekonomi++;
                    else if(mapel.find("Sosiologi") != string::npos) total_jam_sosiologi++;
                }
            }
        }
        
        cout << "\n=== DISTRIBUSI JAM PELAJARAN PER MATA PELAJARAN ===" << endl;
        cout << left << setw(20) << "Mata Pelajaran" << setw(15) << "Total Jam/Minggu" << endl;
        cout << string(50, '-') << endl;
        cout << left << setw(20) << "Matematika" << setw(15) << total_jam_matematika << endl;
        cout << left << setw(20) << "Fisika" << setw(15) << total_jam_fisika << endl;
        cout << left << setw(20) << "Kimia" << setw(15) << total_jam_kimia << endl;
        cout << left << setw(20) << "Biologi" << setw(15) << total_jam_biologi << endl;
        cout << left << setw(20) << "B. Indonesia" << setw(15) << total_jam_bindonesia << endl;
        cout << left << setw(20) << "B. Inggris" << setw(15) << total_jam_binggris << endl;
        cout << left << setw(20) << "Sejarah" << setw(15) << total_jam_sejarah << endl;
        cout << left << setw(20) << "Geografi" << setw(15) << total_jam_geografi << endl;
        cout << left << setw(20) << "Ekonomi" << setw(15) << total_jam_ekonomi << endl;
        cout << left << setw(20) << "Sosiologi" << setw(15) << total_jam_sosiologi << endl;
        
        cout << "\n=== DAFTAR KELAS YANG TERSEDIA ===" << endl;
        for(int i = 0; i < jumlah_kelas_jadwal; i++) {
            cout << i + 1 << ". " << jadwal_kelas[i].nama_kelas << endl;
        }
        
        cout << "\n=== RINGKASAN JADWAL ===" << endl;
        cout << "Total Kelas: " << jumlah_kelas_jadwal << endl;
        cout << "Hari Aktif: Senin - Sabtu (6 hari)" << endl;
        cout << "Jam Pelajaran: 07.00 - 14.00" << endl;
        cout << "Sistem: Jam pelajaran @ 45 menit" << endl;
    }
    
    // FUNGSI NILAI (EXISTING)
    void tampilkanHeaderRingkas() {
        cout << "\n" << string(108, '=') << endl;
        cout << setw(50) << "SISTEM MANAJEMEN NILAI SISWA SMA" << endl;
        cout << string(108, '=') << endl;
        cout << left << setw(5) << "ID" << setw(18) << "Nama" << setw(10) << "Kelas"
             << setw(6) << "MTK" << setw(6) << "FIS" << setw(6) << "KIM"
             << setw(6) << "BIO" << setw(6) << "B.IND" << setw(6) << "B.ING"
             << setw(6) << "PAI" << setw(6) << "PKN" << setw(6) << "SBK" << setw(6) << "PKWU"
             << setw(10) << "Total" << setw(8) << "Grade" << endl;
        cout << string(108, '-') << endl;
    }
    
    void tampilkanSiswaRingkas(int index) {
        cout << left << setw(5) << siswa[index].id
             << setw(18) << siswa[index].nama
             << setw(10) << siswa[index].kelas
             << setw(6) << fixed << setprecision(1) << siswa[index].matematika.nilai_akhir
             << setw(6) << siswa[index].fisika.nilai_akhir
             << setw(6) << siswa[index].kimia.nilai_akhir
             << setw(6) << siswa[index].biologi.nilai_akhir
             << setw(6) << siswa[index].bahasa_indonesia.nilai_akhir
             << setw(6) << siswa[index].bahasa_inggris.nilai_akhir
             << setw(6) << siswa[index].agama_islam.nilai_akhir
             << setw(6) << siswa[index].pendidikan_kewarganegaraan.nilai_akhir
             << setw(6) << siswa[index].seni_budaya.nilai_akhir
             << setw(6) << siswa[index].prakarya.nilai_akhir
             << setw(10) << setprecision(2) << siswa[index].rata_rata_keseluruhan
             << setw(8) << siswa[index].grade << endl;
    }
    
    void tampilkanSemuaSiswa() {
        tampilkanHeaderRingkas();
        for(int i = 0; i < counter; i++) {
            tampilkanSiswaRingkas(i);
        }
        cout << string(108, '=') << endl;
        cout << "Total Siswa: " << counter << endl;
    }
    
    void tampilkanDetailNilai(int index) {
        cout << "\n=== DETAIL NILAI SISWA ===" << endl;
        cout << "Nama: " << siswa[index].nama << endl;
        cout << "Kelas: " << siswa[index].kelas << endl;
        cout << string(80, '-') << endl;
        
        cout << left << setw(15) << "Mata Pelajaran" 
             << setw(8) << "UK1" << setw(8) << "UK2" << setw(8) << "UK3"
             << setw(10) << "Rata UK" << setw(8) << "UTS" << setw(8) << "UAS"
             << setw(12) << "Nilai Akhir" << endl;
        cout << string(80, '-') << endl;
        
        tampilkanDetailMapel("Matematika", siswa[index].matematika);
        tampilkanDetailMapel("Fisika", siswa[index].fisika);
        tampilkanDetailMapel("Kimia", siswa[index].kimia);
        tampilkanDetailMapel("Biologi", siswa[index].biologi);
        tampilkanDetailMapel("B. Indonesia", siswa[index].bahasa_indonesia);
        tampilkanDetailMapel("B. Inggris", siswa[index].bahasa_inggris);
        tampilkanDetailMapel("Agama Islam", siswa[index].agama_islam);
        tampilkanDetailMapel("Pkn", siswa[index].pendidikan_kewarganegaraan);
        tampilkanDetailMapel("Sbk", siswa[index].seni_budaya);
        tampilkanDetailMapel("Pkwu", siswa[index].prakarya);
        
        cout << string(80, '-') << endl;
        cout << "Rata-rata Keseluruhan: " << fixed << setprecision(2) 
             << siswa[index].rata_rata_keseluruhan << " (Grade: " << siswa[index].grade << ")" << endl;
    }
    
    void tampilkanDetailMapel(string nama_mapel, NilaiMataPelajaran mapel) {
        cout << left << setw(15) << nama_mapel
             << setw(8) << fixed << setprecision(1) << mapel.uk1
             << setw(8) << mapel.uk2
             << setw(8) << mapel.uk3
             << setw(10) << setprecision(2) << mapel.rata_rata_uk
             << setw(8) << setprecision(1) << mapel.uts
             << setw(8) << mapel.uas
             << setw(12) << setprecision(2) << mapel.nilai_akhir << endl;
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
        
        cout << "\n=== INPUT NILAI MATEMATIKA ===" << endl;
        inputNilaiMapel("Matematika", siswa[counter].matematika);
        
        cout << "\n=== INPUT NILAI FISIKA ===" << endl;
        inputNilaiMapel("Fisika", siswa[counter].fisika);
        
        cout << "\n=== INPUT NILAI KIMIA ===" << endl;
        inputNilaiMapel("Kimia", siswa[counter].kimia);
        
        cout << "\n=== INPUT NILAI BIOLOGI ===" << endl;
        inputNilaiMapel("Biologi", siswa[counter].biologi);
        
        cout << "\n=== INPUT NILAI BAHASA INDONESIA ===" << endl;
        inputNilaiMapel("Bahasa Indonesia", siswa[counter].bahasa_indonesia);
        
        cout << "\n=== INPUT NILAI BAHASA INGGRIS ===" << endl;
        inputNilaiMapel("Bahasa Inggris", siswa[counter].bahasa_inggris);
        
        cout << "\n=== INPUT NILAI AGAMA ISLAM ===" << endl;
        inputNilaiMapel("Agama Islam", siswa[counter].agama_islam);
        
        cout << "\n=== INPUT NILAI PENDIDIKAN KEWARGANEGARAAN ===" << endl;
        inputNilaiMapel("Pendidikan kewarganegaraan", siswa[counter].pendidikan_kewarganegaraan);
        
        cout << "\n=== INPUT NILAI SENI BUDAYA ===" << endl;
        inputNilaiMapel("Seni Budaya", siswa[counter].seni_budaya);
        
        cout << "\n=== INPUT NILAI PRAKARYA ===" << endl;
        inputNilaiMapel("Prakarya", siswa[counter].prakarya);
        
        
        hitungTotalRataRata(counter);
        tentukanGrade(counter);
        counter++;
        
        cout << "\nData siswa berhasil ditambahkan!" << endl;
    }
    
    void inputNilaiMapel(string nama_mapel, NilaiMataPelajaran &mapel) {
        cout << "Nilai UK 1: ";
        cin >> mapel.uk1;
        cout << "Nilai UK 2: ";
        cin >> mapel.uk2;
        cout << "Nilai UK 3: ";
        cin >> mapel.uk3;
        cout << "Nilai UTS: ";
        cin >> mapel.uts;
        cout << "Nilai UAS: ";
        cin >> mapel.uas;
        
        hitungNilaiAkhir(mapel);
        
        cout << "Rata-rata UK: " << fixed << setprecision(2) << mapel.rata_rata_uk << endl;
        cout << "Nilai Akhir " << nama_mapel << ": " << mapel.nilai_akhir << endl;
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
        tampilkanDetailNilai(index);
        
        int pilihan_mapel;
        cout << "\nPilih mata pelajaran yang akan diedit:" << endl;
        cout << "1.  Matematika" << endl;
        cout << "2.  Fisika" << endl;
        cout << "3.  Kimia" << endl;
        cout << "4.  Biologi" << endl;
        cout << "5.  Bahasa Indonesia" << endl;
        cout << "6.  Bahasa Inggris" << endl;
        cout << "7.  Agama Islam" << endl;
        cout << "8.  Pendidikan Kewarganegaraan" << endl;
        cout << "9.  Seni Budaya" << endl;
        cout << "10. Prakarya" << endl;
        cout << "11. Edit Semua Mata Pelajaran" << endl;
        cout << "Pilihan: ";
        cin >> pilihan_mapel;
        
        switch(pilihan_mapel) {
            case 1:
                cout << "\n=== EDIT NILAI MATEMATIKA ===" << endl;
                inputNilaiMapel("Matematika", siswa[index].matematika);
                break;
            case 2:
                cout << "\n=== EDIT NILAI FISIKA ===" << endl;
                inputNilaiMapel("Fisika", siswa[index].fisika);
                break;
            case 3:
                cout << "\n=== EDIT NILAI KIMIA ===" << endl;
                inputNilaiMapel("Kimia", siswa[index].kimia);
                break;
            case 4:
                cout << "\n=== EDIT NILAI BIOLOGI ===" << endl;
                inputNilaiMapel("Biologi", siswa[index].biologi);
                break;
            case 5:
                cout << "\n=== EDIT NILAI BAHASA INDONESIA ===" << endl;
                inputNilaiMapel("Bahasa Indonesia", siswa[index].bahasa_indonesia);
                break;
            case 6:
                cout << "\n=== EDIT NILAI BAHASA INGGRIS ===" << endl;
                inputNilaiMapel("Bahasa Inggris", siswa[index].bahasa_inggris);
                break;
            case 7:
                cout << "\n=== EDIT NILAI AGAMA ISLAM ===" << endl;
                inputNilaiMapel("Agama Islam", siswa[index].agama_islam);
                break;
            case 8:
                cout << "\n=== EDIT NILAI PENDIDIKAN KEWARGANEGARAAN ===" << endl;
                inputNilaiMapel("Pendidikan Kewarganegaraan", siswa[index].pendidikan_kewarganegaraan);
                break;
            case 9:
                cout << "\n=== EDIT NILAI SENI BUDAYA ===" << endl;
                inputNilaiMapel("Seni Budaya", siswa[index].seni_budaya);
                break;
            case 10:
                cout << "\n=== EDIT NILAI PRAKARYA ===" << endl;
                inputNilaiMapel("Prakarya", siswa[index].prakarya);
                break;
            case 11:
                cout << "\n=== EDIT SEMUA NILAI ===" << endl;
                inputNilaiMapel("Matematika", siswa[index].matematika);
                inputNilaiMapel("Fisika", siswa[index].fisika);
                inputNilaiMapel("Kimia", siswa[index].kimia);
                inputNilaiMapel("Biologi", siswa[index].biologi);
                inputNilaiMapel("Bahasa Indonesia", siswa[index].bahasa_indonesia);
                inputNilaiMapel("Bahasa Inggris", siswa[index].bahasa_inggris);
                inputNilaiMapel("Agama Islam", siswa[index].agama_islam);
                inputNilaiMapel("Pendidikan Kewarganegaraan", siswa[index].pendidikan_kewarganegaraan);
                inputNilaiMapel("Seni Budaya", siswa[index].seni_budaya);
                inputNilaiMapel("Prakarya", siswa[index].prakarya);
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                return;
        }
        
        hitungTotalRataRata(index);
        tentukanGrade(index);
        
        cout << "Nilai berhasil diupdate!" << endl;
    }
    
    void lihatDetailNilaiSiswa() {
        int id;
        cout << "\n=== LIHAT DETAIL NILAI SISWA ===" << endl;
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
        
        tampilkanDetailNilai(index);
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
                
                tampilkanHeaderRingkas();
                for(int i = 0; i < counter; i++) {
                    if(siswa[i].nama.find(nama) != string::npos) {
                        tampilkanSiswaRingkas(i);
                        ditemukan = true;
                    }
                }
                break;
            }
            case 2: {
                int id;
                cout << "Masukkan ID siswa: ";
                cin >> id;
                
                for(int i = 0; i < counter; i++) {
                    if(siswa[i].id == id) {
                        tampilkanDetailNilai(i);
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
                
                tampilkanHeaderRingkas();
                for(int i = 0; i < counter; i++) {
                    if(siswa[i].kelas == kelas) {
                        tampilkanSiswaRingkas(i);
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
                for(int i = 0; i < counter - 1; i++) {
                    for(int j = 0; j < counter - i - 1; j++) {
                        if(siswa[j].rata_rata_keseluruhan < siswa[j + 1].rata_rata_keseluruhan) {
                            swap(siswa[j], siswa[j + 1]);
                        }
                    }
                }
                cout << "Data berhasil diurutkan berdasarkan rata-rata!" << endl;
                break;
                
            case 3:
                for(int i = 0; i < counter - 1; i++) {
                    for(int j = 0; j < counter - i - 1; j++) {
                        if(siswa[j].total_nilai_akhir < siswa[j + 1].total_nilai_akhir) {
                            swap(siswa[j], siswa[j + 1]);
                        }
                    }
                }
                cout << "Data berhasil diurutkan berdasarkan total nilai!" << endl;
                break;
                
            case 4:
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
            total_rata_rata += siswa[i].rata_rata_keseluruhan;
            
            if(siswa[i].rata_rata_keseluruhan > nilai_tertinggi) 
                nilai_tertinggi = siswa[i].rata_rata_keseluruhan;
            if(siswa[i].rata_rata_keseluruhan < nilai_terendah) 
                nilai_terendah = siswa[i].rata_rata_keseluruhan;
            
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
        cout << "Grade A: " << grade_A << " siswa (" << fixed << setprecision(1) 
             << (grade_A * 100.0 / counter) << "%)" << endl;
        cout << "Grade B: " << grade_B << " siswa (" << (grade_B * 100.0 / counter) << "%)" << endl;
        cout << "Grade C: " << grade_C << " siswa (" << (grade_C * 100.0 / counter) << "%)" << endl;
        cout << "Grade D: " << grade_D << " siswa (" << (grade_D * 100.0 / counter) << "%)" << endl;
        cout << "Grade E: " << grade_E << " siswa (" << (grade_E * 100.0 / counter) << "%)" << endl;
        
        cout << "\n=== KETERANGAN SISTEM PENILAIAN ===" << endl;
        cout << "Nilai Akhir = (Rata-rata UK × 30%) + (UTS × 35%) + (UAS × 35%)" << endl;
        cout << "UK = Ulangan Kecil, UTS = Ulangan Tengah Semester, UAS = Ulangan Akhir Semester" << endl;
        
        tampilkanSemuaSiswa();
    }
    
    void tampilkanMenu() {
        cout << "\n" << string(60, '=') << endl;
        cout << setw(45) << "SISTEM MANAJEMEN NILAI & JADWAL SMA" << endl;
        cout << setw(35) << "dengan UK, UTS, UAS" << endl;
        cout << string(60, '=') << endl;
        cout << "=== MENU NILAI ===" << endl;
        cout << "1.  Tampilkan Semua Siswa (Ringkas)" << endl;
        cout << "2.  Input Nilai Siswa Baru" << endl;
        cout << "3.  Edit Nilai Siswa" << endl;
        cout << "4.  Lihat Detail Nilai Siswa" << endl;
        cout << "5.  Cari Siswa" << endl;
        cout << "6.  Sorting Data" << endl;
        cout << "7.  Laporan Nilai" << endl;
        cout << "8.  Lihat Jadwal Kelas" << endl;
        cout << "9.  Lihat Jadwal Siswa" << endl;
        cout << "10. Cari Jadwal Mata Pelajaran" << endl;
        cout << "11. Edit Jadwal Kelas" << endl;
        cout << "12. Laporan Jadwal" << endl;
        cout << "\n0. Keluar" << endl;
        cout << string(60, '=') << endl;
        cout << "Total Siswa: " << counter << " | Total Kelas: " << jumlah_kelas_jadwal << endl;
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
                    lihatDetailNilaiSiswa();
                    break;
                case 5:
                    cariSiswa();
                    break;
                case 6:
                    sortingSiswa();
                    break;
                case 7:
                    laporanNilai();
                    break;
                case 8:
                    tampilkanJadwalKelas();
                    break;
                case 9:
                    tampilkanJadwalSiswa();
                    break;
                case 10:
                    cariJadwalMapel();
                    break;
                case 11:
                    editJadwalKelas();
                    break;
                case 12:
                    laporanJadwal();
                    break;
                case 0:
                    cout << "\nTerima kasih telah menggunakan Sistem Manajemen Nilai & Jadwal SMA!" << endl;
                    break;
                default:
                    cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            }
            
            
            cout << "\nApakah Anda ingin melanjutkan? (y/n): ";
            char lanjut;
            cin >> lanjut;
            if (lanjut != 'y' && lanjut != 'Y') {
                break; // Keluar dari loop jika pengguna tidak ingin melanjutkan
            }
        } while (true); // Loop terus berjalan sampai pengguna memilih untuk keluar
    }
    
};

int main() {
    SistemNilai sistem; // Membuat objek dari kelas SistemNilai
    sistem.jalankan(); // Menjalankan sistem
    return 0; // Mengembalikan 0 menandakan program selesai


}

