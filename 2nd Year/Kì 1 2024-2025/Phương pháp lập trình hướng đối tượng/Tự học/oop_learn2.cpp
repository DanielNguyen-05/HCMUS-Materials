#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <iomanip>
using namespace std;

// template <class T1, class T2, class T3>
// typedef T1 (* Operation) (T2, T3)

class Person {
    private:
        string name;
        string address;
    public:
        Person(string name, string address) {
            this->name = name; 
            this->address = address;
        }   
        string getName() {
            return this->name;
        }
        string getAddress() {
            return this->address;
        }
        void setName(string name) {
            this->name = name;
        }
        void setAddress(string address) {
            this->address = address;
        }
        void nhap() {
            cout << "Input your name: "; getline(cin, this->name);
            cout << "Input your address: "; getline(cin, this->address);
        }
        void in() {
            cout << this->getName() << " " << this->getAddress() << " "; 
        }
        void xinchao() {
            cout << "Hello!" << "\n";
        }
};

// class Student ke thua tu class Person (con cua cha) - single inheritance
class Student : public Person {
    // nhung phuong thuc bo sung cho class Student
    private:
        float gpa;
    public:
        Student() : Person("", "") {
            this->gpa = 0;
        }
        Student(string name, string address, float gpa) : Person(name, address) {
            this->gpa = gpa;
        }
        float getGPA() {
            return this->gpa;
        }
        void setGPA(float gpa) {
            this->gpa = gpa;
        }
        void nhap() {
            Person::nhap();
            cout << "Input your GPA: "; cin >> this->gpa;
        }
        void in() {
            Person::in(); // function overriding
            cout << fixed << setprecision(2) << this->gpa << "\n";
        }
};

class Employee {
    private:
        double salary;
    public:
        Employee() {
            this->salary = 0;
        }
        Employee(double salary) {
            this->salary = salary;
        }
        double getSalary() {
            return this->salary;
        }
        void setSalary(double salary) {
            this->salary = salary;
        }
        void nhap() {
            cout << "Input your salary: "; cin >> this->salary;
        }
        void in() {
            cout << fixed << setprecision(2) << this->salary << "\n";
        }
};

// class Lecturer ke thua tu class Person va Employee (2 cha) - multiple inheritance
class Lecturer : public Person, public Employee {
    private:
        string faculty;
    public:
        Lecturer() : Person("", ""), Employee(0) {
            this->faculty = "";
        }
        Lecturer(string name, string address, double salary, string faculty) : Person(name, address), Employee(salary) {
            this->faculty = faculty;
        }
        string getFaculty() {
            return this->faculty;
        }
        void setFaculty(string faculty) {
            this->faculty = faculty;
        }
        void nhap() {
            Person::nhap();
            Employee::nhap();
            cout << "Input your faculty: "; getline(cin, this->faculty);
        }
        void in() {
            Person::in();
            Employee::in();
            cout << this->faculty << "\n";
        }
};
 
int main() {
    // Student s;
    // s.Person::nhap(); // it xai, khi nay thi minh chi xai ham nhap cua lop CHA thoi
    // s.Person::in();  // it xai, vi khi nay thi minh chi xai ham in cua lop CHA thoi
    // s.nhap();
    // s.in();

    Lecturer l; 
    l.Person::xinchao(); // xai ham cua lop cha

    return 0;
}  

/* SU KHAC NHAU GIUA CLASS FRIEND & SUPERCLASS
- Class Friend: cho phep lop BAN BE co the truy cap vao thanh vien PRIVATE va PROTECTED.
- Superclass: cho phep lop CON co the truy cap vao thanh vien PUBLIC va PROTECTED cua lop CHA. Vi co the truy cap vao PUBLIC, nen ta co the tai su dung ma (phuong thuc) cua lop cha va mo rong tinh nang (code them phuong thuc rieng cho lop con) dua tren TINH KE THUA

=> Uu diem cua Class Friend: co the truy xuat thanh vien ma khong phai thong qua cac phuong thuc cong khai (public methods)
=> Nhuoc diem cua Superclass la muon truy suat thanh vien cua lop CHA thi phai thong cac phuong thuc cong khai (public methods) nhu getName(),...
*/

/*
A <- B <- C: A la lop cha, B la lop con cua A, C la lop con cua B (Multilevel Inheritance)
A<-B && B->C: A va C la lop cha, B la lop con cua A va C (Multiple Inheritance)
A<-B && A<-C: A la lop cha, B va C la lop con cua A (Hierarchical Inheritance)
*/