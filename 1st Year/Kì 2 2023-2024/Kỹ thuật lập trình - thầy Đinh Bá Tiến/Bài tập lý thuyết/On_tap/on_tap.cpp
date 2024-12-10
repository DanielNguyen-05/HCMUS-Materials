#include <iostream>
#include <fstream>

struct Node {
    int data;
    Node* pNext;
};

void printList(Node* pHead) {
    while (pHead) {
        std::cout << pHead->data << " ";
        pHead = pHead->pNext;
    }
    std::cout << std::endl;
}

void deallocate (Node* &pHead) {
    while (pHead != nullptr) {
        Node* cur = pHead;
        pHead = pHead->pNext;
        delete cur;
    }
}

void makeAndAddNode (Node* &pHead, int x) {
    Node* new_node = new Node;
    new_node->data = x;
    new_node->pNext = nullptr;

    if (pHead == nullptr) {
        pHead = new_node;
        return;
    }
    else {
        Node* tmp = pHead;
        while (tmp->pNext != nullptr) tmp = tmp->pNext;
        tmp->pNext = new_node;
        return;
    }
}  

bool isPrime (int x) {
    if (x < 2) return false;
    else {
        for (int i = 2; i <= x / 2; i++) {
            if (x % i == 0) return false;
        }
        return true;
    }
}

void getList (Node* &pHead) {
    std::ifstream fin;
    fin.open("input.txt");
    if (!fin.is_open()) {
        std::cout << "Cannot open the input file!";
        return;
    }
    while (!fin.eof()) {
        int x;
        fin >> x;
        makeAndAddNode(pHead, x);
    }
    fin.close();
}

int countPrime (Node* pHead) {
    if (pHead == nullptr) return 0;
    int dem = 0;
    Node* cur = pHead;
    while(cur) {
        if (isPrime(cur->data)) dem++;
        cur = cur->pNext;
    }
    return dem;
}

void removeLastPrime (Node* &pHead, int k, int dem, Node* cur) {
    if (cur == nullptr) return;
    if (dem == 1 && isPrime(pHead->data)) {
        Node* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
        return;
    }
    else if (k == dem && isPrime(cur->pNext->data)) {
        Node* tmp2 = cur->pNext;
        cur->pNext = tmp2->pNext;
        delete tmp2;
        return;
    }
    else if (k != dem && isPrime(cur->pNext->data)) removeLastPrime(pHead, k + 1, dem, cur->pNext);
    else removeLastPrime(pHead, k, dem, cur->pNext);
}

int main() {
    Node* pHead = nullptr;
    getList(pHead);
    if (pHead == nullptr) std::cout << "The input file is null";
    int dem = countPrime(pHead);
    if (dem == 0) printList(pHead);
    else {
        Node* cur = pHead;
        removeLastPrime(pHead, 0, dem, cur);
    }
    printList(pHead);

    return 0;
}
