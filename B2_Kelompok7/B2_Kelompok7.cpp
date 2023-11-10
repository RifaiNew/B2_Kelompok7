#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h>
#include "admin_tiket_kapal.hpp"
#include "user_tiket_kapal.hpp"
using namespace std;

struct akun
{
    string username;
    string password;

    akun *next = NULL;
    akun *prev = NULL;
};

akun *cariUsername(akun *head, string x)
{
    akun *temp = head;
    while (temp != NULL)
    {
        if (temp->username == x)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

akun *Newakun(akun *head)
{
    akun *newNode = new akun();
    char c, a;
    string pass, cekPass;

    while (true)
    {
        cout << " Username : ";
        fflush(stdin), getline(cin, newNode->username);
        akun *cek = cariUsername(head, newNode->username);
        if (cek != NULL)
        {
            cout << "username telah digunakan, silahkan ganti" << endl;
            system("pause");
        }
        else
        {
            cout << " Password : ";
            while (c != '\r')
            {
                c = getch();

                if (c == '\b')
                {
                    if (pass.size() != 0)
                    {
                        cout << "\b \b";
                        pass.erase(pass.size() - 1, 1);
                    }
                    continue;
                }
                else if (c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
                {
                    pass += c;
                    cout << "*";
                }
            }
            cout << endl;
            cout << " Cek Password : ";
            while (a != '\r')
            {
                a = getch();

                if (a == '\b')
                {
                    if (cekPass.size() != 0)
                    {
                        cout << "\b \b";
                        cekPass.erase(cekPass.size() - 1, 1);
                    }
                    continue;
                }
                else if (a <= '9' && a >= '0' || a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z')
                {
                    cekPass += a;
                    cout << "*";
                }
            }
            if (pass != cekPass)
            {
                cout << endl;
                cout << "Konfirmasi Ulang Password" << endl;
                a = '0';
                c = '0';
                pass = "";
                cekPass = "";
            }
            else
            {
                newNode->password = pass;
                return newNode;
                break;
            }
        }
    }
}

void loadAkun(akun *&head, akun *&tail)
{
    ifstream file("B2_Kelompok7/akun.csv");

    if (!file.is_open())
    {
        cout << "File akun.csv tidak ditemukan." << endl;
        return;
    }

    string line;
    akun *current = nullptr; // Pointer tambahan
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
            string username, password;
            getline(ss, username, ',');
            getline(ss, password, '\n');

            akun *temp = new akun;
            temp->username = username;
            temp->password = password;
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
                temp->next = NULL;
                temp->prev = tail;
                tail->next = temp;
                tail = temp; // Set tail ke elemen baru
            }
            current = temp; // Update node sebelumnya ke elemen baru
        }
    }

    file.close();
    cout << "Data telah dibaca dari file data_tiket.csv" << endl;
}

void saveAkun(akun *head)
{
    ofstream file("B2_Kelompok7/akun.csv");

    if (!file.is_open())
    {
        cout << "Gagal membuka file data_barang.csv" << endl;
        return;
    }

    akun *current = head;
    while (current)
    {
        file << current->username << ",";
        file << current->password << "\n";
        current = current->next;
    }

    file.close();
    cout << "" << endl;
    cout << "==========================================================\n";
    cout << "|             succesfully adding to akun.csv             |\n";
}

void login(akun *head)
{
    akun *temp = head;
    for (int i = 0; i < 3; i++)
    {
        string user, pass;
        system("cls");
        cout << "=============================================\n";
        cout << "|                  LOGIN                    |\n";
        cout << "=============================================\n";
        char c;
        cout << " Username : "; fflush(stdin); getline(cin, user);
        bool cekAdmin = false;
        bool cekUser = false;
        cout << " Password : ";
        while (c != '\r')
        {
            c = getch();

            if (c == '\b')
            {
                if (pass.size() != 0)
                {
                    cout << "\b \b";
                    pass.erase(pass.size() - 1, 1);
                }
                continue;
            }
            else if (c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
            {
                pass += c;
                cout << "*";
            }
        }
        c = '\0';
        cout << endl;
        cout << "=============================================\n";
        akun *temp = head;
        while (temp != NULL)
        {
            if (user == "admin" && pass == "123admin")
            {
                cekAdmin = true;
                break;
            }
            else if (temp->username == user && temp->password == pass)
            {
                cekUser = true;
                break;
            }
            temp = temp->next;
        }
        if(cekAdmin){
            cout << "Login Berhasil !!!" << endl;
            system("pause");
            menuA();
            return;
        }
        if(cekUser){
            cout << "Login Berhasil !!!" << endl;
            system("pause");
            menuU(user, pass);
            return;
        }
        cout << "Username Atau Password Salah !!!" << endl;
        system("pause");
    }
}

void tambahakun(akun **head, akun **tail)
{
    system("cls");
    cout << "=============================================\n";
    cout << "|                SIGIN UP                   |\n";
    cout << "=============================================\n";
    akun *newNode = Newakun(*head);
    cout << endl;
    cout << "=============================================\n";
    if (head == NULL && tail == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        cout << endl;
        newNode->next = NULL;
        newNode->prev = (*tail);
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int main()
{
    akun *head = NULL;
    akun *tail = NULL;
    loadAkun(head, tail);
    string x = "|                  LOGIN                    |";
    string b = "|                 SIGN IN                   |";
    string c = "|                  EXIT                     |";
    int pilih = 2;
    char key;
    while (true)
    {
        system("cls");
        cout << "=============================================\n";
        cout << "|     Selamat Datang Di Program Kami!!!     |\n";
        cout << "=============================================\n";
        cout << x << endl;
        cout << b << endl;
        cout << c << endl;
        cout << "=============================================" << endl;

        key = _getch();
        if (key == 72 && (pilih >= 2 && pilih <= 3))
        {
            pilih--;
        }
        else if (key == 80 && (pilih >= 1 && pilih <= 2))
        {
            pilih++;
        }
        if (key == '\r')
        {
            if (pilih == 1)
            {
                login(head);
      
            }
            else if (pilih == 2)
            {
                tambahakun(&head, &tail);
                saveAkun(head);
                cout << "==========================================================\n";
                system("pause");
                main();
        
            }
            else if (pilih == 3)
            {
                saveAkun(head);
                cout << "==========================================================\n";
                cout << "|     Terima Kasih Telah Menggunakan Program Kami!!!     |\n";
                cout << "==========================================================\n";
                exit(0);
            }
        }
        if (pilih == 1)
        {
            x = "|               >> LOGIN <<                 |";
            b = "|                 SIGN IN                   |";
            c = "|                  EXIT                     |";
        }
        else if (pilih == 2)
        {
            x = "|                  LOGIN                    |";
            b = "|              >> SIGN IN <<                |";
            c = "|                  EXIT                     |";
        }
        else if (pilih == 3)
        {
            x = "|                  LOGIN                    |";
            b = "|                 SIGN IN                   |";
            c = "|               >> EXIT <<                  |";
        }
    }
}