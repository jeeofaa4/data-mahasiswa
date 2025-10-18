#include <iostream>
using namespace std;

struct tanggal {
    int hari;
    int bulan;
    int tahun;
};

struct mahasiswa {
    string nama;
    int umur;
    string jurusan;
};

struct nilai {
    float uts;
    float uas;
    float tugas;
};


void inputData (mahasiswa &w,tanggal &l,nilai &n)
{
cout << "masukkan nama anda = ";
cin >> w.nama;
cout << "masukkan umur anda = ";
cin >> w.umur;
cout << "masukkan jurusan anda = ";
cin >> w.jurusan;
cout << "masukkan tanggal lahir (hari) anda = ";
cin >> l.hari;
cout << "masukkan tanggal lahir (bulan) anda = ";
cin >> l.bulan;
cout << "masukkan tanggal lahir (tahun) anda = ";
cin >> l.tahun;
cout << "masukkan nilai uts anda = ";
cin >> n.uts;
cout << "masukkan  nilai uas anda = ";
cin >> n.uas;
cout << "masukkan nilai tugas anda = ";
cin >>n.tugas;
}

float hitungNilaiAkhir(float uts, float uas, float tugas) {
    return (uts * 0.35) + (uas * 0.4) + (tugas * 0.25);
}


void tampilData (mahasiswa w,tanggal l,nilai n)
{
    cout << "nama           :" << w.nama << endl;
    cout << "umur           :" << w.umur << endl;
    cout << "jurusan        :" << w.jurusan << endl;
    cout << "tanggal lahir  :" << l.hari << "/" << l.bulan << "/" << l.tahun << endl;
    cout << "nilai uts      :" << n.uts << endl;
    cout << "nilai uas      :" << n.uas << endl;
    cout << "nilai tugas    :" << n.tugas << endl;

float nilaiAkhir =hitungNilaiAkhir(n.uts,n.uas,n.tugas);
cout << "nilai akhir anda adalah : " << nilaiAkhir << endl;
}

int main() {
    mahasiswa w[3];
    nilai n[3];
    tanggal l[3];

    cout << "=== INPUT DATA 3 MAHASISWA ===" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "\n--- Mahasiswa ke-" << i + 1 << " ---" << endl;
        inputData(w[i], l[i], n[i]);
    }

    cout << "\n\n=== HASIL DATA MAHASISWA ===" << endl;
    for (int i = 0; i < 3; i++) {
        tampilData(w[i],l[i], n[i]);
    }

    return 0;
}

