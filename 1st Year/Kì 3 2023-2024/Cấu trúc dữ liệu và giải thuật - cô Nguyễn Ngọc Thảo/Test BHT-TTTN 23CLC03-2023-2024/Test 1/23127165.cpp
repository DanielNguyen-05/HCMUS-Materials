#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Passenger {
    int age;
    string date; 
    float weight;
};

// 1a
void print2D(Passenger** p, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << p[i][j].date << " ";
        }
        cout << "\n";
    }
}

// 1b
Passenger*** readFile(string filename, int& p, int& m, int& n) {
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        cout << "Cannot open file!\n";
        return NULL;
    }
    fin >> p >> m >> n;
    fin.ignore();
    
    Passenger*** P = new Passenger**[p];
    for (int i = 0; i < p; i++) {
        P[i] = new Passenger*[m];
        for (int j = 0; j < m; j++)
            P[i][j] = new Passenger[n];
    }
    
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                string tmp1, tmp2, tmp3;

                getline(fin, tmp1, ' ');
                P[i][j][k].age = stoi(tmp1);

                getline(fin, tmp2, ' ');
                P[i][j][k].date = tmp2;
                
                getline(fin, tmp3);
                P[i][j][k].weight = stof(tmp3);
            }
        }
    }
    fin.close();
    return P;
}

// 1c
void print3D(Passenger*** P, int p, int m, int n) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                cout << P[i][j][k].date << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

// 1d
//Passenger*** findPopular(Passenger*** P, int p, int m, int n, int x, int y, string date) {
//    Passenger*** a = new Passenger**[x];
//    for (int i = 0; i < x; ++i)
//        a[i] = new Passenger[y];
//
//    float minWeight = INT_MAX;
//
//    for (int t = 0; t < p; ++t) {
//        for (int i = 0; i <= m - x; ++i) {
//            for (int j = 0; j <= n - y; ++j) {
//                float curWeight = 0;
//
//                for (int dx = 0; dx < x; ++dx) {
//                    for (int dy = 0; dy < y; ++dy) {
//                        curWeight += P[t][i + dx][j + dy].weight;
//                    }
//                }
//
//                if (curWeight < minWeight) {
//                    minWeight = curWeight;
//
//                    for (int dx = 0; dx < x; ++dx) {
//                        for (int dy = 0; dy < y; ++dy) {
//                            a[dx][dy] = P[t][i + dx][j + dy];
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return a;
//}

struct PaxNode {
    Passenger data;
    PaxNode* next;
};

struct PaxList {
    PaxNode* head;
    PaxNode* tail;
};

void initializeList(PaxList& list) {
    list.head = NULL;
    list.tail = NULL;
}

void addPassenger(PaxList& list, Passenger& P) {
    PaxNode* newNode = new PaxNode;
    newNode->data = P;
    newNode->next = NULL;

    if (list.tail == NULL) list.head = list.tail = newNode;
    else {
        list.tail->next = newNode;
        list.tail = newNode;
    }
}

int dateToInt(string date) {
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 2)) + 2000;
    return year * 10000 + month * 100 + day;
}

void bubbleSortByDate(Passenger passengers[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (dateToInt(passengers[j].date) < dateToInt(passengers[j + 1].date)) {
                Passenger temp = passengers[j];
                passengers[j] = passengers[j + 1];
                passengers[j + 1] = temp;
            }
        }
    }
}

// 2a
PaxList readFile(string filename) {
    PaxList list;
    list.head = NULL;
    list.tail = NULL;

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Cannot open file\n";
        return list;
    }

    int p, m, n;
    fin >> p >> m >> n;
    fin.ignore();

    Passenger a[p * m * n];
    for (int i = 0; i < p * m * n; ++i) {
        fin >> a[i].age >> a[i].date >> a[i].weight;
        fin.ignore();
    }
    fin.close();

    bubbleSortByDate(a, p * m * n);

    for (int i = 0; i < p * m * n; ++i)
        addPassenger(list, a[i]);

    return list;
}

void printList(PaxList P) {
    PaxNode* cur = P.head;
    while (cur != NULL) {
        cout << "Date: " << cur->data.date << ", Weight: " << cur->data.weight << "\n";
        cur = cur->next;
    }
}

// 2b
void remove(PaxList& P, int alpha) {
    PaxNode* cur = P.head;
    PaxNode* prev = NULL;

    if (P.head != NULL && P.head->next != NULL && P.head->data.weight + P.head->next->data.weight > alpha) {
        PaxNode* toDelete = P.head;
        P.head = P.head->next;
        delete toDelete;
    }

    cur = P.head;

    while (cur != NULL && cur->next != NULL) {
        if (cur->data.weight + cur->next->data.weight > alpha) {
            PaxNode* toDelete = cur->next;
            cur->next = toDelete->next;
            if (toDelete == P.tail) P.tail = cur;
            delete toDelete;
        }
        else {
            prev = cur;
            cur = cur->next;
        }
    }
}


