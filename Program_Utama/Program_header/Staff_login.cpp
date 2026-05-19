#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../Data_header/Staff_login.h"
#include "../Data_header/Program_staff.h"
#include "../Data_header/struct.h"
#include "../Data_json/json.hpp"

using namespace std;
using json = nlohmann::json;

const string FILE_STAFF = "Data_json/Data_staff.json";

void staff_regis()
{
    Staff staff_baru;
    bool input_valid = true;

    json j;
    ifstream fileIn(FILE_STAFF);
    if (fileIn.is_open())
    {
        if (fileIn.peek() != std::ifstream::traits_type::eof())
        {
            fileIn >> j;
        }
        fileIn.close();
    }

    if (j.is_null())
    {
        j = json::array();
    }

    int staff_aktif = 0;
    for (const auto &item : j)
    {
        if (item["status_terima"] == true && item["status_kerja"] == true)
        {
            staff_aktif++;
        }
    }

    if (staff_aktif >= 10)
    {
        cout << "\n[INFO] Kuota Staff Tambak Lele Sudah FULL!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "============================" << endl;
    cout << "===== REGISTRASI STAFF =====" << endl;
    cout << "============================" << endl;
    while (input_valid)
    {
        try
        {
            cout << "Masukkan Username: ";
            getline(cin >> ws, staff_baru.username);
            if (staff_baru.username.length() < 1)
            {
                throw invalid_argument("Username Tidak Boleh Kosong!!!");
            }

            for (char huruf : staff_baru.username)
            {
                if (!isalpha(huruf))
                {
                    throw invalid_argument("Username Hanya Boleh Berupa Huruf Saja!!!");
                }
            }

            for (const auto &item : j)
            {
                if (item["nama"] == staff_baru.username)
                {
                    throw invalid_argument("Username Name Sudah Digunakan!!!");
                }
            }

            cout << "Masukkan Password: ";
            getline(cin >> ws, staff_baru.password);
            if (staff_baru.password.length() < 1)
            {
                throw invalid_argument("Password Tidak Boleh Kosong!!!");
            }

            for (char c : staff_baru.password)
            {
                if (isspace(c))
                {
                    throw invalid_argument("Password TIDAK BOLEH Mengandung SPASI!!!");
                }
            }

            input_valid = false;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] " << e.what() << endl;
            cout << "Silakan Coba Lagi!\n"
                 << endl;
            system("pause");
            system("cls");

            cout << "============================" << endl;
            cout << "===== REGISTRASI STAFF =====" << endl;
            cout << "============================" << endl;
        }
    }
    staff_baru.regis_status = false;
    staff_baru.employed_status = false;
    staff_baru.saldo = 0.0;

    if (j.empty())
    {
        staff_baru.id_staff = 1;
    }
    else
    {
        staff_baru.id_staff = j.back()["id"].get<int>() + 1;
    }

    json staffjson = {
        {"id", staff_baru.id_staff},
        {"nama", staff_baru.username},
        {"pass", staff_baru.password},
        {"status_terima", staff_baru.regis_status},
        {"status_kerja", staff_baru.employed_status},
        {"saldo", staff_baru.saldo},
    };
    j.push_back(staffjson);

    ofstream fileOut(FILE_STAFF);
    fileOut << j.dump(4);
    fileOut.close();

    cout << "[BERHASIL] Registrasi Berhasil! Akun Anda (ID: " << staff_baru.id_staff << ") Silahkan Tunggu Persetujuan Dari Admin" << endl;
    system("pause");
    system("cls");
}

bool status_regis()
{
    string cek_username;
    bool cek_regis = true;

    system("cls");
    cout << "=================================" << endl;
    cout << "===== CEK STATUS REGISTRASI =====" << endl;
    cout << "=================================" << endl;
    while (cek_regis)
    {
        try
        {
            cout << "Masukkan Username: ";
            getline(cin >> ws, cek_username);

            if (cek_username.length() < 1)
            {
                throw invalid_argument("Input Username Tidak Boleh Kosong!!!");
            }

            for (char c : cek_username)
            {
                if (!isalpha(c))
                {
                    throw invalid_argument("Input Username Hanya Boleh Huruf!!!");
                }
            }

            cek_regis = false;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] " << e.what() << endl;
        }
    }

    json j;
    ifstream fileIn(FILE_STAFF);

    if (fileIn.is_open())
    {
        if (fileIn.peek() != std::ifstream::traits_type::eof())
        {
            fileIn >> j;
        }
        fileIn.close();

        if (!j.empty())
        {
            for (auto &item : j)
            {
                if (item["nama"] == cek_username)
                {
                    if (item["status_terima"] == true)
                    {
                        cout << "[SELAMAT] Anda Diterima Sebagai Karyawan Tambak Lele :) !!!" << endl;
                        system("pause");
                        system("cls");
                        return true;
                    }
                    else
                    {
                        cout << "[WAKWAW] Anda Masih Belum Di ACC Sebagai Karyawan Tambak Lele :( !!!" << endl;
                        system("pause");
                        system("cls");
                        return false;
                    }
                }
            }
        }
    }
    cout << "\n[ERROR] Username '" << cek_username << "' Tidak Ditemukan!!!" << endl;
    system("pause");
    system("cls");
    return false;
}

int login_staff()
{
    string log_username, log_pass;
    int batas_login = 0;
    int id_staff;

    while (batas_login < 3)
    {
        system("cls");
        cout << "=======================" << endl;
        cout << "===== LOGIN STAFF =====" << endl;
        cout << "=======================" << endl;
        cout << "Username : ";
        getline(cin >> ws, log_username);
        cout << "Password : ";
        getline(cin >> ws, log_pass);

        json j;
        ifstream fileIn(FILE_STAFF);
        bool user_ditemukan = false;

        if (fileIn.is_open())
        {
            if (fileIn.peek() != std::ifstream::traits_type::eof())
            {
                fileIn >> j;
            }
            fileIn.close();

            if (!j.empty())
            {
                for (const auto &item : j)
                {
                    if (item["nama"] == log_username && item["pass"] == log_pass)
                    {
                        user_ditemukan = true;

                        if (item["status_terima"] == true && item["status_kerja"] == true)
                        {
                            cout << "[BERHASIL] Login Berhasil! Selamat Datang, " << log_username << endl;
                            id_staff = item["id"];
                            system("pause");
                            system("cls");
                            return id_staff;
                        }
                        else
                        {
                            cout << "[GAGAL] Login Gagal! Akun Anda Belum Terdata!!!" << endl;
                            system("pause");
                            system("cls");
                            return 0;
                        }
                    }
                }
            }
        }

        if (!user_ditemukan)
        {
            batas_login++;
            int sisa_percobaan = 3 - batas_login;

            if (batas_login < 3)
            {
                cout << "\n[GAGAL] Login Gagal! Username/Password Salah atau Belum Terdaftar!!!" << endl;
                cout << "[SISA PERCOBAAN](Sisa Percobaan: " << sisa_percobaan << "x)" << endl;
                system("pause");
                system("cls");
            }
            else
            {
                cout << "[KACAU] Anda Telah Salah 3x!!!" << endl;
                system("pause");
                system("cls");
                return 0;
            }
        }
    }
    return 0;
}

void menu_staff(int &id_staff)
{
    int pilihan = 0;
    string pilihan_menu;
    bool staff_menu = true;

    while (staff_menu)
    {
        system("cls");

        cout << "======================================" << endl;
        cout << "===== RUANG KENDALI STAFF TAMBAK =====" << endl;
        cout << "======================================" << endl;
        cout << "1. Update Jatah Pakan" << endl;
        cout << "2. Catat Kematian Ikan" << endl;
        cout << "3. Lihat Saldo Rekening"<< endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan: ";
        getline(cin >> ws, pilihan_menu);

        try
        {
            pilihan = stoi(pilihan_menu);
        }
        catch (const exception &e)
        {
            pilihan = 0;
        }

        switch (pilihan)
        {
        case 1:
            tebar_pakan(id_staff);
            break;

        case 2:
            catatMortalitas(id_staff);
            break;

        case 3:
            rekening_staff(id_staff);
            break;

        case 4:
            staff_menu = false;
            system("pause");
            system("cls");
            break;

        default:
            cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}