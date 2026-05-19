#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <iomanip> // Untuk merapikan tabel
#include "../Data_header/Program_admin.h"
#include "../Data_header/struct.h"
#include "../Data_json/json.hpp"

using namespace std;
using json = nlohmann::json;

const string FILE_STAFF = "Data_json/Data_staff.json";
const string FILE_KOLAM = "Data_json/Data_kolam.json";
const string FILE_KEUANGAN = "Data_json/Laporan_keuangan.json";
const string FILE_REKBER = "Data_json/Rekber_admin.json";
const string FILE_PAKAN = "Data_json/Data_pakan.json";
const string FILE_LAPORAN = "Data_json/Laporan_staff.json";
const string FILE_GAJI = "Data_json/Data_gaji.json";

static json load_json(string PATH, string messages)
{
    json j;
    ifstream fileIn(PATH);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << messages << endl;
    }

    return j;
}

json load_data_pakan()
{
    Pakan pakan;

    json j;
    ifstream fileIn(FILE_PAKAN);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        pakan.harga_per_kg = 0;
        pakan.stok_kg = 0;
        pakan.total_modal_pakan = 0;

        json kolamjson = {
            {"stok_kg", pakan.stok_kg},
            {"harga_per_kg", pakan.harga_per_kg},
            {"total_modal_pakan", pakan.total_modal_pakan},
        };

        j.push_back(kolamjson);
    }

    return j;
}

void lihat_staff(int id)
{
    json j;
    ifstream fileIn(FILE_STAFF);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    bool valid = false;

    cout << "=======================================================" << endl;
    cout << "============== DAFTAR STAFF BERDASARKAN ID ============" << endl;
    cout << "=======================================================" << endl;
    cout << left << setw(5)  << "ID" << "| "
         << left << setw(20) << "Username" << "| "
         << left << setw(15) << "Status" << "|" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (const auto &item : j)
    {
        if (item["id"] == id)
        {
            int id = item.value("id", 0);
            string nama = item.value("nama", "-");

            cout << left << setw(5)  << id << "| "
                 << left << setw(20) << nama << "| "
                 << left << setw(15) << "Aktif Bekerja" << "|" << endl;
            cout << "-------------------------------------------------------" << endl;
            valid = true;
        }
    }

    if (valid)
    {
        cout << "\n[SUCCESS] Staff Dengan (ID: " << id << ") Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "[ERROR] Staff Dengan (ID: " << id << ") Tidak Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
}

void lihat_staff()
{
    json j;
    ifstream fileIn(FILE_STAFF);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Staff Di Database!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    string pilihan_menu, input_id;
    int pilihan, id;
    bool loop = true;

    while (loop)
    {
        system("cls");
        cout << "============================" << endl;
        cout << "===== MENU LIHAT STAFF =====" << endl;
        cout << "============================" << endl;
        cout << "1. Lihat Staff Berdasarkan ID Staff" << endl;
        cout << "2. Lihat Staff Yang Aktif Bekerja" << endl;
        cout << "3. Lihat Staff Yang Belum Aktif Bekerja" << endl;
        cout << "4. Keluar" << endl;
        cout << "Masukan Pilihan: ";
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
            system("cls");

            while (true)
            {
                try
                {
                    cout << "Masukan ID Kolam Yang Ingin Di Lihat (Input 0 Untuk Batal): ";
                    getline(cin >> ws, input_id);

                    id = stoi(input_id);

                    if (id == 0)
                    {
                        system("cls");
                        return;
                    }

                    break;
                }
                catch (const exception &e)
                {
                    cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                    system("pause");
                    system("cls");
                }
            }

            lihat_staff(id);

            break;

        case 2:
            system("cls");
            cout << "=======================================================" << endl;
            cout << "================== DAFTAR STAFF AKTIF =================" << endl;
            cout << "=======================================================" << endl;
            cout << left << setw(5)  << "ID" << "| "
                 << left << setw(20) << "Username" << "| "
                 << left << setw(15) << "Status" << "|" << endl;
            cout << "-------------------------------------------------------" << endl;

            for (int i = 0; i < j.size(); i++)
            {
                for (int k = 0; k < j.size() - 1 - i; k++)
                {
                    if (j[k]["id"] > j[k + 1]["id"])
                    {
                        swap(j[k], j[k + 1]);
                    }
                }
            }

            for (const auto &item : j)
            {
                if (item["status_terima"] == true && item["status_kerja"] == true)
                {
                    int id = item.value("id", 0);
                    string nama = item.value("nama", "-");

                    cout << left << setw(5)  << id << "| "
                         << left << setw(20) << nama << "| "
                         << left << setw(15) << "Aktif Bekerja" << "|" << endl;
                    cout << "-------------------------------------------------------" << endl;
                }
            }

            system("pause");
            system("cls");
            break;

        case 3:
        {

            system("cls");
            cout << "========================================================" << endl;
            cout << "=============== DAFTAR STAFF BELUM AKTIF ===============" << endl;
            cout << "========================================================" << endl;
            cout << left << setw(5)  << "ID" << "| "
                 << left << setw(20) << "Username" << "| "
                 << left << setw(15) << "Status" << "|" << endl;
            cout << "-------------------------------------------------------" << endl;

            for (int i = 0; i < j.size(); i++)
            {
                for (int k = 0; k < j.size() - 1 - i; k++)
                {
                    if (j[k]["id"] > j[k + 1]["id"])
                    {
                        swap(j[k], j[k + 1]);
                    }
                }
            }

            bool ketemu = false;

            for (const auto &item : j)
            {
                if (item["status_terima"] == false || item["status_kerja"] == false)
                {
                    int id = item.value("id", 0);
                    string nama = item.value("nama", "-");

                    cout << left << setw(5)  << id << "| "
                         << left << setw(20) << nama << "| "
                         << left << setw(15) << "Tidak Aktif " << "|" << endl;
                    cout << "-------------------------------------------------------" << endl;

                    ketemu = true;
                }
            }

            if(!ketemu)
            {
                cout << "\n[INFO] Belum Ada Staff Yang Tidak Aktif" << endl;
            }

            system("pause");
            system("cls");
            break;
        }

        case 4:
            loop = false;
            system("cls");
            break;

        default:
            cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
            system("pause");
            break;
        }
    }

    system("pause");
    system("cls");
    return;
}

void acc_staff()
{
    json j;
    ifstream fileIn(FILE_STAFF);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Staff Di Database!!!" << endl;
        system("pause");
        system("cls");
        return;
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
        cout << "[INFO] Kuota Karyawan Sudah Penuh (10/10)!!!" << endl;
        cout << "Tidak Bisa ACC Staff Baru Sebelum Ada Yang Di-PHK!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "=======================================================" << endl;
    cout << "============== DAFTAR STAFF MENUNGGU ACC ==============" << endl;
    cout << "=======================================================" << endl;
    cout << left << setw(5)  << "ID" << "| "
         << left << setw(20) << "Username" << "| "
         << left << setw(15) << "Status" << "|" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (int i = 0; i < j.size(); i++)
    {
        for (int k = 0; k < j.size() - 1 - i; k++)
        {
            if (j[k]["id"] > j[k + 1]["id"])
            {
                swap(j[k], j[k + 1]);
            }
        }
    }

    bool ada_pending = false;
    for (const auto &item : j)
    {
        if (item["status_terima"] == false)
        {
            int id = item.value("id", 0);
            string nama = item.value("nama", "-");

            cout << left << setw(5)  << id << "| "
                 << left << setw(20) << nama << "| "
                 << left << setw(15) << "Menunggu  " << "|" << endl;
            cout << "-------------------------------------------------------" << endl;
            ada_pending = true;
        }
    }

    if (!ada_pending)
    {
        cout << "\n[INFO] Tidak Ada Staff Baru Yang Mendaftar!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int id_pilihan = -1;
    string input_id;

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Staff yang ingin di-ACC (0 untuk batal): ";
            getline(cin >> ws, input_id);

            id_pilihan = stoi(input_id);

            if (id_pilihan == 0)
            {
                system("cls");
                return;
            }

            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid!!!" << endl;
            system("pause");
            system("cls");

            cout << "=======================================================" << endl;
            cout << "============== DAFTAR STAFF MENUNGGU ACC ==============" << endl;
            cout << "=======================================================" << endl;
            cout << left << setw(5)  << "ID" << "| "
                 << left << setw(20) << "Username" << "| "
                 << left << setw(15) << "Status" << "|" << endl;
            cout << "-------------------------------------------------------" << endl;

            for (const auto &item : j)
            {
                if (item["status_terima"] == false)
                {
                    int id = item.value("id", 0);
                    string nama = item.value("nama", "-");

                    cout << left << setw(5)  << id << "| "
                        << left << setw(20) << nama << "| "
                        << left << setw(15) << "Menunggu  " << "|" << endl;
                    cout << "-------------------------------------------------------" << endl;
                }
            }
        }
    }

    bool ditemukan = false;
    for (auto &item : j)
    {
        if (item["id"] == id_pilihan && item["status_terima"] == false)
        {
            item["status_terima"] = true;
            item["status_kerja"] = true;
            ditemukan = true;
            break;
        }
    }

    if (ditemukan)
    {
        ofstream fileOut(FILE_STAFF);
        fileOut << j.dump(4);
        fileOut.close();
        cout << "[BERHASIL] Staff Dengan ID " << id_pilihan << " Telah Diterima Bekerja!!!" << endl;
    }
    else
    {
        cout << "[ERROR] ID Tidak Ditemukan / Sudah Pernah Di ACC Sebelumnya!!!" << endl;
    }

    system("pause");
    system("cls");
}

void pecat_staff()
{
    json j;
    ifstream fileIn(FILE_STAFF);

    if (fileIn.is_open())
    {
        if (fileIn.peek() != std::ifstream::traits_type::eof()) {
            fileIn >> j;
        }
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Staff Di Database!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "=======================================================" << endl;
    cout << "================ DAFTAR STAFF AKTIF ===================" << endl;
    cout << "=======================================================" << endl;
    cout << left << setw(5)  << "ID" << "| "
         << left << setw(20) << "Username" << "| "
         << left << setw(15) << "Status" << "|" << endl;
    cout << "-------------------------------------------------------" << endl;

    for (int i = 0; i < j.size(); i++)
    {
        for (int k = 0; k < j.size() - 1 - i; k++)
        {
            if (j[k]["id"] > j[k + 1]["id"])
            {
                swap(j[k], j[k + 1]);
            }
        }
    }

    bool ada_aktif = false;
    for (const auto &item : j)
    {
        if (item["status_terima"] == true && item["status_kerja"] == true)
        {
            int id = item.value("id", 0);
            string nama = item.value("nama", "-");

            cout << left << setw(5)  << id << "| "
                 << left << setw(20) << nama << "| "
                 << left << setw(15) << "Aktif Bekerja" << "|" << endl;
            cout << "-------------------------------------------------------" << endl;
            ada_aktif = true;
        }
    }

    if (!ada_aktif)
    {
        cout << "\n[INFO] Belum Ada Staff Yang Berstatus Aktif!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int id_pilihan = -1;
    string input_id;

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Staff Yang Ingin Di PHK (0 untuk batal): ";
            getline(cin >> ws, input_id);

            id_pilihan = stoi(input_id);

            if (id_pilihan == 0)
            {
                system("cls");
                return;
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid!!!" << endl;
            system("pause");
            system("cls");

            cout << "=======================================================" << endl;
            cout << "================ DAFTAR STAFF AKTIF ===================" << endl;
            cout << "=======================================================" << endl;
            cout << left << setw(5)  << "ID" << "| "
                 << left << setw(20) << "Username" << "| "
                 << left << setw(15) << "Status" << "|" << endl;
            cout << "-------------------------------------------------------" << endl;

            for (const auto &item : j)
            {
                if (item["status_terima"] == true && item["status_kerja"] == true)
                {
                    int id = item.value("id", 0);
                    string nama = item.value("nama", "-");

                    cout << left << setw(5)  << id << "| "
                         << left << setw(20) << nama << "| "
                         << left << setw(15) << "Aktif Bekerja" << "|" << endl;
                    cout << "-------------------------------------------------------" << endl;
                }
            }
        }
    }

    bool ditemukan = false;
    for (auto it = j.begin(); it != j.end(); ++it)
    {
        if ((*it)["id"] == id_pilihan && (*it)["status_terima"] == true && (*it)["status_kerja"] == true)
        {
            j.erase(it); 
            ditemukan = true;
            break;
        }
    }

    if (ditemukan)
    {
        ofstream fileOut(FILE_STAFF);
        fileOut << j.dump(4);
        fileOut.close();

        json gaji_j = load_json(FILE_GAJI, "");
        if(gaji_j.is_array() && !gaji_j.empty())
        {
            for (auto it = gaji_j.begin(); it != gaji_j.end(); )
            {
                if ((*it).value("id_staff", -1) == id_pilihan)
                {
                    it = gaji_j.erase(it);
                }
                else
                {
                    ++it;
                }
            }
            ofstream outGaji(FILE_GAJI);
            outGaji << gaji_j.dump(4);
            outGaji.close();
        }

        json laporan_j = load_json(FILE_LAPORAN, "");
        if(laporan_j.is_array() && !laporan_j.empty())
        {
            for (auto it = laporan_j.begin(); it != laporan_j.end(); )
            {
                if((*it).value("id_staff", -1) == id_pilihan)
                {
                    it = laporan_j.erase(it);
                }
                else
                {
                    ++it;
                }
            }
            ofstream outLaporan(FILE_LAPORAN);
            outLaporan << laporan_j.dump(4);
            outLaporan.close();
        }

        cout << "\n[BERHASIL] Staff Dengan ID " << id_pilihan << " Telah Dihapus Permanen!" << endl;
        cout << "[INFO] Seluruh riwayat Gaji & Laporan Kinerja staff tersebut telah dihanguskan." << endl;
    }
    else
    {
        cout << "\n[ERROR] ID Tidak Ditemukan / Staff Sudah Tidak Aktif!!!" << endl;
    }

    system("pause");
    system("cls");
}

void lihat_kolam(int id)
{
    json j;
    ifstream fileIn(FILE_KOLAM);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    bool valid = false;

    cout << "======================================================================" << endl;
    cout << "==================== DAFTAR KOLAM BERDASARKAN ID =====================" << endl;
    cout << "======================================================================" << endl;
    cout << left << setw(5)  << "ID" << "| "
         << left << setw(15) << "Tipe" << "| "
         << left << setw(12) << "Kapasitas" << "| "
         << left << setw(12) << "Populasi" << "| "
         << left << setw(15) << "Status" << "|" << endl;
    cout << "----------------------------------------------------------------------" << endl;


    for (const auto &item : j)
    {
        if (item["id"] == id)
        {
            int id = item.value("id", 0);
                string tipe = item.value("tipe", "-");
                int kapasitas = item.value("kapasitas", 0);
                int populasi = item.value("populasi", 0);
                string status = item.value("status_kolam", "-");

            cout << left << setw(5)  << id << "| "
                 << left << setw(15) << tipe << "| "
                 << left << setw(12) << kapasitas << "| "
                 << left << setw(12) << populasi << "| "
                 << left << setw(15) << status << "|" << endl;
            cout << "----------------------------------------------------------------------" << endl;

            valid = true;
        }
    }

    if (valid)
    {
        cout << "\n[SUCCESS] Kolam Dengan (ID: " << id << ") Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "\n[ERROR] Kolam Dengan (ID: " << id << ") Tidak Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
}

void lihat_kolam()
{
    json j;
    ifstream fileIn(FILE_KOLAM);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    bool loop = true;
    string pilihan_menu, input_id, input_tipe, input_status;
    int pilihan, id;

    while (loop)
    {
        system("cls");
        cout << "============================" << endl;
        cout << "===== MENU LIHAT KOLAM =====" << endl;
        cout << "============================" << endl;
        cout << "1. Lihat Seluruh Kolam" << endl;
        cout << "2. Lihat Kolam Berdasarkan ID Kolam" << endl;
        cout << "3. Lihat Kolam Berdasarkan Tipe Kolam" << endl;
        cout << "4. Lihat Kolam Berdasarkan Status Kolam" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukan Pilihan: ";
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
            system("cls");

            for (int i = 0; i < j.size(); i++)
            {
                for (int k = 0; k < j.size() - 1 - i; k++)
                {
                    if (j[k]["id"] > j[k + 1]["id"])
                    {
                        swap(j[k], j[k + 1]);
                    }
                }
            }

            system("cls");
            cout << "======================================================================" << endl;
            cout << "==================== DAFTAR SELURUH KOLAM ============================" << endl;
            cout << "======================================================================" << endl;
            
            cout << left << setw(5)  << "ID" << "| "
                 << left << setw(15) << "Tipe" << "| "
                 << left << setw(12) << "Kapasitas" << "| "
                 << left << setw(12) << "Populasi" << "| "
                 << left << setw(15) << "Status" << "|" << endl;
            cout << "----------------------------------------------------------------------" << endl;

            for (const auto &item : j)
            {
                // Tarik value JSON ke tipe data dasar biar aman saat dicetak
                int id = item.value("id", 0);
                string tipe = item.value("tipe", "-");
                int kapasitas = item.value("kapasitas", 0);
                int populasi = item.value("populasi", 0);
                string status = item.value("status_kolam", "-");

                // Mencetak Isi Tabel sama persisi dengan Header
                cout << left << setw(5)  << id << "| "
                     << left << setw(15) << tipe << "| "
                     << left << setw(12) << kapasitas << "| "
                     << left << setw(12) << populasi << "| "
                     << left << setw(15) << status << "|" << endl;
                cout << "----------------------------------------------------------------------" << endl;
            }
            
            system("pause");
            system("cls");
            break;

        case 2:
        {
            system("cls");

            while (true)
            {
                try
                {
                    cout << "Masukan ID Kolam Yang Ingin Di Lihat: ";
                    getline(cin >> ws, input_id);

                    id = stoi(input_id);

                    if (id == 0)
                    {
                        system("cls");
                        return;
                    }

                    break;
                }
                catch (const exception &e)
                {
                    cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                    system("pause");
                    system("cls");
                }
            }

            lihat_kolam(id);

            break;
        }

        case 3:
        {
            system("cls");

            while (true)
            {
                cout << "Masukan Tipe Kolam Yang Ingin Di lihat (Kecil, Sedang, Besar): ";
                getline(cin >> ws, input_tipe);

                for (char &huruf : input_tipe)
                {
                    huruf = tolower(huruf);
                }

                if (input_tipe != "kecil" && input_tipe != "sedang" && input_tipe != "besar")
                {
                    cout << "[ERROR] Input Tidak Valid!!!" << endl;
                    cout << "[INFO] Silahkan Coba Lagi!!!" << endl;
                    system("pause");
                    system("cls");
                    continue;
                }

                cout << "========================================================================" << endl;
                cout << "==================== DAFTAR KOLAM BERDASARKAN TIPE =====================" << endl;
                cout << "========================================================================" << endl;
                
                cout << left << setw(5)  << "ID" << "| "
                     << left << setw(15) << "Tipe" << "| "
                     << left << setw(12) << "Kapasitas" << "| "
                     << left << setw(12) << "Populasi" << "| "
                     << left << setw(15) << "Status" << "|" << endl;
                cout << "------------------------------------------------------------------------" << endl;
                
                for (int i = 0; i < j.size(); i++)
                {
                    for (int k = 0; k < j.size() - 1 - i; k++)
                    {
                        if (j[k]["id"] > j[k + 1]["id"])
                        {
                            swap(j[k], j[k + 1]);
                        }
                    }
                }

                bool ada_data = false;
                for (const auto &item : j)
                {
                    if (item["tipe"] == input_tipe)
                    {
                        int id = item.value("id", 0);
                        string tipe = item.value("tipe", "-");
                        int kapasitas = item.value("kapasitas", 0);
                        int populasi = item.value("populasi", 0);
                        string status = item.value("status_kolam", "-");

                        cout << left << setw(5)  << id << "| "
                            << left << setw(15) << tipe << "| "
                            << left << setw(12) << kapasitas << "| "
                            << left << setw(12) << populasi << "| "
                            << left << setw(15) << status << "|" << endl;
                        cout << "----------------------------------------------------------------------" << endl;
                        ada_data = true;
                    }
                }

                if (!ada_data)
                {
                    cout << "[INFO] Tidak Ada Kolam Dengan (Tipe: " << input_tipe << ") Saat Ini!!!" << endl;
                }

                system("pause");
                system("cls");
                break;
            }
            break;
        }

        case 4:
        {
            system("cls");

            while (true)
            {
                cout << "Masukan Tipe Kolam Yang Ingin Di lihat (Kosong, Terisi, Panen): ";
                getline(cin >> ws, input_status);

                for (char &huruf : input_status)
                {
                    huruf = tolower(huruf);
                }

                input_status[0] = toupper(input_status[0]);

                if (input_status != "Kosong" && input_status != "Terisi" && input_status != "Panen")
                {
                    cout << "[ERROR] Input Tidak Valid!!!" << endl;
                    cout << "[INFO] Silahkan Coba Lagi!!!" << endl;
                    system("pause");
                    system("cls");
                    continue;
                }

                cout << "========================================================================" << endl;
                cout << "==================== DAFTAR KOLAM BERDASARKAN STATUS ===================" << endl;
                cout << "========================================================================" << endl;
                cout << left << setw(5)  << "ID" << "| "
                     << left << setw(15) << "Tipe" << "| "
                     << left << setw(12) << "Kapasitas" << "| "
                     << left << setw(12) << "Populasi" << "| "
                     << left << setw(15) << "Status" << "|" << endl;
                cout << "------------------------------------------------------------------------" << endl;

                for (int i = 0; i < j.size(); i++)
                {
                    for (int k = 0; k < j.size() - 1 - i; k++)
                    {
                        if (j[k]["id"] > j[k + 1]["id"])
                        {
                            swap(j[k], j[k + 1]);
                        }
                    }
                }

                bool ada_data = false;
                for (const auto &item : j)
                {
                    if (item["status_kolam"] == input_status)
                    {
                        int id = item.value("id", 0);
                        string tipe = item.value("tipe", "-");
                        int kapasitas = item.value("kapasitas", 0);
                        int populasi = item.value("populasi", 0);
                        string status = item.value("status_kolam", "-");

                        cout << left << setw(5)  << id << "| "
                            << left << setw(15) << tipe << "| "
                            << left << setw(12) << kapasitas << "| "
                            << left << setw(12) << populasi << "| "
                            << left << setw(15) << status << "|" << endl;
                        cout << "----------------------------------------------------------------------" << endl;
                        ada_data = true;
                    }
                }

                if (!ada_data)
                {
                    cout << "[INFO] Tidak Ada Kolam Dengan (Status: " << input_status << ") Saat Ini!!!" << endl;
                }

                system("pause");
                system("cls");
                break;
            }
            break;
        }

        case 5:
            system("cls");
            loop = false;
            break;

        default:
            cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
            system("pause");
            break;
        }
    }
}

void buat_kolam()
{
    Kolam kolam;

    json j;
    ifstream fileIn(FILE_KOLAM);
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

    if (j.size() >= 10)
    {
        cout << "\n[ERROR] Kuota Kolam Tambak Lele FULL!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "============================" << endl;
    cout << "======== BUAT KOLAM ========" << endl;
    cout << "============================" << endl;
    cout << "Masukkan Tipe Kolam (Kecil, Sedang, Besar): ";
    getline(cin >> ws, kolam.tipe_kolam);

    kolam.status_kolam = "Kosong";
    kolam.populasi_ikan = 0;
    kolam.total_harga_benih = 0;
    kolam.total_mati = 0;
    kolam.umur_kolam = 0;
    kolam.fase_kolam = "";
    kolam.total_berat_kolam = 0;
    kolam.total_harga_pakan = 0;
    kolam.total_modal = 0;
    kolam.siklus_kolam = 0;

    for (char &huruf : kolam.tipe_kolam)
    {
        huruf = tolower(huruf);
    }

    if (kolam.tipe_kolam == "kecil")
    {
        kolam.kapasitas = 500;
    }
    else if (kolam.tipe_kolam == "sedang")
    {
        kolam.kapasitas = 1500;
    }
    else if (kolam.tipe_kolam == "besar")
    {
        kolam.kapasitas = 3000;
    }
    else
    {
        cout << "[ERROR] Pilihan Tidak Valid!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    if (j.empty())
    {
        kolam.id_kolam = 1;
    }
    else
    {
        kolam.id_kolam = j.back()["id"].get<int>() + 1;
    }

    json kolamjson = {
        {"id", kolam.id_kolam},
        {"tipe", kolam.tipe_kolam},
        {"kapasitas", kolam.kapasitas},
        {"populasi", kolam.populasi_ikan},
        {"status_kolam", kolam.status_kolam},
        {"total_harga_benih", kolam.total_harga_benih},
        {"total_mati", kolam.total_harga_benih},
        {"fase_kolam", kolam.fase_kolam},
        {"total_berat_kolam", kolam.total_berat_kolam},
        {"umur_kolam", kolam.umur_kolam},
        {"total_harga_pakan", kolam.total_harga_pakan},
        {"total_modal", kolam.total_modal},
        {"siklus_kolam", kolam.siklus_kolam}};

    j.push_back(kolamjson);

    ofstream fileOut(FILE_KOLAM);
    fileOut << j.dump(4);
    fileOut.close();

    cout << "[BERHASIL] Berhasil Menambah Kolam!!! (ID: " << kolam.id_kolam << ")" << endl;
    system("pause");
    system("cls");
}

void bongkar_kolam()
{
    json j;
    ifstream fileIn(FILE_KOLAM);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "======================================================================" << endl;
    cout << "====================== DAFTAR KOLAM KOSONG ===========================" << endl;
    cout << "======================================================================" << endl;
    cout << left << setw(5)  << "ID" << "| "
         << left << setw(15) << "Tipe" << "| "
         << left << setw(12) << "Kapasitas" << "| "
         << left << setw(12) << "Populasi" << "| "
         << left << setw(15) << "Status" << "|" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    bool kolam_kosong = false;
    for (const auto &item : j)
    {
        if (item["status_kolam"] == "Kosong")
        {
            int id = item.value("id", 0);
            string tipe = item.value("tipe", "-");
            int kapasitas = item.value("kapasitas", 0);
            int populasi = item.value("populasi", 0);
            string status = item.value("status_kolam", "-");

            cout << left << setw(5)  << id << "| "
                 << left << setw(15) << tipe << "| "
                 << left << setw(12) << kapasitas << "| "
                 << left << setw(12) << populasi << "| "
                 << left << setw(15) << status << "|" << endl;
            cout << "----------------------------------------------------------------------" << endl;
            kolam_kosong = true;
        }
    }

    if (!kolam_kosong)
    {
        cout << "\n[INFO] Belum Ada Kolam Yang Berstatus Kosong!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int id_pilihan = -1;
    string input_id;

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Kolam Yang Ingin Di Bongkar/Hapus (0 untuk batal): ";
            getline(cin >> ws, input_id);

            id_pilihan = stoi(input_id);

            if (id_pilihan == 0)
            {
                system("cls");
                return;
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid!!!" << endl;
            system("pause");
            system("cls");

            cout << "======================================================================" << endl;
            cout << "====================== DAFTAR KOLAM KOSONG ===========================" << endl;
            cout << "======================================================================" << endl;
            cout << left << setw(5)  << "ID" << "| "
                 << left << setw(15) << "Tipe" << "| "
                 << left << setw(12) << "Kapasitas" << "| "
                 << left << setw(12) << "Populasi" << "| "
                 << left << setw(15) << "Status" << "|" << endl;
            cout << "----------------------------------------------------------------------" << endl;
            for (const auto &item : j)
            {
                if (item["status_kolam"] == "Kosong")
                {
                    int id = item.value("id", 0);
                        string tipe = item.value("tipe", "-");
                        int kapasitas = item.value("kapasitas", 0);
                        int populasi = item.value("populasi", 0);
                        string status = item.value("status_kolam", "-");

                    cout << left << setw(5)  << id << "| "
                            << left << setw(15) << tipe << "| "
                            << left << setw(12) << kapasitas << "| "
                            << left << setw(12) << populasi << "| "
                            << left << setw(15) << status << "|" << endl;
                    cout << "----------------------------------------------------------------------" << endl;
                }
            }
        }
    }

    bool ditemukan = false;
    for (auto it = j.begin(); it != j.end(); ++it)
    {
        if ((*it)["id"] == id_pilihan && (*it)["status_kolam"] == "Kosong")
        {
            j.erase(it);
            ditemukan = true;
            break;
        }
    }

    if (ditemukan)
    {
        ofstream fileOut(FILE_KOLAM);
        fileOut << j.dump(4);
        fileOut.close();
        cout << "[BERHASIL] Kolam Dengan ID " << id_pilihan << " Telah Di Bongkar!!!" << endl;
    }
    else
    {
        cout << "[ERROR] ID Kolam Tidak Ditemukan / Kolam Sudah Dibongkar!!!" << endl;
    }

    system("pause");
    system("cls");
}

void tebar_benih()
{
    json j, r;
    ifstream fileIn(FILE_KOLAM);
    ifstream fileRek(FILE_REKBER); 

    if (fileIn.is_open())
    {
        if (fileIn.peek() != std::ifstream::traits_type::eof()) {
            fileIn >> j;
        }
        fileIn.close();
    }

    if(fileRek.is_open())
    {
        if (fileRek.peek() != std::ifstream::traits_type::eof()) {
            fileRek >> r;
        }
        fileRek.close();
    }

    // Antisipasi jika Rekber belum memiliki struktur array
    if (r.empty() || !r.is_array()) {
        r = json::array();
        r.push_back({{"rekening_admin", 0.0}});
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "======================================================================" << endl;
    cout << "====================== DAFTAR KOLAM KOSONG ===========================" << endl;
    cout << "======================================================================" << endl;
    cout << left << setw(5)  << "ID" << "| "
         << left << setw(15) << "Tipe" << "| "
         << left << setw(12) << "Kapasitas" << "| "
         << left << setw(12) << "Populasi" << "| "
         << left << setw(15) << "Status" << "|" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    bool kolam_kosong = false;
    for (const auto &item : j)
    {
        if (item["status_kolam"] == "Kosong")
        {
            
            int id = item.value("id", 0);
            string tipe = item.value("tipe", "-");
            int kapasitas = item.value("kapasitas", 0);
            int populasi = item.value("populasi", 0);
            string status = item.value("status_kolam", "-");

            cout << left << setw(5)  << id << "| "
                 << left << setw(15) << tipe << "| "
                 << left << setw(12) << kapasitas << "| "
                 << left << setw(12) << populasi << "| "
                 << left << setw(15) << status << "|" << endl;
            cout << "----------------------------------------------------------------------" << endl;
            kolam_kosong = true;
        }
    }

    if (!kolam_kosong)
    {
        cout << "\n[INFO] Tidak Ada Kolam Kosong Saat Ini. Silahkan Bongkar/Buat Kolam Baru!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int id_kolam = -1;
    string input_pilihan;

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Kolam Yang Ingin Di Tebar Benih (0 untuk batal): ";
            getline(cin >> ws, input_pilihan);
            id_kolam = stoi(input_pilihan);

            if (id_kolam == 0)
            {
                system("cls");
                return;
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid! Masukkan Angka." << endl;
        }
    }

    bool ditemukan = false;
    string jumlah, harga;
    int jumlahBenih, hargaBenih, totalHargaBenih;

    for (auto &item : j)
    {
        if (item["id"] == id_kolam && item["status_kolam"] == "Kosong")
        {
            ditemukan = true;
            bool input_sukses = true;

            while (input_sukses)
            {
                try
                {
                    double saldo_admin = r[0].value("rekening_admin", 0.0); 
                    long long cetak_saldo = (long long)saldo_admin;

                    cout << "\n====== JUMLAH SALDO PERUSAHAAN (SALDO: Rp " << cetak_saldo << ") ======" << endl;
                  
                    cout << "\nInput Jumlah Benih yang ingin anda Tebar (Ekor): ";
                    getline(cin >> ws, jumlah);
                    jumlahBenih = stoi(jumlah);

                    if (jumlahBenih <= 0)
                    {
                        cout << "[ERROR] Jumlah Benih Harus Lebih Dari 0!!!" << endl;
                        continue;
                    }

                    if (jumlahBenih > item["kapasitas"])
                    {
                        cout << "[ERROR] Jumlah Benih Melebihi Kapasitas Kolam!!!" << endl;
                        continue;
                    }

                    cout << "Input Harga Benih (Rp/Ekor): ";
                    getline(cin >> ws, harga);
                    hargaBenih = stoi(harga);

                    if (hargaBenih <= 0)
                    {
                        cout << "[ERROR] Harga Benih Harus Lebih Dari 0!!!" << endl;
                        continue;
                    }

                    totalHargaBenih = jumlahBenih * hargaBenih;

                    if (saldo_admin < totalHargaBenih)
                    {
                        cout << "\n[ERROR] Saldo Perusahaan Tidak Mencukupi!!!" << endl;
                        cout << "Sisa Saldo: Rp " << cetak_saldo << " | Butuh: Rp " << totalHargaBenih << endl;
                        continue; 
                    }

                    // Potong saldo di memori
                    r[0]["rekening_admin"] = saldo_admin - totalHargaBenih;

                    // Update data kolam harian
                    item["total_harga_benih"] = totalHargaBenih;
                    item["status_kolam"] = "Terisi";
                    item["populasi"] = jumlahBenih;
                    item["fase_kolam"] = "Benih";

                    int populasi = item["populasi"];
                    item["total_berat_kolam"] = populasi * 1; // Asumsi berat awal 1 gram per ekor

                    input_sukses = false;
                }
                catch (const exception &e)
                {
                    cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                }
            }
            break;
        }
    }

    if (ditemukan)
    {
        // Save Data Kolam
        ofstream fileOut(FILE_KOLAM);
        fileOut << j.dump(4);
        fileOut.close();

        // Tulis  data Rekber ke file agar saldo berkurang permanen
        ofstream fileOutRek(FILE_REKBER);
        fileOutRek << r.dump(4);
        fileOutRek.close();

        cout << "\n[BERHASIL] Kolam Dengan ID " << id_kolam << " Telah Di Tebar Benih!!!" << endl;
    }
    else
    {
        cout << "\n[ERROR] ID Kolam Tidak Ditemukan atau Kolam Sudah Terisi!!!" << endl;
    }

    system("pause");
    system("cls");
}

void beli_pakan()
{
    json j_pakan = load_json(FILE_PAKAN, "[INFO] Data Pakan Belum Dibuat!!!");
    json r_rekber = load_json(FILE_REKBER, "[INFO] Data Rekening Belum Dibuat!!!");

    if (j_pakan.empty() || r_rekber.empty())
    {
        cout << "[ERROR] FILE JSON Data Pakan & Rekber Kosong Melompong!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int jumlah_beli, harga_beli, total_biaya;
    string input_jumlah, input_harga;

    system("cls");
    cout << "==============================================" << endl;
    cout << "============= MENU BELI PAKAN ================" << endl;
    cout << "==============================================" << endl;

    double saldo_admin = r_rekber[0].value("rekening_admin", 0.0); 
    long long cetak_saldo = (long long)saldo_admin;

    cout << "\n====== JUMLAH SALDO PERUSAHAAN (SALDO: " << cetak_saldo << ") ======" << endl;
                 
    while (true)
    {
        try
        {
            cout << "Input Jumlah Pakan yang dibeli (Kilogram): ";
            getline(cin >> ws, input_jumlah);
            jumlah_beli = stoi(input_jumlah);

            if (jumlah_beli <= 0)
            {
                cout << "[ERROR] Jumlah Pakan Harus Lebih Dari 0!!!" << endl;
                continue;
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
        }
    }

    while (true)
    {
        try
        {
            cout << "Input Harga Pakan Baru (Rp/Kg): ";
            getline(cin >> ws, input_harga);
            harga_beli = stoi(input_harga);

            if (harga_beli <= 0)
            {
                cout << "[ERROR] Harga Pakan Harus Lebih Dari 0!!!" << endl;
                continue;
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
        }
    }

    total_biaya = jumlah_beli * harga_beli;

    double saldo_perusahaan = r_rekber[0].value("rekening_admin", 0.0);

    if (saldo_perusahaan < total_biaya)
    {
        cout << "\n[ERROR] Saldo Perusahaan Tidak Mencukupi!!!" << endl;
        cout << "Sisa Saldo Kas: Rp " << saldo_perusahaan << " | Butuh Kas: Rp " << total_biaya << endl;
        system("pause");
        system("cls");
        return; 
    }

    r_rekber[0]["rekening_admin"] = saldo_perusahaan - total_biaya;

    for (auto &item : j_pakan)
    {
        int stok_lama = item.value("stok_kg", 0);
        int modal_lama = item.value("total_modal_pakan", 0);

        item["stok_kg"] = stok_lama + jumlah_beli;
        item["harga_per_kg"] = harga_beli; 
        item["total_modal_pakan"] = modal_lama + total_biaya; 
    }

    ofstream outPakan(FILE_PAKAN);
    outPakan << j_pakan.dump(4);
    outPakan.close();

    ofstream outRek(FILE_REKBER);
    outRek << r_rekber.dump(4);
    outRek.close();

    cout << "\n[BERHASIL] Pembelian Pakan Sukses Masuk ke Gudang!!!" << endl;
    cout << "[INFO] Uang Kas Perusahaan Otomatis Dipotong: Rp " << total_biaya << endl;

    system("pause");
    system("cls");
}

void tampilkan_data_pakan()
{
    json j = load_data_pakan();

    if (j.empty())
    {
        cout << "[INFO] Data Pakan Masih Kosong!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (auto &item : j)
    {
        double stok = item.value("stok_kg", 0.0);
        
        // Pakai long long karena nominal uang yang berpotensi besar
        long long harga = item.value("harga_per_kg", 0);
        long long total_harga = item.value("total_modal_pakan", 0);

        cout << "\n=================================" << endl;
        cout << "         DATA STOCK PAKAN        " << endl;
        cout << "=================================" << endl;
        cout << "Stok Gudang    : " << stok << " Kg" << endl;
        cout << "Harga Rata-Rata: Rp " << harga << " /Kg" << endl;
        cout << "Total Modal    : Rp " << total_harga << endl;
        cout << "=================================" << endl;
    }

    system("pause");
    system("cls");
}

void jual_ikan()
{
    json j, r, s;
    ifstream fileklm(FILE_KOLAM);
    ifstream filejl(FILE_REKBER);
    ifstream files(FILE_STAFF);

    if (filejl.is_open())
    {
        filejl >> r;
        filejl.close();
    }

    if (files.is_open())
    {
        files >> s;
        files.close();
    }

    if (fileklm.is_open())
    {
        fileklm >> j;
        fileklm.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    bool kolam_panen = true;
    for (const auto &item : j)
    {
        if (item["status_kolam"] == "Panen")
        {
            kolam_panen = false;
        }
    }

    if (kolam_panen)
    {
        cout << "[INFO] Belum Ada Kolam Dengan Status Panen Saat Ini!!!" << endl;
        system("pause");
        system("clear");
        return;
    }
    else if (!kolam_panen)
    {
        system("cls");
        cout << "======================================================================" << endl;
        cout << "====================== DAFTAR KOLAM SIAP PANEN =======================" << endl;
        cout << "======================================================================" << endl;
        cout << left << setw(5)  << "ID" << "| "
             << left << setw(15) << "Tipe" << "| "
             << left << setw(12) << "Kapasitas" << "| "
             << left << setw(12) << "Populasi" << "| "
             << left << setw(15) << "Status" << "|" << endl;
        cout << "----------------------------------------------------------------------" << endl;

        for (int i = 0; i < j.size(); i++)
        {
            for (int k = 0; k < j.size() - 1 - i; k++)
            {
                if (j[k]["id"] > j[k + 1]["id"])
                {
                    swap(j[k], j[k + 1]);
                }
            }
        }

        for (const auto &item : j)
        {
            if (item["status_kolam"] == "Panen")
            {
                int id = item.value("id", 0);
                string tipe = item.value("tipe", "-");
                int kapasitas = item.value("kapasitas", 0);
                int populasi = item.value("populasi", 0);
                string status = item.value("status_kolam", "-");

                cout << left << setw(5)  << id << "| "
                    << left << setw(15) << tipe << "| "
                    << left << setw(12) << kapasitas << "| "
                    << left << setw(12) << populasi << "| "
                    << left << setw(15) << status << "|" << endl;
                cout << "----------------------------------------------------------------------" << endl;
            }
        }

        string input_id;
        int id;

        while (true)
        {
            try
            {
                cout << "Masukan ID Kolam Yang Ingin Dipanen & Dijual (0 Untuk Batal): ";
                getline(cin >> ws, input_id);

                id = stoi(input_id);

                if (id == 0)
                {
                    system("cls");
                    return;
                }

                break;
            }
            catch (const exception &e)
            {
                cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                cout << "[INFO] Silahkan Coba Lagi!!!" << endl;
                system("pause");
                system("cls");

                cout << "======================================================================" << endl;
                cout << "====================== DAFTAR KOLAM SIAP PANEN =======================" << endl;
                cout << "======================================================================" << endl;
                cout << left << setw(5)  << "ID" << "| "
                     << left << setw(15) << "Tipe" << "| "
                     << left << setw(12) << "Kapasitas" << "| "
                     << left << setw(12) << "Populasi" << "| "
                     << left << setw(15) << "Status" << "|" << endl;
                cout << "----------------------------------------------------------------------" << endl;

                for (int i = 0; i < j.size(); i++)
                {
                    for (int k = 0; k < j.size() - 1 - i; k++)
                    {
                        if (j[k]["id"] > j[k + 1]["id"])
                        {
                            swap(j[k], j[k + 1]);
                        }
                    }
                }

                for (const auto &item : j)
                {
                    if (item["status_kolam"] == "Panen")
                    {
                        int id = item.value("id", 0);
                        string tipe = item.value("tipe", "-");
                        int kapasitas = item.value("kapasitas", 0);
                        int populasi = item.value("populasi", 0);
                        string status = item.value("status_kolam", "-");

                        cout << left << setw(5)  << id << "| "
                            << left << setw(15) << tipe << "| "
                            << left << setw(12) << kapasitas << "| "
                            << left << setw(12) << populasi << "| "
                            << left << setw(15) << status << "|" << endl;
                        cout << "----------------------------------------------------------------------" << endl;
                    }
                }
            }
        }

        bool ditemukan = false;
        for (auto &item : j)
        {
            if (item["id"] == id && item["status_kolam"] == "Panen")
            {
                double jumlah_ikan = item["populasi"];
                double harga_benih = item["total_harga_benih"];
                double harga_pakan = item.value("total_harga_pakan", 0.0);
                
                double modal = harga_benih + harga_pakan;
                
                double harga_ikan = (modal + (modal * 2)) / jumlah_ikan;
                double total_kotor = jumlah_ikan * harga_ikan; 
                double gaji_staff_total = total_kotor * 0.5; 
                double keuntungan_bersih = total_kotor - (gaji_staff_total + modal); 
                double uang_kas_masuk = modal + keuntungan_bersih;

                // Gaji Staff
                int jumlah_staff_aktif = 0;
                for (auto &st : s)
                {
                    if (st["status_kerja"] == true)
                    {
                        jumlah_staff_aktif++;
                    }
                }

                if (jumlah_staff_aktif > 0)
                {
                    double gaji_per_orang = gaji_staff_total / jumlah_staff_aktif;

                    json riwayatj = load_json(FILE_GAJI, "");
                    if(!riwayatj.is_array())
                    {
                        riwayatj = json::array();
                    }

                    for (auto &st : s)
                    {
                        if (st["status_kerja"] == true)
                        {
                            double saldo = st.value("saldo", 0.0);
                            st["saldo"] = saldo + gaji_per_orang;

                            json riwayat_baru = {
                                {"id_staff", st["id"]},
                                {"nama_staff", st["nama"]},
                                {"id_kolam_panen", id},
                                {"nominal_gaji", gaji_per_orang}
                            };
                            riwayatj.push_back(riwayat_baru);
                        }
                    }

                    ofstream fileOutRiwayat(FILE_GAJI);
                    fileOutRiwayat << riwayatj.dump(4);
                    fileOutRiwayat.close();

                    long long gaji_staff = (long long) gaji_staff_total;
                    cout << "\n[SUCCESS] Gaji Total (Rp " << gaji_staff << ") Telah Dibagikan Kepada " << jumlah_staff_aktif << " Staff!!!" << endl;
                }
                else
                {
                    uang_kas_masuk += gaji_staff_total; 
                    keuntungan_bersih += gaji_staff_total;
                    cout << "\n[UNTUNG] Tidak Ada Staff Aktif. Jatah Gaji Masuk Ke Rekening Perusahaan!!!" << endl;
                }

                // REKBER ADMIN
                double saldo_admin_lama = r[0].value("rekening_admin", 0.0);
                
                // Masukkan uang_kas_masuk ke rekening admin (Modal + Untung)
                r[0]["rekening_admin"] = saldo_admin_lama + uang_kas_masuk;

                long long cetak_kas = (long long) uang_kas_masuk;
                cout << "[SUCCESS] Kas Masuk (Modal + Untung: Rp " << cetak_kas << ") Telah Masuk Ke Rekening Admin!!!" << endl;

                // Reset Kolam
                item["hargaBenih"] = 0;
                item["populasi"] = 0;
                item["status_kolam"] = "Kosong";
                item["total_harga_benih"] = 0;
                item["total_mati"] = 0;
                item["total_harga_pakan"] = 0;

                json keuanganj = load_json(FILE_KEUANGAN, "");
                if(!keuanganj.is_array()){
                    keuanganj = json::array();
                }
                
                int id_transaksi_baru = 1;
                if(!keuanganj.empty())
                {
                    id_transaksi_baru = keuanganj.back().value("id_transaksi", 0) + 1;
                }

                int siklus_lama = item.value("siklus_panen", 0);
                int siklus_baru = siklus_lama + 1;
                item["siklus_panen"] = siklus_baru;

                // Masukan Data Ke JSON LK
                json keuangan_baru = {
                    {"id_transaksi", id_transaksi_baru},
                    {"id_penjualan_kolam", id},
                    {"pengeluaran", modal},
                    {"untung_bersih", keuntungan_bersih},
                    {"keterangan", "Panen Kolam ID " + to_string(id) + " (Siklus " + to_string(siklus_baru) + ")"}
                };

                keuanganj.push_back(keuangan_baru);

                ofstream fileOutKeuangan(FILE_KEUANGAN);
                fileOutKeuangan << keuanganj.dump(4);
                fileOutKeuangan.close();

                ditemukan = true;
                break;
            }
        }

        if (ditemukan)
        {
            ofstream outkolam(FILE_KOLAM);
            outkolam << j.dump(4);
            outkolam.close();

            ofstream outrekening(FILE_REKBER);
            outrekening << r.dump(4);
            outrekening.close();

            ofstream outstaff(FILE_STAFF);
            outstaff << s.dump(4);
            outstaff.close();

            cout << "[BERHASIL] Ikan Di Kolam Dengan (ID: " << id << ") Telah Terjual Semua !!!" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            cout << "[ERROR] ID Kolam Tidak Ditemukan!!!" << endl;
            system("pause");
            system("cls");
        }
    }
}

void laporan_keuangan()
{
    json j = load_json(FILE_KEUANGAN, "[INFO] Belum Ada Riwayat Penjualan / Laporan Keuangan!!!");
    
    if (j.empty())
    {
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0; i < (int)j.size(); i++)
    {
        for (int k = 0; k < (int)j.size() - 1 - i; k++)
        {
            if (j[k]["id_penjualan_kolam"] > j[k + 1]["id_penjualan_kolam"])
            {
                swap(j[k], j[k + 1]);
            }
        }
    }

    double total_pengeluaran = 0.0;
    double total_untung = 0.0;

    system("cls");
    cout << "=========================================================================================" << endl;
    cout << "                         BUKU BESAR & LAPORAN KEUANGAN TAMBAK                            " << endl;
    cout << "=========================================================================================" << endl;
    cout << "ID Nota | Keterangan Transaksi           | Pengeluaran (Modal)  | Keuntungan Bersih     |" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    for (const auto &item : j)
    {
        int id = item["id_transaksi"]; 
        string ket = item["keterangan"];
        double pengeluaran = item["pengeluaran"];
        double untung = item["untung_bersih"];

        total_pengeluaran += pengeluaran;
        total_untung += untung;

        cout << "   " << id << "\t| " << ket << "\t | Rp " << (long long)pengeluaran << "\t\t| Rp " << (long long)untung << "\n";
    }

    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << " [+] TOTAL AKUMULASI MODAL DIKELUARKAN  : Rp " << (long long)total_pengeluaran << endl;
    cout << " [+] TOTAL AKUMULASI KEUNTUNGAN BERSIH  : Rp " << (long long)total_untung << endl;
    cout << "=========================================================================================" << endl;
    cout << "\n";

    system("pause");
    system("cls");
}

void laporan_staff(int id)
{
    json j;
    ifstream fileIn(FILE_LAPORAN);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    bool valid = false;

    cout << "\n========================================================" << endl;
    cout << "============== KINERJA STAFF BERDASARKAN ID ============" << endl;
    cout << "========================================================" << endl;

    for (const auto &item : j)
    {
        if(item["id_staff"] == id)
        {
            valid = true;
            cout << "ID Staff     : " << item["id_staff"] << endl;
            cout << "Kegiatan     : " << item["jenis_kegiatan"] << endl;
            cout << "Dicatat Oleh : " << item["dicatat_oleh"] << endl;
            cout << "ID Kolam     : " << item["id_kolam"] << endl;

            if (item["jenis_kegiatan"] == "Tebar Pakan")
            {
                cout << "Total Pakan  : " << item["total_pakan_gram"] << " gram" << endl;
                cout << "Total Biaya  : Rp " << item["total_biaya"] << endl;
            }
            else if (item["jenis_kegiatan"] == "Catat Mortalitas")
            {
                cout << "Total Mati   : " << item["total_mati"] << " ekor" << endl;
                cout << "Pop. Akhir   : " << item["populasi_akhir"] << " ekor" << endl;
            }
            cout << "--------------------------------------------------------" << endl;
        }
    }

    if (valid)
    {
        cout << "\n[SUCCESS] Staff Dengan (ID: " << id << ") Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "\n[ERROR] Staff Dengan (ID: " << id << ") Tidak Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
}

void laporan_staff()
{
    json j;
    ifstream fileIn(FILE_LAPORAN);

    if(fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    json s;
    ifstream filest(FILE_STAFF);

    if(filest.is_open())
    {
        filest >> s;
        filest.close();
    }

    if(j.empty())
    {
        cout << "[INFO] Belum Ada Data Laporan Dari Staff!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    string pilihan_menu, input_id;
    int pilihan, id;
    bool loop = true;

    while (loop)
    {
        system("cls");
        cout << "==============================================" << endl;
        cout << "========== MENU LIHAT KINERJA STAFF ==========" << endl;
        cout << "==============================================" << endl;
        cout << "1. Lihat Kinerja Staff Berdasarkan ID Staff" << endl;
        cout << "2. Lihat Kinerja Staff Dari Laporan Tebar Pakan " << endl;
        cout << "3. Lihat Kinerja Staff Dari Laporan Mortalitas" << endl;
        cout << "4. Keluar" << endl;
        cout << "Masukan Pilihan: ";
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
                system("cls");

                while(true)
                {
                    system("cls");
                    cout << "=======================================================" << endl;
                    cout << "================== DAFTAR STAFF AKTIF =================" << endl;
                    cout << "=======================================================" << endl;
                    cout << left << setw(5)  << "ID" << "| "
                        << left << setw(20) << "Username" << "| "
                        << left << setw(15) << "Status" << "|" << endl;
                    cout << "-------------------------------------------------------" << endl;

                    for (int i = 0; i < s.size(); i++)
                    {
                        for (int k = 0; k < s.size() - 1 - i; k++)
                        {
                            if (s[k]["id"] > s[k + 1]["id"])
                            {
                                swap(s[k], s[k + 1]);
                            }
                        }
                    }

                    for (const auto &item : s)
                    {
                        if (item["status_terima"] == true && item["status_kerja"] == true)
                        {
                            int id = item.value("id", 0);
                            string nama = item.value("nama", "-");

                            cout << left << setw(5)  << id << "| "
                                << left << setw(20) << nama << "| "
                                << left << setw(15) << "Aktif Bekerja" << "|" << endl;
                            cout << "-------------------------------------------------------" << endl;
                        }
                    }

                    try
                    {
                        cout << "Masukan ID Staff Yang Ingin Di Lihat Kinerjanya (Input 0 Untuk Batal): ";
                        getline(cin >> ws, input_id);

                        id = stoi(input_id);

                        if(id == 0)
                        {
                            system("cls");
                            return;
                        }

                        break;
                    }
                    catch (const exception &e)
                    {
                        cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                        system("pause");
                    }
                }

                laporan_staff(id);

                break;

            case 2:
                system("cls");
                cout << "=======================================================" << endl;
                cout << "========== KINERJA STAFF LAPORAN TEBAR PAKAN ==========" << endl;
                cout << "=======================================================" << endl;

                for (int i = 0; i < j.size(); i++)
                {
                    for (int k = 0; k < j.size() - 1 - i; k++)
                    {
                        if (j[k]["id_kolam"] > j[k + 1]["id_kolam"])
                        {
                            swap(j[k], j[k + 1]);
                        }
                    }
                }

                for (const auto &item : j)
                {
                    if (item["jenis_kegiatan"] == "Tebar Pakan")
                    {
                        cout << "ID Kolam       : " << item["id_kolam"] << endl;
                        cout << "Rentang Hari   : " << item["rentang_hari"] << endl;
                        cout << "Total Pakan    : " << item["total_pakan_gram"] << " gram" << endl;
                        cout << "Total Biaya    : " << item["total_biaya"] << endl;
                        cout << "Dicatat Oleh   : " << item["dicatat_oleh"] << endl;
                        cout << "ID Staff       : " << item["id_staff"] << endl;
                        cout << "==============================================" << endl;
                    }
                }

                system("pause");
                system("cls");
                break;

            case 3:
                system("cls");
                cout << "=======================================================" << endl;
                cout << "=========== KINERJA STAFF LAPORAN MORTALITAS ==========" << endl;
                cout << "=======================================================" << endl;

                for (int i = 0; i < j.size(); i++)
                {
                    for (int k = 0; k < j.size() - 1 - i; k++)
                    {
                        if (j[k]["id_kolam"] > j[k + 1]["id_kolam"])
                        {
                            swap(j[k], j[k + 1]);
                        }
                    }
                }

                for (const auto &item : j)
                {
                    if (item["jenis_kegiatan"] == "Catat Mortalitas")
                    {
                        cout << "ID Kolam       : " << item["id_kolam"] << endl;
                        cout << "Total Mati     : " << item["total_mati"] << endl;
                        cout << "Populasi Akhir : " << item["populasi_akhir"] << endl;
                        cout << "Dicatat oleh   : " << item["dicatat_oleh"] << endl;
                        cout << "ID Staff       : " << item["id_staff"] << endl;
                        cout << "==============================================" << endl;
                    }
                }

                system("pause");
                system("cls");
                break;

            case 4:
                system("cls");
                loop = false;
                break;
        }
    }
}

void rekber_admin()
{
    json r_rekber = load_json(FILE_REKBER, "[INFO] Data Rekening Admin Belum Dibuat!!!");

    if (r_rekber.empty())
    {
        system("pause");
        system("cls");
        return;
    }

    //pakai [0] karena bentuknya array
    double saldo_admin = r_rekber[0].value("rekening_admin", 0.0);

    //Konversi ke bilangan bulat panjang biar nggak muncul huruf 'e' 
    long long cetak_saldo = (long long)saldo_admin;

    
    string status_keuangan;
    if (cetak_saldo >= 50000000) 
    {
        status_keuangan = "DANA AMAN !!!";
    } 
    else if (cetak_saldo >= 15000000) 
    {
        status_keuangan = "DANA STABIL !!!";
    } 
    else if (cetak_saldo >= 5000000) 
    {
        status_keuangan = "DANA CUKUP !!!";
    } 
    else 
    {
        status_keuangan = "DAH NAK BANGKRUT NI !!!";
    }

    system("cls");
    cout << "=========================================================" << endl;
    cout << "                 BRANKAS UTAMA PERUSAHAAN                " << endl;
    cout << "                 >>   PT TAMBAK LELE   <<                " << endl;
    cout << "=========================================================" << endl;
    cout << "                                                         " << endl;
    cout << "   [+] TOTAL KAS TERSEDIA : Rp " << cetak_saldo << endl;
    cout << "                                                         " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "   [*] STATUS KEUANGAN    : " << status_keuangan << endl;
    cout << "   [*] HAK AKSES          : Executive Admin              " << endl;
    cout << "                                                         " << endl;
    cout << "=========================================================" << endl;
    cout << "   [!] Gunakan Dana Dengan Bijak Jangan Sampai Bangkrut  " << endl;
    cout << "=========================================================" << endl;
    cout << "\n";

    system("pause");
    system("cls");
}
