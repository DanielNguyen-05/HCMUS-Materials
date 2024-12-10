#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Mono {
    float deg;
    float coef;
};

struct Poly {
    short int n;
    Mono* mono;
};

void readFromFile (Poly* &poly, int &size) {
    ifstream fin;
    int count = 0;

    // Find the number of polynominal
    fin.open("POLY.BIN", ios::binary);
    if (!fin.is_open()) {
        cout << "Cannot open the file!";
        return;
    }
    fin.seekg(ios::beg);
    while (!fin.eof()) {
        short int num;
        fin.read((char*)& num, 2);
        fin.seekg(8*num, ios::cur);
        count++;
    }
    size = count;
    fin.close();

    // Star reading the binary file
    poly = new Poly[size];
    ifstream READ;
    READ.open("POLY.BIN", ios::binary);
    if (!READ.is_open()) {
        cout << "Cannot open the file!";
        return;
    }
    for (int i = 0; i < size; i++) {
        short int num;
        READ.read((char*)& num, 2);
        poly[i].n = num;
        poly[i].mono = new Mono[num];
        READ.read((char*) poly[i].mono, 8 * num);
    }
    READ.close();
}

void writeFile (Poly* poly, int size) {
    // Find the largest degree first
    short int max = 0;
    for (int i = 0; i < size; i++) {
        if (poly[i].n > max) max = poly[i].n;
    }
    
    // Write file
    ofstream fout;
    fout.open("POLY_LARGEST.BIN", ios::binary);
    if (!fout.is_open()) {
        cout << "Cannot create the file!";
        return;
    }
    for (int i = 0; i < size; i++) {
        if (poly[i].n == max) {
            short int num = poly[i].n;
            fout.write((char*)&num, 2);
            fout.write((char*) poly[i].mono, 8 * num);
        }
    }
}

int main() {
}