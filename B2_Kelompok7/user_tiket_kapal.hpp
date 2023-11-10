#include <iostream>
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

struct pesanan
{
    int id;
    string username;
    string asal;
    string tujuan;
    int harga;
    int jumlah;
};

struct tiketUser
{
    pesanan data;
    tiketUser *next;
};

struct bayar
{
    int id;
    string username;
    string asal;
    string tujuan;
    int harga;
    int jumlah;
    int total;
    bayar *next = NULL;
    bayar *prev = NULL;
};

bool isEmptyT(tiket *head, tiket *tail)
{

    if (head == NULL && tail == NULL)
    {
        return true;
    }
    return false;
}

// Fungsi untuk membaca data dari file CSV
void loadTiket(tiket *&head, tiket *&tail)
{
    ifstream file("B2_Kelompok7/data_tiket.csv");

    if (!file.is_open())
    {
        cout << "File data_tiket.csv tidak ditemukan." << endl;
        return;
    }

    string line;
    tiket *current = nullptr; // Pointer tambahan
    while (getline(file, line))
    {
        if (line.empty())
        {
            cout << "Data Not Found" << endl;
            return;
        }
        else
        {

            stringstream ss(line);
            string id_str, asal, tujuan, harga_Str;
            getline(ss, id_str, ',');
            getline(ss, asal, ',');
            getline(ss, tujuan, ',');
            getline(ss, harga_Str, ',');

            int harga = stoi(harga_Str); // Mengonversi harga dari string ke integer
            int id = stoi(id_str);       // Mengonversi harga dari string ke integer

            tiket *temp = new tiket;
            temp->id = id;
            temp->asal = asal;
            temp->tujuan = tujuan;
            temp->harga = harga;
            temp->next = nullptr;
            temp->prev = current; // Mengatur node sebelumnya

            if (head == nullptr)
            {
                // Jika *head masih NULL, maka elemen baru menjadi head
                head = temp;
                temp->prev = nullptr; // Set prev dari elemen baru ke nullptr
                tail = temp;          // elemen baru juga menjadi tail karena ini elemen pertama
            }
            else
            {
                // Jika *head sudah ada, hubungkan elemen baru dengan yang ada
                tail->next = temp;
                temp->prev = tail;
                tail = temp; // Set tail ke elemen baru
            }

            current = temp; // Update node sebelumnya ke elemen baru
        }
    }

    file.close();
    cout << "Data telah dibaca dari file data_tiket.csv" << endl;
}

void Datapesanuser(tiketUser *&front, tiketUser *&rear, string username)
{
    ifstream file("B2_Kelompok7/tiket_user.csv");

    if (!file.is_open())
    {
        cout << "File data_tiket.csv tidak ditemukan." << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            cout << "Data Not Found" << endl;
            return;
        }
        else
        {
            stringstream ss(line);
            string username, asal, tujuan, harga, jumlah;
            int harga_int, jumlah_int;
            getline(ss, username, '|');
            getline(ss, asal, '|');
            getline(ss, tujuan, '|');
            getline(ss, harga, '|');
            getline(ss, jumlah, '\n');

            stringstream harga_str(harga);
            stringstream jumlah_str(jumlah);

            harga_str >> harga_int;
            jumlah_str >> jumlah_int;

            tiketUser *temp = new tiketUser;

            temp->data.username = username;
            temp->data.asal = asal;
            temp->data.tujuan = tujuan;
            temp->data.harga = harga_int;
            temp->data.jumlah = jumlah_int;
            temp->next = NULL;

            if (front == NULL)
            {
                front = temp;
            }
            else
            {
                (rear)->next = temp;
            }
            rear = temp;
        }
    }

    file.close();
    cout << "Data telah dibaca dari file data_tiket.csv" << endl;
}

void Databayaruser(bayar *&head, bayar *&tail, string username)
{
    ifstream file("B2_Kelompok7/bayar_tiket.csv");

    if (!file.is_open())
    {
        cout << "File data_tiket.csv tidak ditemukan." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            cout << "Data Not Found" << endl;
            return;
        }
        else
        {
            stringstream ss(line);
            string username, asal, tujuan, harga, jumlah, total;
            int harga_int, jumlah_int, total_int;
            getline(ss, username, '|');
            getline(ss, asal, '|');
            getline(ss, tujuan, '|');
            getline(ss, harga, '|');
            getline(ss, jumlah, '|');
            getline(ss, total, '\n');

            stringstream harga_str(harga);
            stringstream jumlah_str(jumlah);
            stringstream total_str(total);

            harga_str >> harga_int;
            jumlah_str >> jumlah_int;
            total_str >> total_int;

            bayar *current = nullptr;
            bayar *baru = new bayar;

            baru->username = username;
            baru->asal = asal;
            baru->tujuan = tujuan;
            baru->harga = harga_int;
            baru->jumlah = jumlah_int;
            baru->total = total_int;
            baru->next = nullptr;
            baru->prev = tail;

            if (head == nullptr)
            {
                // Jika *head masih NULL, maka elemen baru menjadi head
                head = baru;
                baru->prev = nullptr; // Set prev dari elemen baru ke nullptr
                tail = baru;          // elemen baru juga menjadi tail karena ini elemen pertama
            }
            else
            {
                // Jika *head sudah ada, hubungkan elemen baru dengan yang ada
                tail->next = baru;
                baru->prev = tail;
                tail = baru; // Set tail ke elemen baru
            }
        }
    }
    file.close();
    cout << "Data telah dibaca dari file data_tiket.csv" << endl;
}

tiketUser *newNode(string username, int pilih, int berapa)
{
    tiket *head = NULL;
    tiket *tail = NULL;
    loadCSV(head, tail);

    ofstream file("B2_Kelompok7/tiket_user.csv", ios::out | ios::app);
    tiketUser *nodeBaru = new tiketUser();
    if (!file.is_open())
    {
        cout << "Gagal membuka file data_barang.csv" << endl;
        file.close();
    }
    else
    {
        if (isEmpty(head, tail))
        {
            cout << "Data Kosong!!" << endl;
        }
        else
        {
            tiket *temp = head;
            while (temp != NULL)
            {
                if (pilih == temp->id)
                {
                    nodeBaru->data.username = username;
                    nodeBaru->data.asal = temp->asal;
                    nodeBaru->data.tujuan = temp->tujuan;
                    nodeBaru->data.harga = temp->harga;
                    nodeBaru->data.jumlah = berapa;

                    file << nodeBaru->data.username << "|";
                    file << nodeBaru->data.asal << "|";
                    file << nodeBaru->data.tujuan << "|";
                    file << nodeBaru->data.harga << "|";
                    file << nodeBaru->data.jumlah << "\n";
                    break;
                }
                temp = temp->next;
            }
        }
    }

    file.close();
    return nodeBaru;
}

void Enque(tiketUser **Front, tiketUser **Rear, string username)
{
    tiket *head = NULL;
    tiket *tail = NULL;
    loadCSV(head, tail);

    int pilih, berapa;
    bool cek = false;
    cout << "-------------------------------------------------------------------------------------------------" << endl
         << endl;
    cout << "Pilih ID Tiket : ";
    cin >> pilih;
    tiket *temp = head;
    while (temp != NULL)
    {
        if (pilih == temp->id && !cin.fail())
        {
            cek = true;
            break;
        }
        temp = temp->next;
    }
    if (cek)
    {
        cout << "Berapa Tiket? ";
        cin >> berapa;
        if (!cin.fail())
        {
            if(berapa <= 10){
                tiketUser *nodeBaru = newNode(username, pilih, berapa);
                if (*Front == NULL)
                {
                    *Front = nodeBaru;
                }
                else
                {
                    (*Rear)->next = nodeBaru;
                }
                *Rear = nodeBaru;
                cout << "<==================== Tiket Berhasil Dipesan ====================>"<<endl;
            }
            else {
                cout << "Anda hanya bisa memesan 10 tiket per tiket"<<endl;
            }
        }
    }
    cin.clear(); // Mengatur status kesalahan kembali ke "baik"
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displaytiket(tiketUser *front, string username)
{
    if (front == NULL)
    {
        cout << "Gak ada yang ngantri" << endl;
        return;
    }
    tiketUser *temp = front;
    while (temp != NULL)
    {
        if (temp->data.username == username)
        {
            cout << "Nama         : " << temp->data.username << endl;
            cout << "asal         : " << temp->data.asal << endl;
            cout << "tujuan       : " << temp->data.tujuan << endl;
            cout << "harga        : " << temp->data.harga << endl;
            cout << "Jumlah Tiket : " << temp->data.jumlah << endl;
            cout << "============================" << endl
                 << endl;
        }
        temp = temp->next;
    }
    cout << endl;
}

void riwayat(bayar *head, string username)
{
    if (head == NULL)
    {
        cout << "Belum ada riwayat pesanan" << endl;
        system("pause");
        return;
    }
    else
    {
        bayar *temp = head;
        while (temp != NULL)
        {
            if (temp->username == username)
            {
                cout << "Nama   : " << temp->username << endl;
                cout << "asal   : " << temp->asal << endl;
                cout << "tujuan : " << temp->tujuan << endl;
                cout << "harga  : " << temp->harga << endl;
                cout << "jumlah : " << temp->jumlah << endl;
                cout << "total  : " << temp->total << endl;
                cout << "============================" << endl
                     << endl;
            }
            temp = temp->next;
        }
        cout << "\n";
    }
}

void gantipesan(tiketUser *front)
{
    ofstream file;
    file.open("B2_Kelompok7/tiket_user.csv", ios::out | ios::trunc);

    if (front == NULL)
    {
        cout << "Gak ada yang ngantri" << endl;
        return;
    }
    while (front != NULL)
    {
        file << front->data.username << "|";
        file << front->data.asal << "|";
        file << front->data.tujuan << "|";
        file << front->data.harga << "|";
        file << front->data.jumlah << "\n";
        front = front->next;
    }
    file.close();
}

void Deque(tiketUser **Front, tiketUser **Rear, bayar **head, bayar **tail, string user)
{
    ofstream file;
    file.open("B2_Kelompok7/bayar_tiket.csv", ios::app);
    if (*Front == NULL)
    {
        cout << "Tidak Ada Pesanan" << endl;
        return;
    }
    tiketUser *temp = *Front;
    tiketUser *prev = nullptr;
    bool hapus = false;
    bayar *newnode = new bayar();
    while (temp != NULL)
    {
        if (temp->data.username == user)
        {

            newnode->username = temp->data.username;
            newnode->asal = temp->data.asal;
            newnode->tujuan = temp->data.tujuan;
            newnode->harga = temp->data.harga;
            newnode->jumlah = temp->data.jumlah;
            newnode->total = newnode->harga * newnode->jumlah;
            if (temp == *Front)
            {
                *Front = (*Front)->next; // Hapus node depan
                delete temp;
                if (*Front == NULL)
                {
                    *Rear == NULL;
                }
            }
            else
            {
                prev->next = temp->next; // Hapus node lain
                delete temp;
                if (temp == *Rear)
                {
                    *Rear = prev; // Update Rear jika yang dihapus adalah node terakhir
                }
            }
            hapus = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    if (hapus)
    {
        file << user << "|";
        file << newnode->asal << "|";
        file << newnode->tujuan << "|";
        file << newnode->harga << "|";
        file << newnode->jumlah << "|";
        file << newnode->total << "\n";
        if (*head == NULL && *tail == NULL)
        {
            *head = newnode;
            *tail = newnode;
        }
        else
        {
            newnode->next = *head;
            (*head)->prev = newnode;
            *head = newnode;
        }
        gantipesan(*Front);
    }
    file.close();
}

void lihatBayar(tiketUser *front, string username)
{
    if (front == NULL)
    {
        cout << "Gak ada yang ngantri" << endl;
        return;
    }
    tiketUser *temp = front;
    while (temp != NULL)
    {
        if (temp->data.username == username)
        {
            cout << "Nama         : " << temp->data.username << endl;
            cout << "asal         : " << temp->data.asal << endl;
            cout << "tujuan       : " << temp->data.tujuan << endl;
            cout << "harga        : " << temp->data.harga << endl;
            cout << "Jumlah Tiket : " << temp->data.jumlah << endl;
            cout << "Total        : " << temp->data.harga * temp->data.jumlah << endl;
            cout << "============================" << endl
                 << endl;
            break;
        }
        temp = temp->next;
    }
    cout << endl;
}

void cariTiket(tiket *head, tiket *tail, string tujuan)
{

    if (isEmpty(head, tail))
    {
        cout << "Data Kosong!!" << endl;
    }
    else
    {
        tiket *temp = head;
        int i = 0;
        cout << "-------------------------------------------------------------------------------------------------" << endl
             << endl;
        cout << "NO  "
             << "ID\t    "
             << "ASAL\t "
             << "TUJUAN \t "
             << "HARGA \t" << endl;
        while (temp != NULL)
        {
            if (tujuan == temp->tujuan)
            {
                cout << left << setw(4) << i + 1 << setw(8) << temp->id << setw(13) << temp->asal << setw(15) << temp->tujuan << temp->harga << endl;
            }
            temp = temp->next;
            i++;
        }
    }
}

void menuU(string user, string pass)
{
    tiket *head = NULL;
    tiket *tail = NULL;

    loadTiket(head, tail);

    bayar *head1 = NULL;
    bayar *tail1 = NULL;
    tiketUser *front = NULL;
    tiketUser *rear = NULL;
    Databayaruser(head1, tail1, user);
    Datapesanuser(front, rear, user);
    string x = "|                PESAN TIKET                |";
    string a = "|               LIHAT PESANAN               |";
    string b = "|           LIHAT RIWAYAT PESANAN           |";
    string d = "|                  BAYAR                    |";
    string e = "|                CARI TIKET                 |";
    string z = "|                   EXIT                    |";
    int pilih = 2;
    char key;
    while (true)
    {
        system("cls");
        cout << "=============================================\n";
        cout << "|                  MENU                     |\n";
        cout << "=============================================\n";
        cout << x << endl;
        cout << a << endl;
        cout << b << endl;
        cout << d << endl;
        cout << e << endl;
        cout << z << endl;
        cout << "=============================================" << endl;
        key = _getch();
        if (key == 72 && (pilih >= 2 && pilih <= 6))
        {
            pilih--;
        }
        else if (key == 80 && (pilih >= 1 && pilih <= 5))
        {
            pilih++;
        }
        if (key == '\r')
        {
            if (pilih == 1)
            {
                display(head, tail);
                Enque(&front, &rear, user);
                system("pause");
            }
            else if (pilih == 2)
            {
                displaytiket(front, user);
                system("pause");
            }
            else if (pilih == 3)
            {
                riwayat(head1, user);
                system("pause");
            }
            else if (pilih == 4)
            {
                lihatBayar(front, user);
                string bayar;
                cout << "Ingin Bayar? y/n ";
                fflush(stdin);
                getline(cin, bayar);
                if (bayar == "y")
                {
                    Deque(&front, &rear, &head1, &tail1, user);
                }
                system("pause");
            }
            else if (pilih == 5)
            {
                string tujuan, pesan;
                cout << "cari tujuan anda : ";
                fflush(stdin);
                getline(cin, tujuan);
                cariTiket(head, tail, tujuan);
                while(true){
                    cout << "apakah anda ingin memesan tiket? y/n : ";fflush(stdin); getline(cin, pesan);
                    if (pesan == "y"){
                        Enque(&front, &rear, user);
                        break;
                    }else if (pesan == "n"){
                        break;
                    }else{
                        cout << "masukkan input yang benar !!" << endl;
                    }
                }
                system("pause");
            }
            else if (pilih == 6)
            {
                cout << "==========================================================\n";
                cout << "|     Terima Kasih Telah Menggunakan Program Kami!!!     |\n";
                cout << "==========================================================\n";
                system("pause");
                return;

            }
        }
        if (pilih == 1)
        {
            x = "|          >>    PESAN TIKET    <<          |";
            a = "|               LIHAT PESANAN               |";
            b = "|           LIHAT RIWAYAT PESANAN           |";
            d = "|                  BAYAR                    |";
            e = "|                CARI TIKET                 |";
            z = "|                   EXIT                    |";
        }
        else if (pilih == 2)
        {
            x = "|                PESAN TIKET                |";
            a = "|            >> LIHAT PESANAN <<            |";
            b = "|           LIHAT RIWAYAT PESANAN           |";
            d = "|                  BAYAR                    |";
            e = "|                CARI TIKET                 |";
            z = "|                   EXIT                    |";
        }
        else if (pilih == 3)
        {
            x = "|                PESAN TIKET                |";
            a = "|               LIHAT PESANAN               |";
            b = "|        >> LIHAT RIWAYAT PESANAN <<        |";
            d = "|                  BAYAR                    |";
            e = "|                CARI TIKET                 |";
            z = "|                   EXIT                    |";
        }
        else if (pilih == 4)
        {
            x = "|                PESAN TIKET                |";
            a = "|               LIHAT PESANAN               |";
            b = "|           LIHAT RIWAYAT PESANAN           |";
            d = "|               >> BAYAR <<                 |";
            e = "|                CARI TIKET                 |";
            z = "|                   EXIT                    |";
        }
        else if (pilih == 5)
        {
            x = "|                PESAN TIKET                |";
            a = "|               LIHAT PESANAN               |";
            b = "|           LIHAT RIWAYAT PESANAN           |";
            d = "|                  BAYAR                    |";
            e = "|             >> CARI TIKET <<              |";
            z = "|                   EXIT                    |";
        }
        else if (pilih == 6)
        {
            x = "|                PESAN TIKET                |";
            a = "|               LIHAT PESANAN               |";
            b = "|           LIHAT RIWAYAT PESANAN           |";
            d = "|                  BAYAR                    |";
            e = "|                CARI TIKET                 |";
            z = "|                >> EXIT <<                 |";
        }
    }
}