// in ra so bit co the co voi n phan tu
/*
#include <iostream>
using namespace std;

void print(int n, int* a) {
    for(int i = 0; i < n; i++) cout << a[i];
    cout << "\n";
}

void tryK (int k, int n, int* a) {
    for (int i = 0; i <= 1; i++) {
        a[k] = i;
        if(k == n - 1) print(n, a);
        else tryK(k + 1, n, a);
    }
}

int main() {
    int n, k, *a;
    cout << "Input the number of bits: "; cin >> n;
    a = new int[n];
    tryK(0, n, a);
    delete[] a;
    return 0;
}  
*/

// in ra to hop chap m cua n, k phai chay tu 1, gia tri nho nhat ma a[k] nhan duoc la a[k - 1] + 1, va gia tri lon nhat la n - m + k
/*
#include <iostream>
using namespace std;

void print (int m, int* a) {
    for (int i = 1; i <= m; i++) cout << a[i];
    cout << "\n";
}

void tryK (int k, int n, int m, int* a) {
    for (int i = a[k - 1] + 1; i <= n - m + k; i++) {
        a[k] = i;
        if(k == m) print(m, a);
        else tryK(k + 1, n, m, a);
    }
}

int main() {
    int n, m, k, *a;
    cout << "Input n: "; cin >> n;
    cout << "Input m: "; cin >> m;
    a = new int[m + 1];
    tryK (1, n, m, a);
    delete[] a;
    return 0;
}
*/

// Bai toan hoan vi
/*
#include <iostream>
using namespace std;

void print(int n, int* a) {
    for (int i = 1; i <= n; i++) cout << a[i];
    cout << "\n";
}

void tryK (int n, int* a, int k, bool* used) {
    for (int i = 1; i <= n; i++) {
        if (used[i] == false) {
            a[k] = i;
            used[i] = true;
            if (k == n) print(n, a);
            else tryK(n, a, k + 1, used);
            used[i] = false;
        }
    }
}

int main() {
    int n, *a;
    bool* used;
    cout << "Input n: "; cin >> n;
    a = new int[n + 1];
    used = new bool[n + 1];
    for (int i = 1; i <= n; i++) used[i] = false;
    tryK (n, a, 1, used);
    delete[] a;
    delete[] used;
    return 0;
}
*/

// N queens duong cheo xuoi i + j - 1, duong cheo nguoc i - j + n
/*
#include <iostream>
using namespace std;

void print (int n, int** slots) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << slots[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void tryK (int n, int** slots, int k, bool* d1, bool* d2, bool* c) {
    for (int j = 1; j <= n; j++) {
        if (c[j] == false && d1[k + j - 1] == false && d2[k - j + n] == false) {
            slots[k][j] = 1;
            c[j] = d1[k + j - 1] = d2[k - j + n] = true;
            if (k == n) print(n, slots);
            else tryK(n, slots, k + 1, d1, d2, c);
            slots[k][j] = 0;
            c[j] = d1[k + j - 1] = d2[k - j + n] = false;
        }
    }
}

int main() {
    int n;
    cout << "Input the size of chess board n x n: "; cin >> n;

    int** slots = new int*[n + 1];
    for (int i = 1; i <= n; i++) {
        slots[i] = new int[n + 1];
        for (int j = 1; j <= n; j++) slots[i][j] = 0;
    }

    bool* d1 = new bool[2 * n];
    bool* d2 = new bool[2 * n];
    bool* c = new bool[n + 1];
    for (int i = 1; i <= (2 * n) - 1; i++) d1[i] = d2[i] = false;
    for (int i = 1; i <= n; i++) c[i] = false;

    tryK (n, slots, 1, d1, d2, c);
    delete[] d1;
    delete[] d2;
    delete[] c;
    for (int i = 1; i <= n; i++) delete[] slots[i];
    delete[] slots;
    return 0;
}
*/

// Bai toan sieu thi
/*
#include <iostream>
#include <vector>
using namespace std;

int findMax (vector<int> a) {
    if (a.size() == 1) return a[0];
    int max = a[0];
    for (int i = 1; i < a.size(); i++) {
        if (a[i] > max) max = a[i];
    }
    return max;
}

void tryK (int n, int* items, vector<int> &a, bool* bought, int remain_money, int money, int k) {

    int min_item_cost = *min_element(items, items + n);
    if (remain_money < min_item_cost) {
        a.push_back(money - remain_money);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (bought[i] == false && remain_money >= items[i]) {
            remain_money -= items[i];
            bought[i] = true;
            if (k == n - 1) a.push_back(money - remain_money);
            else tryK (n, items, a, bought, remain_money, money, k + 1);
            // backtrack
            bought[i] = false;
            remain_money = remain_money + items[i];
        }
        else if (k == n - 1) a.push_back(money - remain_money);
    }
}

int main() {
    int n, *items;
    cout << "Input the number of items: "; cin >> n;
    cout << "Input the prices of " << n << " items: ";
    items = new int[n];
    for (int i = 0; i < n; i++) cin >> items[i];
    vector<int> a;
    bool* bought = new bool[n];
    for (int i = 0; i < n; i++) bought[i] = false;
    int money;
    cout << "Input the money you have: "; cin >> money;

    tryK(n, items, a, bought, money, money, 0);
    cout << "The best price you can bought is: " << findMax(a);

    delete[] bought
    return 0;
}
*/

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* makeNode(int x) {
    Node* p = new Node;
    p->data = x;
    p->next = nullptr;
    return p;
}

void addNode(Node* &head, int x) {
    Node* p = makeNode(x);
    if (head == nullptr) head = p;
    else {
        Node* cur = head;
        while (cur->next != nullptr) cur = cur->next;
        cur->next = p;
    }
}

void printList(Node* head) {
    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << "\n";
}

bool checkIncrease (Node* head) {
    if (head == nullptr) return false;
    if (head->next == nullptr || head->next->next == nullptr) return true;
    int x = head->next->data - head->data;
    int y = head->next->next->data - head->next->data;
    if (x == y) {
        head = head->next;
        return checkIncrease(head); 
    }
    else return false;
    return true;
}

void reverseList(Node* &head) {
    if (head == nullptr || head->next == nullptr) return;
    Node* first = head;
    Node* rest = head->next;
    reverseList(rest);
    first->next->next = first;
    first->next = nullptr;
    head = rest;
}

void longestAscendingList(Node* head) {
    if (head == nullptr) return;
    Node* cur = head;
    int max = 1;
    int count = 1;
    Node* start = head;
    Node* maxStart = head; // To keep track of the start of the longest ascending sublist
    while (cur->next != nullptr) {
        if (cur->next->data >= cur->data) {
            count++;
        }
        else {
            if (count > max) {
                max = count;
                start = maxStart; // Update start pointer to the beginning of the current ascending sublist
            }
            count = 1;
            maxStart = cur->next; // Update maxStart to the next node
        }
        cur = cur->next;
    }
    if (count > max) {
        max = count;
        start = maxStart; // Update start pointer to the beginning of the current ascending sublist
    }
    cout << "The longest ascending list is: ";
    while (max > 0 && start != nullptr) {
        cout << start->data << " ";
        start = start->next;
        max--;
    }
}

int main() {
    // Node* head = nullptr;
    // addNode(head, 9);
    // addNode(head, 1);
    // addNode(head, 2);
    // addNode(head, 4);
    // addNode(head, 3);
    // addNode(head, 6);
    // printList(head);

    // if (checkIncrease(head)) cout << "Yes";
    // else cout << "No";
    // reverseList(head);
    // printList(head);
    // longestAscendingList(head);

    // int a[] = {9, 1, 2, 17, 5};
    // int n = sizeof(a) / sizeof(a[0]);
    // int* L = new int[n];
    // for (int i = 0; i <= n; i++) L[i] = 1;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < i; j++) {
    //         if (a[i] > a[j]) {
    //             L[i] = max(L[i], L[j] + 1);
    //         }
    //     }
    // }
    // cout << "The answer is: " << *max_element(L, L + n);

    int a[] = {9, 1, 2, 4, 5};
    int n = sizeof(a) / sizeof(a[0]);

    int* f = new int[n];
    int result = 1;
    for (int i=0; i<n; i++) {
        f[i] = 1;
        for (int j=0; j<i; j++) if (a[j] < a[i]) {
            f[i] = max(f[i], f[j] + 1);
        }
        result = max(result, f[i]);
    }
    cout << "The length of the longest increasing subsequence is: " << result;

    delete[] f;
    return 0;
}
