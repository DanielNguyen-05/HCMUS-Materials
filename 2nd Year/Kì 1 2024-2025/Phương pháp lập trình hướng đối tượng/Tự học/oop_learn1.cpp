#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class GiaoVien; // foward declaration
class SinhVien; // foward declaration => de viet class nao truoc cung duoc
class SoPhuc;

class GiaoVien {
    private:
        string fal; // này goi la thuoc tinh
    public:
        void updatePoint(SinhVien&); // nay goi la phuong thuc
};

// thuoc tinh va phuong thuc duoc goi chung la: thanh vien

class SinhVien {
    friend class GiaoVien;  // Friend class => QUAN TRONG   
    private:
        string name;
        int id, age;
        string stt;
        double gpa;
        static int dem;  // dung chung cho tat ca 

    public:
        SinhVien();  // constructor khong doi so
        SinhVien(string, int, int, double);  // constructor co doi so

        // phuong thuc
        void DiHoc();
        void XinChao();
        void nhap();
        void in();

        double getGPA(); // getter
        string getName();
        // int getID();
        // int getAGE():

        string setName(string); // setter
        // double setGPA(double); 
        int setID(int);
        // int setAGE(int);

        int getDem();
        void tangDem();

        friend void inThongTin(SinhVien); // Friend function
        friend void chuanHoa(SinhVien&);

        // operator overloading
        friend istream& operator >> (istream& in, SinhVien& a); // cin : istream
        friend ostream& operator << (ostream& out, SinhVien a); // cout : ostream
        bool operator < (SinhVien a);
        friend bool operator > (SinhVien a, SinhVien b);

        ~SinhVien(); // destructor

};

class SoPhuc {
    private:
        int thuc, ao;
    public:
        friend istream& operator >> (istream& in, SoPhuc& a);
        friend ostream& operator << (ostream& out, SoPhuc a);
        /*
        SoPhuc operator + (SoPhuc another); // tinh tong cua so phuc HIEN TAI voi so phuc duoc truyen vao (do ham nay la member cua class SoPhuc luon => dung this->thuc || this->ao duoc)
        SoPhuc operator - (SoPhuc another); 

        => 2 ham nay va 2 ham duoi tuong duong nhau, khac nhau o cach khai bao cua ham
        */
        friend SoPhuc operator + (SoPhuc a, SoPhuc b); // tinh tong cua 2 so phuc duoc truyen vao (do ham nay duoc khai bao la FRIEND cua class SoPhuc)
        friend SoPhuc operator - (SoPhuc a, SoPhuc b);
}; 

istream& operator >> (istream& in, SoPhuc& a) {
    cout << "Nhap phan thuc: "; in >> a.thuc;
    cout << "Nhap phan ao: "; in >> a.ao;
    return in;
}

ostream& operator << (ostream& out, SoPhuc a) {
    out << a.thuc << "+" << a.ao << ".i" << "\n";
    return out; 
}

/*
SoPhuc SoPhuc::operator + (SoPhuc another) {
    SoPhuc tong;
    tong.thuc = this->thuc + another.thuc;
    tong.ao = this->ao + another.ao;
    return tong;
}

SoPhuc SoPhuc::operator - (SoPhuc another) {
    SoPhuc hieu;
    hieu.thuc = this->thuc - another.thuc;
    hieu.ao = this->ao - another.ao;
    return hieu;
}

2 ham nay va 2 ham duoi la tuong duong nhau
*/

SoPhuc operator + (SoPhuc a, SoPhuc b) {
    SoPhuc tong;
    tong.thuc = a.thuc + b.thuc;
    tong.ao = a.ao + b.ao;
    return tong;
}

SoPhuc operator - (SoPhuc a, SoPhuc b) {
    SoPhuc hieu;
    hieu.thuc = a.thuc - b.thuc;
    hieu.ao = a.ao - b.ao;
    return hieu;
}

istream& operator >> (istream& in, SinhVien& a) {
    cout << "Nhap id: "; in >> a.id; 
    in.ignore(); 
    cout << "Nhap ten: "; getline(in, a.name);
    cout << "Nhap tuoi: "; in >> a.age;
    cout << "Nhap diem: "; in >> a.gpa;

    return in;
}

ostream& operator << (ostream& out, SinhVien a) {
    out << a.name << " " << a.id << " " << a.age << " " << a.gpa << "\n";
    return out;
}

bool SinhVien::operator < (SinhVien a) {
    return this->gpa < a.gpa;
}

bool operator > (SinhVien a, SinhVien b) {
    return a.gpa > b.gpa;
}

SinhVien::SinhVien() {
    cout << "Ham duoc khoi tao! \n";
    name = stt = "";
    id = age = gpa = 0;  
    // this->name = "";
    // this->id = this->age = this->gpa = 0;
}

SinhVien::SinhVien(string ten, int mssv, int tuoi, double point) {
    name = ten;
    id = mssv;
    age = tuoi;
    gpa = point;
}

/*
// Neu ten cua cac doi so trung voi ten cua cac thuoc tinh cua lop
SinhVien::SinhVien(string name, int id, int age, double gpa) {
    this->name = name;
    this->id = id
    this->age = age;
    this->gpa = gpa;
}
*/

SinhVien::~SinhVien() {
    cout << "Ham da bi huy tai day! \n";
}

void SinhVien::DiHoc() {
    cout << "Sinh vien di hoc! \n";
}

void SinhVien::XinChao() {
    cout << "Xin chao sinh vien! \n";
}

void SinhVien::nhap() {
    cout << "Nhap mssv: "; cin >> this->id;
    cin.ignore();
    cout << "Nhap ten: "; getline(cin, this->name);
    cout << "Nhap tuoi: "; cin >> this->age;    
    cout << "Nhap diem: "; cin >> this->gpa;
    cout << "\n";

    this->stt = "SV" + string(2- to_string(dem).length(), '0') + to_string(dem);
    dem++;
}

void SinhVien::in() {
    cout << stt << " " << name << " " << id << " " << age << " " << gpa << " ";
    // cout << this->name << " " << this->id << " " << this->age << " " << this->gpa << "\n";
}

double SinhVien::getGPA() {
    return this->gpa;
}

bool cmp(SinhVien a, SinhVien b) {
    return a.getGPA() > b.getGPA();
}

string SinhVien::setName(string ten) {
    return this->name = ten;
}

string SinhVien::getName() {
    return this->name;
}


int SinhVien::dem = 1;  // implementation

void SinhVien::tangDem() {
    ++dem;
}

int SinhVien::getDem() {
    return dem;
}

int SinhVien::setID(int mssv) {
    return this->id = mssv;
} 

void inThongTin(SinhVien a) {
    cout << a.stt << " " << a.name << " " << a.id << " " << a.age << " " << a.gpa << "\n";
}

void chuanHoa(SinhVien& a) {
    string res = "";
    stringstream ss(a.name);
    string token;
    while (ss >> token) {
        res += toupper(token[0]);
        for(int i = 1; i < token.length(); i++) {
            res += tolower(token[i]);
        }
        res += " ";
    }
    res.erase(res.length() - 1);
    a.name = res;
}

void GiaoVien::updatePoint(SinhVien& a) {
    double new_point;
    cout << "Nhap so diem ban muon doi thanh: "; cin >> new_point;
    a.gpa = new_point;
}

int main() {
    // SinhVien x;
    // x.nhap();
    // x.in();
    // x.DiHoc();
    // x.XinChao();

    // SinhVien a[3];
    // for(int i = 0; i < 3; i++) {
    //     a[i].nhap();
    // }

    // sort(a, a + 3, cmp);

    // for(int i = 0; i < 3; i++) {
    //     a[i].in();
    // }
    
    // SinhVien x;
    // x.setName("Nguyen Hai Dang");
    // string k = x.getName();
    // cout << k;

    // SinhVien x;
    // x.tangDem();
    // x.tangDem();
    // SinhVien y;
    // cout << y.getDem() << "\n";

    // SinhVien a[3];
    // for(int i = 0; i < 3; i++) {
    //     a[i].nhap();
    //     // a[i].setID(a[i].getDem());
    //     // a[i].tangDem();
    // }

    // for(int i = 0; i < 3; i++) {
    //     // a[i].in();
    //     inThongTin(a[i]);
    // } 

    // SinhVien a;
    // a.nhap();
    // chuanHoa(a);
    // GiaoVien x;
    // x.updatePoint(a);
    // inThongTin(a);

    // SinhVien x, y;
    // cin >> x >> y;
    // if (x < y) cout << "YES";
    // else cout << "NO";

    SoPhuc x, y;
    cin >> x >> y;
    SoPhuc tong = x + y;
    SoPhuc hieu = x - y;

    cout << tong;
    cout << hieu;

    return 0;
}