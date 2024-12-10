// Bai 2
/*
#include <iostream>
using namespace std;

int** createPascalTriangle(int N) {
    int** matrix = new int*[N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[i + 1];
    }
    matrix[0][0] = 1;
    for (int i = 1; i < N; i++) {
        matrix[i][0] = 1; 
        matrix[i][i] = 1;
        for (int j = 1; j < i; j++) {
            matrix[i][j] = matrix[i - 1][j - 1] + matrix[i - 1][j];
        }
    }
    return matrix;
}

int main() {
    int N;
    cout << "Input the rows: "; cin >> N;

    int** matrix = createPascalTriangle(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    
    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
*/

// Bai 3
/*
#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* GetKthNodeFromTail (Node* head, int k) {
    int dem = 0;
    Node* cur = head;
    while (cur != nullptr) {
        dem++;
        cur = cur->next;    
    }
    if (head == nullptr || k > dem || k < 0) return nullptr;
    int k2 = dem - k + 1;
    cur = head;
    int i = 0;
    while (cur != nullptr) {
        i++;
        if (i == k2) return cur;
        cur = cur->next;
    }
    return nullptr;
}

int main() {
    Node* head = nullptr;
    int k = 6;

    Node* node1 = new Node();
    Node* node2 = new Node();
    Node* node3 = new Node();
    Node* node4 = new Node();
    Node* node5 = new Node();
    node1->data = 5;
    head = node1;
    node1->next = node2;
    node2->data = 3;
    node2->next = node3;
    node3->data = 6;
    node3->next = node4;
    node4->data = 4;
    node4->next = node5;
    node5->data = 2;
    node5->next = nullptr;

    Node* kthNode = GetKthNodeFromTail(head, k);
    cout << kthNode->data;
}
*/

// Bai 4
#include <iostream>
#include <vector>
using namespace std;

/*

3 6 15 16 21
1 1 2  2  1

Giải thuật:
Sử dụng quay lui để thử tất cả các trường hợp:
- Đi qua từng tờ tiền, thử cho tờ tiền đó cho từng thợ mỏ
- Khi có 1 phân hoạch thì kiểm tra xem chênh lệch có nhỏ hơn chênh lệch nhỏ nhất hiện tại hay không
- Nếu nhỏ hơn thì lưu lại phân hoạch
- Sau cùng ta sẽ có phân hoạch tối ưu

*/

int* bestPartition;
int bestDiff = INT_MAX;

void backtrack(int a[], int n, int k, int partition[], int *bestPartition, int &bestDiff,  int coinIndex)
{
    if (coinIndex >= n) {
        int* sum = new int[k];
        for (int i = 0; i < k; i++) {
            sum[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            sum[partition[i]] += a[i];
        }

        int minSum = sum[0];
        int maxSum = sum[0];
        for (int i = 1; i < k; i++) {
            minSum = min(minSum, sum[i]);
            maxSum = max(maxSum, sum[i]);
        }

        if (maxSum - minSum < bestDiff) {
            bestDiff = maxSum - minSum;
            for (int i = 0; i < n; i++) {
                bestPartition[i] = partition[i] + 1;
            }
        }

        delete[] sum;

        return;
    }

    for (int i = 0; i < k; i++) {
        partition[coinIndex] = i;
        backtrack(a, n, k, partition, bestPartition, bestDiff, coinIndex + 1);
    }
}

int* getPartition(int a[], int n, int k) {
    int* partition = new int[n];
    int *bestPartition = new int[n];
    int bestDiff = INT_MAX; 

    backtrack(a, n, k, partition, bestPartition, bestDiff, 0);

    delete[] partition;

    return bestPartition;
}

int main()
{
    vector<int> a;
    a.push_back(3);
    a.push_back(6);
    a.push_back(15);
    a.push_back(16);
    a.push_back(21);
    int* partition = getPartition(&a[0], a.size(), 2);

    for (int i = 0; i < a.size(); i++) {
        cout << partition[i] << " ";
    }

    delete[] partition;

    return 0;
}
