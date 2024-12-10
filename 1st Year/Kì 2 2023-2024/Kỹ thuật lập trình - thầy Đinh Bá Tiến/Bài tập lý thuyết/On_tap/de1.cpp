// #include <iostream>

// void init2D_Matrix (char** &A, int& n, int& m);
// void init3D_Matrix (char*** &B, int& n, int& m, int& k);

// void print2D_Matrix (char** A, int n, int m);
// void print3D_Matrix (char*** B, int n, int m, int k);

// char*** findFunnySubMatrix (char** A, int n, int m, int p, int q, int k);

// int main() {
//     int n, m, k;
//     char** A;
//     char*** B;

//     init2D_Matrix (A, n, m);


// }

// void init2D_Matrix (char** &A, int& n, int& m) {
//     std::cout << "Input n, m: ";
//     std::cin >> n >> m;

//     std::cout << "Input 2D matrix: " << "\n";
//     A = new char*[n];
//     for (int i = 0; i < n; i++) {
//         A[i] = new char[m];
//         for (int j = 0; j < m; j++) {
//             std::cin >> A[i][j];
//         }
//     } // A E I D Y E O I A I U O Z Y U E
// }

// void init3D_Matrix (char*** &B, int& n, int& m, int& k) {
//     std::cout << "Input n, m, k: ";
//     std::cin >> n >> m >> k;

//     B = new char**[k];
//     for (int i = 0; i < k; i++) {
//         B[i] = new char*[n];
//         for (int j = 0; j < n; j++) {
//             B[i][j] = new char[m];
//         }
//     }
// }

// void print2D_Matrix (char** A, int n, int m) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             std::cout << A[i][j] << " ";
//         }
//         std::cout << "\n";
//     }
// }

// void print3D_Matrix (char*** B, int n, int m, int k) {

// }

// char*** findFunnySubMatrix (char** A, int n, int m, int p, int q, int k) {
//     char*** B = new char**[k];

// }

#include <iostream>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct List {
    NODE* p_head;
    NODE* p_tail;
};

List createList (int A[], int n) {
    List l;
    l.p_head = nullptr;
    l.p_tail = nullptr;
    for (int i = 0; i < n; i++) {
        NODE* new_node = new NODE;
        new_node->key = A[i];
        new_node->p_next = nullptr;
        if (l.p_head == nullptr) {
            l.p_head = new_node;
            l.p_tail = l.p_head;
        }
        else {
            l.p_tail->p_next = new_node;
            l.p_tail = l.p_tail->p_next;
        }
    }
    return l;
}

List printList (List l) {
    NODE* cur = l.p_head;
    while (cur != nullptr) {
        std::cout << cur->key << " ";
        cur = cur->p_next;
    }
    return l;
}

void getTheStartingIndex (List l) {
    NODE* cur = l.p_head;
    int i = 0;
    while (cur != nullptr) {
        i++;
        cur = cur->p_next;
    }

    NODE* prev = nullptr;
    NODE* cur1 = l.p_head;
    int k = 0, dem1 = 0, dem2 = 0;
    while (cur1->p_next != nullptr) {
        if (cur1->p_next->key >= cur1->key) {
            dem1++;
        }
        else {

        }
    }


}

// List splitLongestAscending (List &l) {

// }

int main() {
    List l;
    int n;
    std::cin >> n;
    int A[n];
    for (int i = 0; i < n; i++){
        std::cin >> A[i];
    }
    l = createList (A, n);
    l = printList (l);


}