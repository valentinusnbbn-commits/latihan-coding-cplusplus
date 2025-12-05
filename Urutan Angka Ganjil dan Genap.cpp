#include <iostream>
using namespace std;

int main(){
    // Array untuk menyimpan bilangan ganjil dan genap
    int ganjil[1001];
    int genap[1001];
    
    int n;              // banyaknya input
    int angka;          // variabel untuk menampung setiap angka yang diinput
    int countGanjil = 0; // jumlah elemen ganjil yang sudah masuk ke array
    int countGenap = 0;  // jumlah elemen genap yang sudah masuk ke array
    
    cin >> n; // input jumlah data
    
    // proses membaca n angka
    for (int i = 0; i < n; i++){
        cin >> angka; // baca angka
        
        // pengecekan apakah angka genap atau ganjil
        if (angka % 2 == 0){
            genap[countGenap] = angka; // simpan ke array genap
            countGenap++;               // naikkan counter genap
        }
        else{
            ganjil[countGanjil] = angka; // simpan ke array ganjil
            countGanjil++;                // naikkan counter ganjil
        }
    }
    
    int jumlahGanjil = 0; // total nilai bilangan ganjil
    int jumlahGenap = 0;  // total nilai bilangan genap
    
    // hitung total bilangan ganjil
    for (int i = 0; i < countGanjil; i++)
        jumlahGanjil += ganjil[i];
    
    // hitung total bilangan genap
    for (int i = 0; i < countGenap; i++)
        jumlahGenap += genap[i];
    
    // bandingkan total kedua kelompok
    // jika total ganjil lebih besar, tampilkan ganjil dulu lalu genap
    if (jumlahGanjil > jumlahGenap){
        for (int i = 0; i < countGanjil; i++)
            cout << ganjil[i] << " ";
        cout << endl;
        
        for (int i = 0; i < countGenap; i++)
            cout << genap[i] << " ";
    }
    
    // jika total genap lebih besar, tampilkan genap dulu lalu ganjil
    if (jumlahGenap > jumlahGanjil){
        for (int i = 0; i < countGenap; i++)
            cout << genap[i] << " ";
        cout << endl;
        
        for (int i = 0; i < countGanjil; i++)
            cout << ganjil[i] << " ";
    }
}
