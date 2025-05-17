// Class Buku berisi informasi seperti judul, penulis, dan status peminjaman (bool dipinjam). Status ini bersifat privat dan tidak
// dapat diubah langsung oleh sembarang class. Hanya class Petugas yang dapat memproses status peminjaman atau pengembalian buku.
// Oleh karena itu, class Petugas harus dijadikan sebagai friend class dari Buku, sehingga dapat memodifikasi status peminjaman
// dengan method seperti prosesPinjam(Buku* b, Peminjam* p) dan prosesKembali(Buku* b).

// Class Peminjam menyimpan data pengguna seperti nama dan ID, serta jumlah buku yang sedang dipinjam (int totalPinjaman).
// Atribut totalPinjaman bersifat privat dan hanya dapat diubah oleh class Petugas yang memproses peminjaman atau pengembalian.
// Oleh karena itu, Petugas juga dijadikan friend class oleh Peminjam.

// Class Petugas bertanggung jawab terhadap operasional peminjaman dan pengembalian. Selain itu, ia memiliki atribut pribadi seperti
// nama, ID petugas, dan level akses (string levelAkses). Namun, hanya class Admin yang boleh mengubah level akses petugas
// berdasarkan performa. Karena itu, class Admin harus dijadikan friend class oleh Petugas.

// Terakhir, class Admin hanya berhak melihat statistik data, termasuk jumlah buku yang sedang dipinjam oleh seorang peminjam, dan
// melihat nama buku yang sedang diproses oleh petugas, tetapi tidak memiliki akses penuh terhadap atribut private class lain.
// Untuk itu, informasi-informasi tersebut diberikan melalui friend function yang didefinisikan di dalam class Peminjam dan Buku,
// tetapi diimplementasikan di dalam class Admin. Dengan kata lain, Admin hanya diizinkan mengakses data privat
// melalui fungsi friend yang disediakan secara terbatas.

#include <iostream>
#include <string>
using namespace std;

class Buku;
class Peminjam;
class Petugas;
class Admin;

class Buku
{
private:
    string judul;
    string penulis;
    bool dipinjam;
public:
    void setJudul(string pJudul);
    void setPenulis(string pPenulis);
    void setDipinjam(bool pDipinjam);
    void prosesPinjam(Buku* b, Peminjam* p);
    void prosesKembali(Buku* b);
    friend class Petugas;
};
class Peminjam
{
    private:
        int totalPinjaman;
    public:
        string nama;
        string id;
        void setTotalPinjaman(int jumlah) { totalPinjaman = jumlah; }
        void prosesPinjam(Buku* b, Peminjam* p);
        void prosesKembali(Buku* b);
        friend class Petugas;
        friend class Admin;
};
void Buku::setJudul(string pJudul)
{
    judul = pJudul;
}
void Buku::setPenulis(string pPenulis)
{
    penulis = pPenulis;
}
void Buku::setDipinjam(bool pDipinjam)
{
    dipinjam = pDipinjam;
}

class Petugas
{
    private:
        string nama;
        string id;
        string levelAkses;
    public:
        void setNama(string pNama);
        void setId(string pId);
        void setLevelAkses(string pLevelAkses);
        void prosesPinjam(Buku* b, Peminjam* p);
        void prosesKembali(Buku* b);
        friend class Admin;
};
void Petugas::setNama(string pNama)
{
    nama = pNama;
}
void Petugas::setId(string pId)
{
    id = pId;
}
void Petugas::setLevelAkses(string pLevelAkses)
{
    levelAkses = pLevelAkses;
}
void Petugas::prosesPinjam(Buku* b, Peminjam* p)
{
    if (b->dipinjam == false)
    {
        b->dipinjam = true;
        p->totalPinjaman++;
        cout << "Buku " << b->judul << " berhasil dipinjam oleh " << p->nama << endl;
        cout << "Total Pinjaman: " << p->totalPinjaman << endl;

    }
    else
    {
        cout << "Buku " << b->judul << " sudah dipinjam." << endl;
        
    }
}
void Petugas::prosesKembali(Buku* b)
{
    if (b->dipinjam == true)
    {
        b->dipinjam = false;
        cout << "Buku " << b->judul << " berhasil dikembalikan." << endl;
    }
    else
    {
        cout << "Buku " << b->judul << " tidak sedang dipinjam." << endl;
    }
}

class Admin
{
    private:
        string nama;
        string id;
    public:
        void setNama(string pNama) { nama = pNama; }
        void setId(string pId) { id = pId; }
        void lihatStatistik(Peminjam* p);
        void lihatBukuDiproses(Petugas* t);
        friend void Petugas::prosesPinjam(Buku* b, Peminjam* p);
        friend void Petugas::prosesKembali(Buku* b);
};
void Admin::lihatStatistik(Peminjam* p)
{
    cout << "Peminjam: " << p->nama << endl;
    cout << "ID Peminjam: " << p->id << endl;
    cout << "Total Pinjaman: " << p->totalPinjaman << endl;
}
void Admin::lihatBukuDiproses(Petugas* t)
{
    cout << "Petugas: " << t->nama << endl;
    cout << "ID Petugas: " << t->id << endl;
    cout << "Level Akses: " << t->levelAkses << endl;
}
int main()
{
    Buku a;
    a.setJudul("Atomics");
    a.setPenulis("James Clear");
    a.setDipinjam(false);

    Peminjam p;
    p.nama = "uwik";
    p.id = "TI23";
    p.setTotalPinjaman(0);

    Petugas t;
    t.setNama("ambon");
    t.setId("TI24");
    Admin a1;
    a1.setNama("Admin User");
    a1.setId("A001");

    t.prosesPinjam(&a, &p);
    a1.lihatStatistik(&p);
    t.prosesKembali(&a);
    a1.lihatBukuDiproses(&t);
    t.prosesKembali(&a);
    a1.lihatBukuDiproses(&t);
    t.prosesPinjam(&a, &p);
    a1.lihatStatistik(&p);
    t.prosesKembali(&a);
    a1.lihatBukuDiproses(&t);
    t.prosesKembali(&a); 
    
    return 0;
}

// selesai




