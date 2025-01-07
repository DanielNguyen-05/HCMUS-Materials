#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

/*
class PhanSo {
    private:
        int tu, mau;
    public:
        friend istream& operator >> (istream& in, PhanSo& a);
        friend ostream& operator << (ostream& out, PhanSo a);
        // PhanSo operator + (PhanSo);
        friend PhanSo operator + (PhanSo, PhanSo);
        void rutGon();
        friend int getUCLN(int, int);
};
 
istream& operator >> (istream& in, PhanSo& a) {
    cout << "Nhap tu so: "; in >> a.tu;
    cout << "Nhap mau so: "; in >> a.mau;
    return in;
}

ostream& operator << (ostream& out, PhanSo a) {
    out << a.tu << "/" << a.mau;
    return out;
}

int getUCLN(int a, int b) {
    if (b == 0) return a; 
    return getUCLN(b, a % b);
}

void PhanSo::rutGon() {
    int r = getUCLN(this->tu, this->mau);
    this->tu /= r;
    this->mau /= r;
}

// PhanSo PhanSo::operator + (PhanSo another) {
//     PhanSo x;
//     another.rutGon();
//     x.tu = this->tu * another.mau + another.tu * this->mau;
//     x.mau = this->mau * another.mau;
//     x.rutGon();
//     return x;
// }

PhanSo operator + (PhanSo a, PhanSo b) {
    PhanSo x;
    a.rutGon();
    b.rutGon();
    x.tu = a.tu * b.mau + b.tu * a.mau;
    x.mau = a.mau * b.mau;
    x.rutGon();
    return x;
}
 
int main() {
    PhanSo x, y;
    cin >> x >> y;
    PhanSo tong = x + y;
    cout << tong;

    return 0;
}
*/

class SinhVien {
    private: 
        string mssv, name, lop, ns;
        float gpa;
        static int dem;
    public: 
        friend istream& operator >> (istream& in, SinhVien& a);
        friend ostream& operator << (ostream& out, SinhVien a);
        SinhVien();
        SinhVien(string, string, string, string, float);
        void tangDem();
        string getLop();
        int getDem();
};

int SinhVien::dem = 1;

void SinhVien::tangDem() {
    ++dem;
}

int SinhVien::getDem() {
    return dem;
}

SinhVien::SinhVien() {
    this->mssv = this->name = this->lop = this->ns = "";
    this->gpa = 0;
}

SinhVien::SinhVien(string mssv, string name, string lop, string ns, float gpa) {
    this->mssv = mssv;
    this->name = name;
    this->lop = lop;
    this->ns = ns;
    this->gpa = gpa;
}

istream& operator >> (istream& in, SinhVien& a) {
    a.mssv = "B20DCCN" + string(3 - to_string(a.getDem()).length(), '0') + to_string(a.getDem());
    a.tangDem();
    cout << "Nhap ten: "; getline(in, a.name);
    cout << "Nhap ngay sinh dd/mm/yyyy: "; in >> a.ns;
    cout << "Nhap lop: "; in >> a.lop;
    cout << "Nhap gpa: "; in >> a.gpa; 
    in.ignore();
    cout << "\n";
    return in;
}

ostream& operator << (ostream& out, SinhVien a) {
    out << a.mssv << " " << a.name << " " << a.ns << " " << a.lop << " " << a.gpa << "\n";
    return out;
}

string SinhVien::getLop() {
    return this->lop;
}

bool cmp (SinhVien a, SinhVien b) {
    return a.getLop() < b.getLop();
}

int main() {
    int n;
    cout << "Nhap so luong sinh vien: "; 
    cin >> n;
    map <int, vector<SinhVien>> mp;
    for(int i = 0; i < n; i++) {
        SinhVien tmp; cin >> tmp;
        mp[stoid(tmp.getLop().substr(0, 1))].push_back(tmp); // lay ra khoa cua lua sinh vien do
    }

    for(SinhVien x : mp[s]) {
        cout << x;
    }

    return 0;
}

