#include <iostream>
#include <fstream>
using namespace std;

// struct Node {
//     int data;
//     Node* next;
// };

// void makeNode(Node* &head, int data) {
//     Node* newNode = new Node;
//     newNode->data = data;
//     newNode->next = nullptr;
//     if (head == nullptr) {
//         head = newNode;
//     } else {
//         Node* temp = head;
//         while (temp->next != nullptr) {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//     }
// }

// void inputNumbers(Node* &head, int& n);
// void write2File(Node* head, int n);
void write2File1();
void findX (int x);
// void sortNumbers(Node* head);

// void write2File();
// void readBinFile();

int main() {
    // write2File();
    // readBinFile();

    // Node* head = nullptr;
    int n;
    // inputNumbers(head, n);
    // write2File(head, n);
    write2File1();
    findX(3);

    return 0;
}

// void sortNumbers(Node* head) {
//     ifstream fin;
//     fin.open("Numbers.dat", ios::binary);
//     if (!fin) {
//         cout << "File not found" << "\n";
//         return;
//     }
//     int n;
//     fin.read((char*) &n, 4);
//     int* a = new int[n];
//     for (int i = 0; i < n; i++) {
//         fin.read((char*) &a[i], 4);
//     }
//     fin.close();

// }

// void inputNumbers(Node* &head, int& n) {
//     n = 0;
//     int m;
//     while (std::cin >> m) {
//         if (m == 0) {
//             return;
//         }
//         n++;
//         makeNode(head, m);
//     }
// }

// void write2File(Node* head, int n) {
//     ofstream fout;
//     fout.open("Numbers.dat", ios::binary);
//     if (!fout) {
//         cout << "File not found" << "\n";
//         return;
//     }
//     fout.write((char*) &n, 4);
//     Node* temp = head;
//     while (temp != nullptr) {
//         fout.write((char*) &temp->data, 4);
//         temp = temp->next;
//     }
//     fout.close();
// }


void write2File1() {
    std::ofstream outputFile("Numbers.dat", std::ios::binary);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file Numbers.dat for writing\n";
        return;
    }

    int number;

    while (true) {
        std::cin >> number;

        if (number == 0) return;
        outputFile.write(reinterpret_cast<const char*>(&number), sizeof(number));
    }

    outputFile.close();
}


void findX(int x) {
    ifstream fin;
    fin.open("Numbers.dat", ios::binary);
    if (!fin) {
        cout << "File not found" << "\n";
        return;
    }
    int n;
    fin.read((char*) &n, 4);
    int t;
    for (int i = 0; i < n; i++) {
        fin.read((char*) &t, 4);
        if (t == x) {
            std::cout << "The index of X is: " << i << "\n";
            return;
        }
    }
    fin.close();
}

// void write2File() { 
//     ofstream fout;
//     fout.open("Output.dat", ios::binary);
//     if (!fout) {
//         cout << "File not found" << "\n";
//         return;
//     }
//     int a[] = {1, 2, 3, 4, 5, 6};
//     int n = sizeof(a) / sizeof(a[0]);

     fout.write((char*) &n, 4);
     fout.write((char*) a, n * 4);

//     fout.close();
// }

// void readBinFile() {
//     ifstream fin;
//     fin.open("Output.dat", ios::binary);
//     if (!fin) {
//         cout << "File not found" << "\n";
//         return;
//     }
//     int t;

//     // fin.seekg(20);
//     fin.seekg(-8, ios::end);
//     fin.read((char*) &t, 4);
//     std::cout << "t = " << t << "\n";
//     fin.close();
// }


6 1 2 3 4 5 6
