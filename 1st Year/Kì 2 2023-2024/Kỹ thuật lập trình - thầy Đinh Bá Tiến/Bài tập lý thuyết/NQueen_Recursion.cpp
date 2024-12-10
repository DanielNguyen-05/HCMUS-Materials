#include <iostream>

void inputSize(int& n) {
    std::cout << "Input the size of chessboard: ";
    std::cin >> n;
}

void display(int* slots, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (slots[i] == j) std::cout << " 1 ";
            else std::cout << " 0 ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
} 

void tryK (int k, int* slots, int n, bool* notUsedCol, bool* notUsedD1, bool* notUsedD2) {
    if (k == n) display(slots, n);
    else for (int i = 0; i < n; i++) {
        if (notUsedCol[i] && notUsedD1[k + i] && notUsedD2[k - i + n - 1]) {
            slots[k] = i;
            notUsedCol[i] = false;
            notUsedD1[k + i] = false;
            notUsedD2[k - i + n - 1] = false;

            tryK (k + 1, slots, n, notUsedCol, notUsedD1, notUsedD2);

            notUsedCol[i] = true;
            notUsedD1[k + i] = true;
            notUsedD2[k - i + n - 1] = true;
        }
    }
}

int main() {
    int n;
    inputSize(n);
    int* slots = new int[n];

    bool* notUsedCol = new bool[n];
    bool* notUsedD1 = new bool[2 * n - 1];
    bool* notUsedD2 = new bool[2 * n - 1];

    for (int i = 0; i < n; i++) {
        notUsedCol[i] = true;
    }

    for (int i = 0; i < 2 * n - 1; i++) {
        notUsedD1[i] = notUsedD2[i] = true;
    }
    
    tryK(0, slots, n, notUsedCol, notUsedD1, notUsedD2);

    delete[] slots;
    delete[] notUsedCol;
    delete[] notUsedD1;
    delete[] notUsedD2;

    return 0;
}