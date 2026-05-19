#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>
using namespace std;

struct Kolam
{
    int id_kolam;
    string status_kolam;
    string tipe_kolam;
    string fase_kolam;
    int kapasitas;
    int populasi_ikan;
    int total_mati;
    double total_harga_benih;
    double total_berat_kolam; // gram
    double total_harga_pakan;
    double total_modal;
    int umur_kolam;
    int siklus_kolam;
};

struct Staff
{
    int id_staff;
    string username;
    string password;
    bool regis_status;
    bool employed_status;
    double saldo;
};

struct Admin
{
    int id_admin;
    string username;
    string password;
};

struct Balance
{
    int total_modal;
    int total_keuntungan;
};

struct Keuangan
{
    int id_penjualan_kolam;
    double pengeluaran;
    double untung_bersih;
    string keterangan;
};

struct Pakan
{
    int stok_kg;
    int harga_per_kg;
    int total_modal_pakan;
};

#endif