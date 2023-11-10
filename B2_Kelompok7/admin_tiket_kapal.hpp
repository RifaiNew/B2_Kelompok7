#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

// Id tiket, asal, tujuan, harga
struct tiket
{
    int id;
    string asal, tujuan;
    int harga;

    tiket *next = NULL;
    tiket *prev = NULL;
};

tiket *cariID(tiket *head, int x)
{
    tiket *temp = head;
    while (temp != NULL)
    {
        if (temp->id == x)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

tiket *NewTiket(tiket *head)
{
    tiket *newnode = new tiket();
    tiket *temp = head;
    while (true)
    {
        cout << "ID : ";
        cin >> newnode->id;

        if (cin.fail() || newnode->id < 0)
        {
            cout << "Masukan ID tidak valid." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            system("pause");
            continue; // Loop to re-enter ID
        }

        tiket *cek = cariID(head, newnode->id);
        if (cek != NULL)
        {
            cout << "ID tidak boleh sama" << endl;
            system("pause");
        }
        else
        {
            cout << "Asal : ";
            fflush(stdin), getline(cin, newnode->asal);
            cout << "Tujuan : ";
            fflush(stdin), getline(cin, newnode->tujuan);
            if (newnode->asal == newnode->tujuan)
            {
                cout << "Asal dan tujuan tidak boleh sama" << endl;
                system("pause");
            }
            else
            {
                cout << "Harga : ";
                cin >> newnode->harga;
                if (cin.fail())
                {
                    cout << "Masukan Harga tidak valid." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer, mengambil nilai maksimum dari input buffer dan kemudian input buffernya dihapus
                    system("pause");
                    continue;
                }
                else if (newnode->harga <= 0)
                {
                    cout << "Harga tidak boleh kurang dari 0" << endl;
                    system("pause");
                }
                else
                {
                    return newnode;
                    break;
                }
            }
        }
    }
}

void saveTiket(tiket *head)
{
    ofstream file("B2_Kelompok7/data_tiket.csv");

    if (!file.is_open())
    {
        cout << "Gagal membuka file data_barang.csv" << endl;
        return;
    }

    tiket *current = head;
    while (current)
    {
        file << current->id << ",";
        file << current->asal << ",";
        file << current->tujuan << ",";
        file << current->harga << "\n";
        current = current->next;
    }

    file.close();
    cout << "" << endl;
    cout << "==========================================================\n";
    cout << "|             succesfully adding to data_barang.csv             |\n";
}

bool isEmpty(tiket *head, tiket *tail)
{

    if (head == NULL && tail == NULL)
    {
        return true;
    }
    return false;
}

void add(tiket **head, tiket **tail)
{
    tiket *newnode = NewTiket(*head);
    if (isEmpty(*head, *tail))
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
}

void display(tiket *head, tiket *tail)
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
            cout << left << setw(4) << i + 1 << setw(8) << temp->id << setw(13) << temp->asal << setw(15) << temp->tujuan << temp->harga << endl;
            temp = temp->next;
            i++;
        }
    }
}

void saveCSV(tiket *head)
{
    ofstream file("B2_Kelompok7/data_tiket.csv");

    if (!file.is_open())
    {
        cout << "Gagal membuka file data_barang.csv" << endl;
        return;
    }

    tiket *current = head;
    while (current)
    {
        file << current->id << ",";
        file << current->asal << ",";
        file << current->tujuan << ",";
        file << current->harga << "\n";
        current = current->next;
    }

    file.close();
    cout << "succesfully adding to data_tiket.csv" << endl;
}

// Fungsi untuk membaca data dari file CSV
void loadCSV(tiket *&head, tiket *&tail)
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
}

void Delete(tiket **head, tiket **tail, int index)
{
    tiket *temp = *head;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    if (temp == *head)
    {
        // cek apakah node cuman 1
        if ((*head)->next == NULL && (*head)->prev == NULL)
        {
            *head = NULL;
            delete temp;
            return;
        }

        *head = (*head)->next;
        (*head)->prev = NULL;
        delete temp;
        return;
    }
    else if (temp == *tail)
    {
        temp->prev->next = NULL;
        (*tail) = temp->prev;
    }
    else
    {

        temp->prev->next = temp->next; // hubungkan next pada node sebelum temp ke node setelahnya
        temp->next->prev = temp->prev; // hubungkan prev pada node setelah temp ke node sebelumnya
    }
    delete temp; // hapus node dari memori
}

void edit(tiket **head)
{
    if (*head == NULL)
    {
        cout << "data masih kosong" << endl;
        return;
    }
    int ubah;
    cout << "Masukan Id Tiket yang akan diubah : ";
    cin >> ubah;
    tiket *temp = *head;
    while (temp != NULL)
    {
        if (temp->id == ubah)
        {
            while (true)
            {
                int ide;
                cout << "ID : ";
                cin >> ide;

                if (cin.fail() || ide < 0)
                {
                    cout << "Masukan ID tidak valid." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                    system("pause");
                    continue; // Loop to re-enter ID
                }
                tiket *cek = cariID(*head, ide);
                if (cek != NULL)
                {
                    cout << "ID sudah digunakan" << endl;
                    system("pause");
                }
                else
                {
                    temp->id = ide;
                    cout << "Asal : ";
                    fflush(stdin), getline(cin, temp->asal);
                    cout << "Tujuan : ";
                    fflush(stdin), getline(cin, temp->tujuan);
                    if (temp->asal == temp->tujuan)
                    {
                        cout << "Asal dan tujuan tidak boleh sama" << endl;
                        system("pause");
                    }
                    else
                    {
                        cout << "Harga : ";
                        cin >> temp->harga;
                        if (cin.fail())
                        {
                            cout << "Masukan Harga tidak valid." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer, mengambil nilai maksimum dari input buffer dan kemudian input buffernya dihapus
                            system("pause");
                            continue;
                        }
                        else if (temp->harga <= 0)
                        {
                            cout << "Harga tidak boleh kurang dari 0" << endl;
                            system("pause");
                        }
                        else
                        {
                            return;
                        }
                    }
                }
            }
        }
        temp = temp->next;
    }
    cout << "Data tidak ditemukan" << endl;
    edit(head);
}

void tukar(tiket *a, tiket *b)
{
    int tempId = a->id;
    string tempAsal = a->asal;
    string tempTujuan = a->tujuan;
    int tempHarga = a->harga;

    a->id = b->id;
    a->asal = b->asal;
    a->tujuan = b->tujuan;
    a->harga = b->harga;

    b->id = tempId;
    b->asal = tempAsal;
    b->tujuan = tempTujuan;
    b->harga = tempHarga;
}

void shellSortId(tiket *head)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }

    int n = 0;
    tiket *current = head;
    while (current != NULL)
    {
        current = current->next;
        n++;
    }

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        bool swapped;
        do
        {
            swapped = false;
            tiket *ptr1 = head;
            tiket *ptr2 = head->next;

            for (int i = 0; i < n - gap; i++)
            {
                if (ptr1->id > ptr2->id)
                {
                    tukar(ptr1, ptr2);
                    swapped = true;
                }
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
        } while (swapped);
    }
}

int length(tiket *head)
{
    int count = 0;
    tiket *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

int min(int x, int y) { return (x <= y) ? x : y; }
int fibMonaccianSearch(tiket *head, int x, int n)
{
    tiket *temp = head;
    int fibMMm2 = 0;              // (m-2)'th Fibonacci No.
    int fibMMm1 = 1;              // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);

        temp = head;
        for (int j = 0; j < i; j++)
        {
            temp = temp->next;
        }

        if (temp->id < x)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (temp->id > x)
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
            return i;
    }
    temp = head;
    for (int j = 0; j < offset + 1; j++)
    {
        temp = temp->next;
    }
    if (fibMMm1 && temp->id == x)
        return offset + 1;
    return -1;
}

void menuA()
{
    tiket *head = NULL;
    tiket *tail = NULL;

    loadCSV(head, tail);
    string x = "|                 ADD DATA                  |";
    string a = "|               DISPLAY DATA                |";
    string b = "|               DELETE DATA                 |";
    string f = "|                EDIT DATA                  |";
    string d = "|               SORTING DATA                |";
    string e = "|              SEARCHING DATA               |";
    string c = "|                   EXIT                    |";
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
        cout << f << endl;
        cout << d << endl;
        cout << e << endl;
        cout << c << endl;
        cout << "=============================================" << endl;
        key = _getch();
        if (key == 72 && (pilih >= 2 && pilih <= 7))
        {
            pilih--;
        }
        else if (key == 80 && (pilih >= 1 && pilih <= 6))
        {
            pilih++;
        }
        if (key == '\r')
        {
            if (pilih == 1)
            {
                add(&head, &tail);
                saveTiket(head);
                system("pause");
            }
            else if (pilih == 2)
            {
                display(head, tail);
                system("pause");
            }
            else if (pilih == 3)
            {
                int index;
                display(head, tail);
                cout << "Hapus Nomor : ";
                cin >> index;
                Delete(&head, &tail, index - 1);
                saveTiket(head);
                system("pause");
            }
            else if (pilih == 4)
            {
                edit(&head);
                saveTiket(head);
                system("pause");
            }
            else if (pilih == 5)
            {
                shellSortId(head);
                cout << "Sorting Berhasil" << endl;
                saveTiket(head);
                system("pause");
            }
            else if (pilih == 6)
            {
                int x;
                cout << "Masukkan ID Tiket : ";
                cin >> x;
                int result = fibMonaccianSearch(head, x, length(head));
                if (result >= 0)
                {
                    cout << "Ditemukan" << endl;
                    tiket *temp = head;
                    while (temp != NULL)
                    {
                        if (temp->id == x)
                        {
                            cout << "ID            : " << temp->id << endl;
                            cout << "Asal - Tujuan : " << temp->asal << " - " << temp->tujuan << endl;
                            cout << "Harga         : " << temp->harga << endl;
                        }
                        temp = temp->next;
                    }
                }
                else
                {
                    cout << "Tidak Ditemukan" << endl;
                }
                system("pause");
            }
            else if (pilih == 7)
            {
                saveCSV(head);
                cout << "==========================================================\n";
                cout << "|     Terima Kasih Telah Menggunakan Program Kami!!!     |\n";
                cout << "==========================================================\n";
                return;
            }
        }
        if (pilih == 1)
        {
            x = "|              >> ADD DATA <<               |";
            a = "|               DISPLAY DATA                |";
            b = "|               DELETE DATA                 |";
            f = "|                EDIT DATA                  |";
            d = "|               SORTING DATA                |";
            e = "|              SEARCHING DATA               |";
            c = "|                  EXIT                     |";
        }
        else if (pilih == 2)
        {
            x = "|                 ADD DATA                  |";
            a = "|            >> DISPLAY DATA <<             |";
            b = "|               DELETE DATA                 |";
            f = "|                EDIT DATA                  |";
            d = "|               SORTING DATA                |";
            e = "|              SEARCHING DATA               |";
            c = "|                  EXIT                     |";
        }
        else if (pilih == 3)
        {
            x = "|                 ADD DATA                  |";
            a = "|               DISPLAY DATA                |";
            b = "|            >> DELETE DATA  <<             |";
            f = "|                EDIT DATA                  |";
            d = "|               SORTING DATA                |";
            e = "|              SEARCHING DATA               |";
            c = "|                  EXIT                     |";
        }
        else if (pilih == 4)
        {
            x = "|                 ADD DATA                  |";
            a = "|               DISPLAY DATA                |";
            b = "|               DELETE DATA                 |";
            f = "|             >> EDIT DATA <<               |";
            d = "|               SORTING DATA                |";
            e = "|              SEARCHING DATA               |";
            c = "|                  EXIT                     |";
        }
        else if (pilih == 5)
        {
            x = "|                 ADD DATA                  |";
            a = "|               DISPLAY DATA                |";
            b = "|               DELETE DATA                 |";
            f = "|                EDIT DATA                  |";
            d = "|            >> SORTING DATA <<             |";
            e = "|              SEARCHING DATA               |";
            c = "|                  EXIT                     |";
        }
        else if (pilih == 6)
        {
            x = "|                ADD DATA                   |";
            a = "|               DISPLAY DATA                |";
            b = "|               DELETE DATA                 |";
            f = "|                EDIT DATA                  |";
            d = "|               SORTING DATA                |";
            e = "|           >> SEARCHING DATA <<            |";
            c = "|                  EXIT                     |";
        }
        else if (pilih == 7)
        {
            x = "|                ADD DATA                   |";
            a = "|               DISPLAY DATA                |";
            b = "|               DELETE DATA                 |";
            f = "|                EDIT DATA                  |";
            d = "|               SORTING DATA                |";
            e = "|              SEARCHING DATA               |";
            c = "|               >> EXIT <<                  |";
        }
    }
}
