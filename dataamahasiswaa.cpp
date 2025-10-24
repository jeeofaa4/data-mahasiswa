#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct tanggal {
    int hari;
    int bulan;
    int tahun;
};
struct nilai {
    float uts;
    float uas;
    float tugas;
    float mtk;
    float ipa;
    float bin;
    float big;
};

struct mahasiswa {
    string nama;
    int umur;
    nilai Nilai; 
    string jurusan;
    string nisn;
    float nilaiMapel;
    float nilaiUjian;
    float nilaiAkhir;
};

mahasiswa w[3];
nilai n[3];
tanggal l[3];

float hitungNilaiMapel(nilai n) {
    return (n.mtk *0.35f) + (n.ipa *0.25f) + (n.bin *0.20f) + (n.big *0.20f);
}
float hitungNilaiUjian(nilai n) {
    return (n.uts * 0.35f) + (n.uas *0.4f) + (n.tugas *0.25f);
}
string trim(string s) {
    while(!s.empty() && s.front()==' ') s.erase(0,1);
    while(!s.empty() && s.back()==' ') s.pop_back();
    return s;
}

void tambahDataSiswa(mahasiswa &w, tanggal &l, nilai &n) {

    cin.ignore(); 
    cout << "masukkan nama anda = ";
    getline(cin, w.nama);
    cout << "masukkan umur anda = ";
    cin >> w.umur;
    cin.ignore();
    cout << "masukkan jurusan anda = ";
    getline(cin, w.jurusan);

    do {
        cout << "masukkan NISN anda (16 digit) = ";
        getline(cin, w.nisn);
        if (w.nisn.length() != 16) 
            cout << "NISN harus 16 digit, ulangi!\n";
    } while (w.nisn.length() != 16);

    cout << "masukkan tanggal lahir (hari) anda = ";
    cin >> l.hari;
    cout << "masukkan tanggal lahir (bulan) anda = ";
    cin >> l.bulan;
    cout << "masukkan tanggal lahir (tahun) anda = ";
    cin >> l.tahun;

    cout << "masukkan nilai mtk anda = ";
    cin >> n.mtk;
    cout << "masukkan nilai ipa anda = ";
    cin >> n.ipa;
    cout << "masukkan nilai bin anda = ";
    cin >> n.bin;
    cout << "masukkan nilai big anda = ";
    cin >> n.big;
    cout << "masukkan nilai uts anda = ";
    cin >> n.uts;
    cout << "masukkan nilai uas anda = ";
    cin >> n.uas;
    cout << "masukkan nilai tugas anda = ";
    cin >> n.tugas;

    w.nilaiMapel = hitungNilaiMapel(n);
    w.nilaiUjian = hitungNilaiUjian(n);
    w.nilaiAkhir = (w.nilaiMapel + w.nilaiUjian) / 2;

    ofstream file("siswa.txt", ios::app);
    file << "---------------------------\n";
    file << "nama : " << w.nama << endl;
    file << "umur : " << w.umur << endl;
    file << "jurusan : " << w.jurusan << endl;
    file << "NISN : " << w.nisn << endl;
    file << "tanggal lahir : " << l.hari << "/" << l.bulan << "/" << l.tahun << endl;
    file << "nilai mtk : " << n.mtk << endl;
    file << "nilai ipa : " << n.ipa << endl;
    file << "nilai bin : " << n.bin << endl;
    file << "nilai big : " << n.big << endl;
    file << "nilai uts : " << n.uts << endl;
    file << "nilai uas : " << n.uas << endl;
    file << "nilai tugas : " << n.tugas << endl;
    file << "nilaiAkhir : " << w.nilaiAkhir << endl;
    file << "---------------------------\n";
    file.close();
}

void tampilDataSiswa() {
    ifstream file("siswa.txt");
    if(!file.is_open()){
        cout << "File tidak ditemukan!\n";
        return;
    }
    string data;
    cout << "\n-----DATA SISWA-----\n";
    while(getline(file, data)) {
        cout << data << endl;
    }
    file.close();
}

void cariSiswa() {
    cout << "Masukkan NISN Yang DiCari = ";
    string nisn;
    getline(cin, nisn);
    nisn = trim(nisn);

    ifstream file("siswa.txt");
    if(!file.is_open()){
        cout << "File Tidak Dapat DiTemukan!" << endl;
        return;
    }

    string line;
    bool ketemu = false;
    string nisnFile;

    while(getline(file,line)) {
        if(line.find("NISN : ") != string::npos) {
            nisnFile = trim(line.substr(7));
        }
        if(nisnFile == nisn) {
            ketemu = true;
            cout << "\n-----DATA SISWA DITEMUKAN-----\n";
            while(getline(file,line) && line != "-------------------\n") {
                cout << line << endl;
            }
            break;
        }
    }
    file.close();
    if(!ketemu) cout << "Mahasiswa Dengan NISN " << nisn << " tidak ditemukan.\n";
}

void ranking() {
    ifstream file("siswa.txt");
    if(!file.is_open()) return;

    string line;
    string nama[100], nisn[100];
    float nilaiAkhir[100];
    int jumlah = 0;

    while(getline(file, line)) {
        line = trim(line);
        if(line.find("nama : ") != string::npos) nama[jumlah] = trim(line.substr(7));
        else if(line.find("NISN : ") != string::npos) nisn[jumlah] = trim(line.substr(7));
        else if(line.find("nilaiAkhir : ") != string::npos) {
            nilaiAkhir[jumlah] = stof(trim(line.substr(13)));
            jumlah++;
        }
    }
    file.close();

    // bubble sort descending
    for(int i=0;i<jumlah-1;i++){
        for(int j=0;j<jumlah-i-1;j++){
            if(nilaiAkhir[j] < nilaiAkhir[j+1]){
                swap(nilaiAkhir[j], nilaiAkhir[j+1]);
                swap(nama[j], nama[j+1]);
                swap(nisn[j], nisn[j+1]);
            }
        }
    }

    cout << "\n=== RANKING SISWA ===\n";
    for(int i=0;i<jumlah;i++){
        cout << i+1 << ". " << nama[i] << " | NISN: " << nisn[i];
        cout << " | Nilai Akhir: " << nilaiAkhir[i] << endl;
    }
}

int main() {
    ofstream file("siswa.txt");
    file.close();
    cout << "=== INPUT DATA 3 MAHASISWA ===\n";
    for(int i=0;i<3;i++){
        cout << "\n--- Mahasiswa ke-" << i+1 << " ---\n";
        tambahDataSiswa(w[i], l[i], n[i]);
    }

    cout << "\n=== HASIL DATA MAHASISWA ===\n";
    tampilDataSiswa();

    cout << "\n=== PENCARIAN SISWA BERDASARKAN NISN ===\n";
    cariSiswa();

    cout << "\n=== RANKING SISWA ===\n";
    ranking();

    return 0;
}
