#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// ============================================================
//  Abstract Base Class
// ============================================================
class RekeningBank {
protected:
    string namaNasabah;
    string nomorRekening;
    double saldo;

public:
    RekeningBank(string nama, string noRek, double saldoAwal)
        : namaNasabah(nama), nomorRekening(noRek), saldo(saldoAwal) {}

    virtual void potongAdmin() = 0;   // pure virtual
    virtual ~RekeningBank() {}

    string getNama()          const { return namaNasabah; }
    string getNomorRekening() const { return nomorRekening; }
    double getSaldo()         const { return saldo; }

    virtual void tampilInfo() const {
        cout << "  Nasabah  : " << namaNasabah   << endl;
        cout << "  No. Rek  : " << nomorRekening  << endl;
        cout << "  Saldo    : Rp " << saldo        << endl;
    }
};


// ============================================================
//  Rekening Syariah — bebas biaya admin
// ============================================================
class RekeningSyariah : public RekeningBank {
public:
    RekeningSyariah(string nama, string noRek, double saldoAwal)
        : RekeningBank(nama, noRek, saldoAwal) {}

    void potongAdmin() override {
        cout << "  [Syariah]       Tidak ada potongan admin (prinsip syariah)." << endl;
    }

    void tampilInfo() const override {
        cout << "  Jenis    : Rekening Syariah" << endl;
        RekeningBank::tampilInfo();
    }
};


// ============================================================
//  Rekening Konvensional — potong Rp 15.000 tiap bulan
// ============================================================
class RekeningKonvensional : public RekeningBank {
private:
    static const double BIAYA_ADMIN;

public:
    RekeningKonvensional(string nama, string noRek, double saldoAwal)
        : RekeningBank(nama, noRek, saldoAwal) {}

    void potongAdmin() override {
        if (saldo >= BIAYA_ADMIN) {
            saldo -= BIAYA_ADMIN;
            cout << "  [Konvensional]  Biaya admin Rp " << BIAYA_ADMIN
                 << " berhasil dipotong." << endl;
        } else {
            cout << "  [Konvensional]  Saldo tidak cukup untuk biaya admin!" << endl;
        }
    }

    void tampilInfo() const override {
        cout << "  Jenis    : Rekening Konvensional" << endl;
        RekeningBank::tampilInfo();
    }
};

const double RekeningKonvensional::BIAYA_ADMIN = 15000.0;


// ============================================================
//  Rekening Premium — dinamis berdasarkan saldo
//    saldo >  10.000.000  →  bebas admin
//    saldo <= 10.000.000  →  potong Rp 50.000
// ============================================================
class RekeningPremium : public RekeningBank {
private:
    static const double BATAS_BEBAS_ADMIN;
    static const double BIAYA_ADMIN_PREMIUM;

public:
    RekeningPremium(string nama, string noRek, double saldoAwal)
        : RekeningBank(nama, noRek, saldoAwal) {}

    void potongAdmin() override {
        if (saldo > BATAS_BEBAS_ADMIN) {
            cout << "  [Premium]       Saldo di atas Rp " << BATAS_BEBAS_ADMIN
                 << ", bebas biaya admin." << endl;
        } else {
            saldo -= BIAYA_ADMIN_PREMIUM;
            cout << "  [Premium]       Saldo <= Rp " << BATAS_BEBAS_ADMIN
                 << ", biaya admin Rp " << BIAYA_ADMIN_PREMIUM << " dipotong." << endl;
        }
    }

    void tampilInfo() const override {
        cout << "  Jenis    : Rekening Premium" << endl;
        RekeningBank::tampilInfo();
    }
};

const double RekeningPremium::BATAS_BEBAS_ADMIN   = 10000000.0;
const double RekeningPremium::BIAYA_ADMIN_PREMIUM  = 50000.0;


void garis() { cout << string(52, '-') << endl; }


// ============================================================
//  main — server bank memproses akhir bulan
// ============================================================
int main() {
    cout << fixed << setprecision(0);

    cout << endl;
    cout << "  ==========================================" << endl;
    cout << "         BANK GIBRAN JAYA                  " << endl;
    cout << "     Proses Biaya Admin Akhir Bulan         " << endl;
    cout << "  ==========================================" << endl;
    cout << endl;

    vector<RekeningBank*> daftarRekening;

    daftarRekening.push_back(new RekeningSyariah(    "Ahmad Fauzi",   "SYR-001",  5000000.0));
    daftarRekening.push_back(new RekeningKonvensional("Budi Santoso", "KON-002",  2500000.0));
    daftarRekening.push_back(new RekeningKonvensional("Citra Dewi",   "KON-003",    10000.0));
    daftarRekening.push_back(new RekeningPremium(    "Diana Pratiwi", "PRM-004", 15000000.0));
    daftarRekening.push_back(new RekeningPremium(    "Eko Wahyudi",   "PRM-005",  8000000.0));

    cout << "  === SALDO SEBELUM PROSES ===" << endl << endl;
    for (RekeningBank* rek : daftarRekening) { garis(); rek->tampilInfo(); }
    garis();

    cout << endl << "  === PROSES POTONGAN ADMIN ===" << endl << endl;
    for (RekeningBank* rek : daftarRekening) {
        garis();
        cout << "  Memproses : " << rek->getNama() << endl;
        rek->potongAdmin();
    }
    garis();

    cout << endl << "  === SALDO SESUDAH PROSES ===" << endl << endl;
    for (RekeningBank* rek : daftarRekening) { garis(); rek->tampilInfo(); }
    garis();

    for (RekeningBank* rek : daftarRekening) delete rek;

    cout << endl << "  Proses akhir bulan selesai." << endl;
    cout << "  ==========================================" << endl << endl;

    return 0;
}