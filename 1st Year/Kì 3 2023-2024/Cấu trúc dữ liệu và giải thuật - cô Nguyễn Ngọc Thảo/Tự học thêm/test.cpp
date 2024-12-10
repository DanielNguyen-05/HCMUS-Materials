#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <math.h>

using namespace std;

struct people {
    string name;
    float height;
    float weight;
};

people initPeople() {
    people p;
    p.name = "NULL";
    p.height = p.weight = 0;
    return p;
}

vector<people> readData(string filename) {
    fstream f(filename, fstream::in);
    vector<people> ls;
    if(!f.is_open()) {
        cout << "Cannot ope file\n";
        return ls;
    }

    while(f.peek() != EOF) {
        people p = initPeople();
        getline(f, p.name, '-');
        string temp = "";
        getline(f, temp, '-');
        p.height = stoi(temp);
        getline(f, temp, '\n');
        p.weight = stoi(temp);
        ls.push_back(p);
    }
    return ls;
}

unsigned long long HashPeople(people p) {
    unsigned long long hash = 0;
    string str = p.name;
    int ascii[128];
    memset(ascii, 0, sizeof(int) * 128);
    for(int i = 0; i < str.size(); i++) {
        hash += str[i] * pow(23, (int) sqrt(p.height) - i + ascii[(int) str[i]]);
        ascii[(int) str[i]]++;
    }
    hash %= (unsigned long long) (pow(10, 9) + 1);
    cout << "hash: " << hash << endl;
    return hash;
}

unsigned long long searchFirstEmpty(people* table, unsigned long long start) {
    bool circle = false;
    unsigned long long j = start;
    if(j >= 2000) {
        j = 0;
        start = 0;
    }
    while(table[j].name != "NULL" && table[j].name != "TOMB") {
        if(j == start && circle) return -1;
        j++;
        if(j == 2000) {
            j = 0;
            circle = true;
        }
    }
    return j;
}

void Insert(people* table, people entry) {
    unsigned long long hashValue = HashPeople(entry);
    unsigned long long index = searchFirstEmpty(table, hashValue);
    if(index == -1); //rehash
    table[index] = entry;
}

int eq(people p1, people p2) {
    return (p1.name == p2.name) && (p1.height == p2.height) && (p1.weight == p2.height);
}

unsigned long long searchFor(people* table, unsigned long long start, people p) {
    bool circle = false;
    unsigned long long j = start;
    if(j >= 2000) {
        j = 0;
        start = 0;
    }
    while(eq(table[j], p)) {
        if(table[j].name == "NULL") return -1;
        if(j == start && circle) return -1;
        j++;
        if(j == 2000) {
            circle = true;
            j = 0;
        }
    }
    return j;
}

void Remove(people*& table, people p) {
    unsigned long long hashVal = HashPeople(p);
    unsigned long long index = searchFor(table, hashVal, p);
    if(index == -1) return; //not exists
    else {
        people temp = initPeople();
        temp.name = "TOMB";
        table[index] = temp;
    }
}

people* createHashTable(vector<people> list_people) {
    people* table = new people[2000];
    people temp = initPeople();
    for(int i = 0; i < 2000; i++) {
        table[i] = temp;
    }
    for(auto i : list_people) {
        Insert(table, i);
    }
    return table;
}

void printPeople(people* table) {
    for(int i = 0; i < 2000; i++) {
        if(table[i].name == "NULL" || table[i].name == "TOMB") continue;
        cout << i + 1 << " " << table[i].name << endl;
    }
}

int main() {
    people* tb = createHashTable(readData("people.txt"));
    printPeople(tb);
    return 0;
}