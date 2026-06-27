#include <iostream>
using namespace std;

//KONSTANTA WILAYAH

const int JUMLAH_WILAYAH = 4;

const string KODE_WILAYAH[JUMLAH_WILAYAH] = {
    "051", "034", "074", "082"
};

//STRUCT UNTUK SENSOR DAN NODE

struct Sensor {
    float temperature;
    float humidity;
    int airQuality;
    bool smoke;
    float noise;
};

struct Node {

    string userID;
    string nama;

    Sensor sensor;

    float monitoringScore;

    Node* next;
};

//STRUCT DARI LINKED LIST
struct LinkedList {

    Node* head;
    int size;

    LinkedList() {

        head = nullptr;
        size = 0;
    }
};

//FUNGSI UNTUK HELPER

// Uppercase manual
string toUpper(string str) {
    for (int i = 0; i < (int)str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
    return str;
}

// Cek wilayah
int cekWilayah(const string& id) {
    for (int i = 0; i < JUMLAH_WILAYAH; i++) {
        if (id.substr(0, 3) == KODE_WILAYAH[i]) {
            return i + 1;
        }
    }
    return -1;
}

// Validasi ID
bool validID(const string& id) {
    if (id.length() < 4)
        return false;
    for (int i = 0; i < (int)id.length(); i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }
    return cekWilayah(id) != -1;
}

// Hitung monitoring score
float hitungScore(const Sensor& s) {
    int ideal = 0;
    if (s.temperature >= 20 && s.temperature <= 27)
        ideal++;
    if (s.humidity >= 40 && s.humidity <= 60)
        ideal++;
    if (s.airQuality >= 0 && s.airQuality <= 50)
        ideal++;
    if (s.smoke == 0)
        ideal++;
    if (s.noise >= 30 && s.noise <= 55)
        ideal++;
    return (float)ideal / 5 * 100;
}

// Validasi sensor
bool validSensor(const Sensor& s) {
    if (s.temperature < -10 || s.temperature > 50)
        return false;
    if (s.humidity < 0 || s.humidity > 100)
        return false;
    if (s.airQuality < 0 || s.airQuality > 500)
        return false;
    if (s.noise < 0 || s.noise > 120)
        return false;
    return true;
}

// Garis
void cetakGaris() {
    cout << "----------------------------------------------"
         << endl;
}

// Header
void cetakHeader() {
    cout << "=============================================="
         << endl;
    cout << "    SISTEM MONITORING IOT - SMART HOME        "
         << endl;
    cout << "    UNIVERSITAS BRAWIJAYA                     "
         << endl;
    cout << "=============================================="
         << endl;
}

// Menu
void cetakMenu() {
    cout << endl;
    cetakGaris();
    cout << "  MENU UTAMA" << endl;
    cetakGaris();
    cout << "  1. Tambah Pelanggan" << endl;
    cout << "  2. Cari Pelanggan" << endl;
    cout << "  3. Update Pelanggan" << endl;
    cout << "  4. Hapus Pelanggan" << endl;
    cout << "  5. Tampilkan Laporan" << endl;
    cout << "  0. Keluar" << endl;

    cetakGaris();

    cout << "  Pilihan : ";
}

//OPERASI LINKED LIST

// Cek ID
bool idSudahAda(LinkedList& ll, const string& id) {
    Node* curr = ll.head;
    while (curr != nullptr) {
        if (curr->userID == id)
            return true;
        curr = curr->next;
    }
    return false;
}

// Cari user
Node* cariUser(LinkedList& ll, const string& id) {
    Node* curr = ll.head;
    while (curr != nullptr) {
        if (curr->userID == id)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

//FUNGSI UNTUK MENAMPILKAN DETAIL

void tampilDetail(Node* node, int ranking) {
    int wilayah = cekWilayah(node->userID);
    cetakGaris();

    cout << "  Peringkat        : "
         << ranking << endl;

    cout << "  User ID          : "
         << node->userID << endl;

    cout << "  Nama Pelanggan   : "
         << node->nama << endl;

    cout << "  Monitoring Score : "
         << node->monitoringScore << "%" << endl;

    cout << "  Wilayah          : "
         << wilayah << endl;

    cout << "  Data Sensor :" << endl;

    cout << "    Temperature : "
         << node->sensor.temperature << " C" << endl;

    cout << "    Humidity    : "
         << node->sensor.humidity << "%" << endl;

    cout << "    Air Quality : "
         << node->sensor.airQuality << endl;

    cout << "    Smoke       : "
         << node->sensor.smoke << endl;

    cout << "    Noise       : "
         << node->sensor.noise << " dB" << endl;
}

//FUNGSI UNTUK MELAKUKAN BUBBLE SORT ASCENDING

void bubbleSort(LinkedList& ll) {
    if (ll.head == nullptr)
        return;
    bool swapped;
    do {
        swapped = false;
        Node* curr = ll.head;
        while (curr->next != nullptr) {
            // ASCENDING
            if (curr->monitoringScore >
                curr->next->monitoringScore) {
                swap(curr->userID,
                     curr->next->userID);
                swap(curr->nama,
                     curr->next->nama);
                swap(curr->sensor,
                     curr->next->sensor);
                swap(curr->monitoringScore,
                     curr->next->monitoringScore);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

//FUNGSI UNTUK MENAMBAH USER

void tambahUser(LinkedList& ll) {
    cout << endl;
    cetakGaris();
    cout << "  TAMBAH PELANGGAN" << endl;
    cetakGaris();
    cout << "  Kode Wilayah :" << endl;
    cout << "  051 = Wilayah 1" << endl;
    cout << "  034 = Wilayah 2" << endl;
    cout << "  074 = Wilayah 3" << endl;
    cout << "  082 = Wilayah 4" << endl;

    cout << endl;

    string id;

    cout << "  Masukkan User ID : ";
    cin >> id;

    if (!validID(id)) {
        cout << endl;
        cout << "  [ERROR] User ID tidak valid!"
             << endl;

        cout << "  Gunakan awalan : "
             << "051 / 034 / 074 / 082"
             << endl;
        return;
    }

    if (idSudahAda(ll, id)) {
        cout << endl;
        cout << "  [ERROR] ID sudah terdaftar!"
             << endl;
        return;
    }

    string nama;
    cout << "  Nama : ";
    cin.ignore();
    getline(cin, nama);
    nama = toUpper(nama);
    Sensor s;

    cout << "  Temperature : ";
    cin >> s.temperature;

    cout << "  Humidity    : ";
    cin >> s.humidity;

    cout << "  Air Quality : ";
    cin >> s.airQuality;
    int smokeInput;
    cout << "  Smoke (0/1) : ";
    cin >> smokeInput;
    s.smoke = (smokeInput == 1);
    cout << "  Noise       : ";
    cin >> s.noise;

    if (!validSensor(s)) {
        cout << endl;
        cout << "  [ERROR] Data sensor tidak valid!"
             << endl;
        return;
    }
    Node* baru = new Node();
    baru->userID = id;
    baru->nama = nama;
    baru->sensor = s;
    baru->monitoringScore =
        hitungScore(s);
    baru->next = nullptr;

    // Insert akhir
    if (ll.head == nullptr) {
        ll.head = baru;

    } else {
        Node* curr = ll.head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = baru;
    }
    ll.size++;
    cout << endl;

    cout << "  Berhasil menambahkan pelanggan baru"
         << endl;
    cout << "  User ID : "
         << baru->userID << endl;
    cout << "  Nama Pelanggan : "
         << baru->nama << endl;
    cout << "  Monitoring Score : "
         << baru->monitoringScore << "%"
         << endl;
}

//FUNGSI UNTUK MENCARI USER

void menuCariUser(LinkedList& ll) {
    cout << endl;
    cetakGaris();

    cout << "  CARI PELANGGAN" << endl;
    cetakGaris();

    string id;
    cout << "  Masukkan User ID : ";
    cin >> id;
    Node* hasil = cariUser(ll, id);
    if (hasil == nullptr) {
        cout << "  User tidak ditemukan"
             << endl;
    } else {
        cout << "  User ditemukan"
             << endl;
        tampilDetail(hasil, 0);
    }
}

//UNTUK MENGUPDATE USER

void updateUser(LinkedList& ll) {
    cout << endl;
    cetakGaris();

    cout << "  UPDATE PELANGGAN" << endl;
    cetakGaris();

    string id;
    cout << "  Masukkan User ID : ";
    cin >> id;
    Node* target = cariUser(ll, id);

    if (target == nullptr) {
        cout << "  User not found"
             << endl;
        return;
    }

    cout << "  User found"
         << endl;
    string nama;
    cout << "  Nama Baru : ";
    cin.ignore();
    getline(cin, nama);
    nama = toUpper(nama);
    Sensor s;
    cout << "  Temperature : ";
    cin >> s.temperature;
    cout << "  Humidity    : ";
    cin >> s.humidity;
    cout << "  Air Quality : ";
    cin >> s.airQuality;
    int smokeInput;
    cout << "  Smoke (0/1) : ";
    cin >> smokeInput;
    s.smoke = (smokeInput == 1);
    cout << "  Noise       : ";
    cin >> s.noise;

    if (!validSensor(s)) {
        cout << endl;
        cout << "  [ERROR] Data sensor tidak valid!"
             << endl;
        return;
    }

    target->nama = nama;
    target->sensor = s;
    target->monitoringScore =
        hitungScore(s);
    cout << endl;
    cout << "  New Monitoring Score : "
         << target->monitoringScore << "%"
         << endl;
}

//UNTUK MENGHAPUS USER

void hapusUser(LinkedList& ll) {
    cout << endl;
    cetakGaris();

    cout << "  HAPUS PELANGGAN" << endl;
    cetakGaris();

    string id;
    cout << "  Masukkan User ID : ";
    cin >> id;
    if (ll.head == nullptr) {
        cout << "  User not found"
             << endl;
        return;
    }
    // Hapus head
    if (ll.head->userID == id) {
        Node* hapus = ll.head;
        ll.head = ll.head->next;
        delete hapus;
        ll.size--;
        cout << "  User dengan ID "
             << id
             << " berhasil dihapus dari sistem"
             << endl;
        return;
    }
    Node* prev = ll.head;
    Node* curr = ll.head->next;
    while (curr != nullptr) {
        if (curr->userID == id) {
            prev->next = curr->next;
            delete curr;
            ll.size--;
            cout << "  User dengan ID "
                 << id
                 << " berhasil dihapus dari sistem"
                 << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "  User not found"
         << endl;
}

//MENAMPILKAN LAPORAN
void showLaporan(LinkedList& ll) {
    cout << endl;
    cetakGaris();
    cout << "  LAPORAN MONITORING IOT"
         << endl;
    cetakGaris();
    if (ll.head == nullptr) {
        cout << "  Belum ada data pelanggan."
             << endl;
        return;
    }

    // Sorting ascending
    bubbleSort(ll);

    // Statistik
    float totalScore = 0;
    int userIdeal = 0;
    int tempIdeal = 0;
    int humIdeal = 0;
    int aqIdeal = 0;
    int smokeIdeal = 0;
    int noiseIdeal = 0;
    Node* curr = ll.head;
    while (curr != nullptr) {
        totalScore += curr->monitoringScore;
        if (curr->monitoringScore == 100)
            userIdeal++;
        Sensor s = curr->sensor;
        if (s.temperature >= 20 &&
            s.temperature <= 27)
            tempIdeal++;
        if (s.humidity >= 40 &&
            s.humidity <= 60)
            humIdeal++;
        if (s.airQuality >= 0 &&
            s.airQuality <= 50)
            aqIdeal++;
        if (s.smoke == 0)
            smokeIdeal++;
        if (s.noise >= 30 &&
            s.noise <= 55)
            noiseIdeal++;
        curr = curr->next;
    }
    int tidakIdeal =
        ll.size - userIdeal;
    float rataRata =
        totalScore / ll.size;
    // Tampilkan statistik
    cout << "  Statistik Monitoring"
         << endl;
    cout << "  Jumlah User Dengan Pembacaan Ideal : "
         << userIdeal << endl;
    cout << "  Jumlah User Dengan Pembacaan Tidak Ideal : "
         << tidakIdeal << endl;
    cout << "  Total Pelanggan : "
         << ll.size << endl;
    cout << "  Rata-rata Score : "
         << rataRata << "%"
         << endl;
    cout << endl;
    cout << "  Rekap Sensor :"
         << endl;
    cout << "  Temperature : "
         << tempIdeal << " rumah"
         << endl;
    cout << "  Humidity    : "
         << humIdeal << " rumah"
         << endl;
    cout << "  Air Quality : "
         << aqIdeal << " rumah"
         << endl;
    cout << "  Smoke       : "
         << smokeIdeal << " rumah"
         << endl;
    cout << "  Noise       : "
         << noiseIdeal << " rumah"
         << endl;
    // Tampilkan ranking
    curr = ll.head;
    int ranking = 1;
    while (curr != nullptr) {
        tampilDetail(curr, ranking);
        curr = curr->next;
        ranking++;
    }
    cetakGaris();
}

//BAGIAN MAIN

int main() {
    LinkedList ll;
    int pilihan;
    cetakHeader();
    do {
        cetakMenu();
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tambahUser(ll);
                break;
            case 2:
                menuCariUser(ll);
                break;
            case 3:
                updateUser(ll);
                break;
            case 4:
                hapusUser(ll);
                break;
            case 5:
                showLaporan(ll);
                break;
            case 0:
                cout << endl;
                cout << "  Terima kasih telah menggunakan sistem!"
                     << endl;
                break;
            default:
                cout << "  [ERROR] Pilihan tidak valid!"
                     << endl;
        }
    } while (pilihan != 0);
    // Hapus memori
    Node* curr = ll.head;
    while (curr != nullptr) {
        Node* hapus = curr;
        curr = curr->next;
        delete hapus;
    }
    return 0;
}