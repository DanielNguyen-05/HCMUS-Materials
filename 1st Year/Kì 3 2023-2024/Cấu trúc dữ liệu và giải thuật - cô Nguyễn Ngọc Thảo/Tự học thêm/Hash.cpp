#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

struct Company {
    string name;
    string profit_tax;
    string address;
};

Company createCompany();
vector<Company> initData(string filename);
long long HashString(string companyName);
long long searchFirstEmpty(Company* table, int size, long long index);
long long searchFor(Company *table, int size, long long index, Company entry);
void InsertTable(Company* &table, int &size, Company entry);
Company* reHash(Company* table, int oldSize);
void DeleteTable(Company* table, int size, Company entry);
Company* CreateHashTable(vector<Company> list_company, int &size);
void printExists(Company* table, int size);

Company createCompany() {
    Company c;
    c.name = "NULL";
    c.profit_tax = c.address = "";
    return c;
}

vector<Company> initData(string filename) {
    fstream f(filename, fstream::in);
    vector<Company> l;
    if(!f.is_open()) {
        cout << "Cannot open file\n";
        return l;
    }

    f.ignore(1024, '\n');
    while(f.peek() != EOF) {
        Company com = createCompany();
        getline(f, com.name, '|');
        getline(f, com.profit_tax, '|');
        getline(f, com.address, '\n');
        l.push_back(com);
    }
    return l;
}

long long HashString(string companyName) {
    string s;
    if(companyName.size() > 20) s = companyName.substr(companyName.size() - 20, 20);
    else s = companyName;
    long long hash = 0;
    for(int i = 0; i < s.size() - 1; i++) {
        hash += (int) s[i] * 31;
    }
    hash = hash % (long long) (pow(10, 9) + 1);
    return hash;
}

long long searchFirstEmpty(Company* table, int size, long long index) {
    bool circle = false;
    long long j = index;
    if(j >= size) {
        index = 0;
        j = 0;
    }
    while(table[j].name != "NULL" && table[j].name != "TOMB") {
        if(j == index && circle) return -1;
        j++;
        if(j == size) {
            circle = true;
            j = 0;
        }
    }
    return j;
}

long long searchFor(Company *table, int size, long long index, Company entry) {
    bool circle = false;
    long long j = index;
    if(j >= size) {
        index = 0;
        j = 0;
    }
    while(table[j].name != entry.name) {
        if(table[j].name == "NULL") return -1;
        if(j == index && circle) return -1;
        j++;
        if(j == size) {
            circle = true;
            j = 0;
        }
    }
    return j;
}

void InsertTable(Company* &table, int &size, Company entry) {
    long long hashVal = HashString(entry.name);
    long long index = searchFirstEmpty(table, size, hashVal);
    if(index == -1)
        table = reHash(table, size);
    table[index] = entry;
}

Company* reHash(Company* table, int oldSize) {
    int newSize = oldSize * 2;
    Company* newTable = new Company[newSize];
    for(int i = 0; i < oldSize; i++) {
        if(table[i].name == "NULL" || table[i].name == "TOMB") continue;
        InsertTable(newTable, newSize, table[i]);
    }
    return newTable;
}

void DeleteTable(Company* table, int size, Company entry) {
    long long hashVal = HashString(entry.name);
    long long index = searchFor(table, size, hashVal, entry);
    if(index == -1) return; //not exists
    else {
        Company temp = createCompany();
        temp.name = "TOMB";
        table[index] = temp;
    }
}

Company* CreateHashTable(vector<Company> list_company, int &size) {
    Company* table = new Company[size];
    Company temp = createCompany();
    for(int i = 0; i < size; i++)
        table[i] = temp;
    for(auto i : list_company)
        InsertTable(table, size, i);
    InsertTable(table, size, list_company[0]);
    return table;
}

void printExists(Company* table, int size) {
    for(int i = 0; i < size; i++) {
        if(table[i].name == "NULL" || table[i].name == "TOMB") continue;
        cout << i + 1 << ": " << table[i].name << endl;
    }
}

int main() {
    int size = 2000;
    Company* table = CreateHashTable(initData("MST.txt"), size);
    printExists(table, size);
}