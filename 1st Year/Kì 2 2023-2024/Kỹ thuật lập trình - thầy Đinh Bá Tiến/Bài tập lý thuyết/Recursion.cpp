// #include <iostream>

// struct Node
// {
//     int data;
//     Node* pNext;
// };

void tryFillSlotK(int k, int* slots, int n, bool* notUsed);
void display(int* slots, int n);

void tryFillSlotK (int k, int* slots, int n, bool* notUsed) {
    if (k == n) display(slots, n);
    else {
        for (int i = 0; i < n; i++) {
            if (notUsed[i]) { // i was not used before
                slots[k] = i;  // put it to slots[k]
                notUsed[i] = false; // used i

                //  try the next slot
                tryFillSlotK(k + 1, slots, n, notUsed);
                notUsed[i] = true;  // undo to try i + 1
            }
        }
    }
}

void display(int* slots, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << slots[i] + 1 << " ";
    }
    std::cout << std::endl;
}

// int main() {
//     int n;
//     std::cout << "Please input a positive integer: ";
//     std::cin >> n;

//     int* slots = new int[n];

//     bool* notUsed = new bool[n];
//     for (int i = 0; i < n; i++)
//         notUsed[i] = true;

//     tryFillSlotK(0, slots, n, notUsed);

//     delete[] slots;
//     delete[] notUsed;
//     return 0;
// }


// #include <iostream>

// struct Node {
//     int data;
//     Node* next;
// };

// void insert(Node*& pHead, int value) {
//     Node* newNode = new Node;
//     newNode->data = value;
//     newNode->next = pHead;
//     pHead = newNode;
// }

// void remove(Node* &pHead) {
//     Node* tmp = pHead;
//     pHead = pHead->next;
//     delete tmp;
// }

// void printpHead(Node* pHead) {
//     std::cout << "{ ";
//     while (pHead != nullptr) {
//         std::cout << pHead->data << " ";
//         pHead = pHead->next;
//     }
//     std::cout << "}" << std::endl;
// }

// void generatepHeads(int start, int end, Node* pHead, int index) {
//     if (index == end) {
//         printpHead(pHead);
//         return;
//     }

//     insert(pHead, index + start);
//     generatepHeads(start, end, pHead, index + 1);
//     remove(pHead);

//     generatepHeads(start, end, pHead, index + 1);
// }

// int main() {
//     Node* pHead = nullptr;
//     generatepHeads(1, 3, pHead, 0);
//     return 0;
// }

// #include <iostream>

// struct Node {
//     int data;
//     Node* next;
// };

// void insert(Node*& subset, int value) {
//     Node* newNode = new Node;
//     newNode->data = value;
//     newNode->next = subset;
//     subset = newNode;
// }

// void remove(Node*& subset) {
//     Node* oldNode = subset;
//     subset = subset->next;
//     delete oldNode;
// }

// void printSubset(Node* subset) {
//     std::cout << "{ ";
//     while (subset != nullptr) {
//         std::cout << subset->data << " ";
//         subset = subset->next;
//     }
//     std::cout << "}" << std::endl;
// }

// void generateSubsets(const int nums[], int n, Node* subset, int index) {
//     if (index == n) {
//         printSubset(subset);
//         return;
//     }

//     insert(subset, nums[index]);
//     generateSubsets(nums, n, subset, index + 1);
//     remove(subset);

//     generateSubsets(nums, n, subset, index + 1);
// }

// int main() {
//     const int nums[] = {1, 2, 3};
//     Node* subset = nullptr;
//     generateSubsets(nums, 3, subset, 0);
//     return 0;
// }


#include <iostream>

// Way 1:
int shopping(int n, int* a, int money) {
    
    if (money == 0 || n == 0) return 0;

    if (a[n - 1] > money) return shopping(n - 1, a, money);

    return std::max(a[n - 1] + shopping(n - 1, a, money - a[n - 1]), shopping(n - 1, a, money));
}

// Way 2:
void tryItemK (int k, int* a, int n, int xR, bool* curCombi, int& bestXR, bool* bestCombi)
{
    if (xR >= a[k]) {
        curCombi[k] = true;
        xR -= a[k];

        if (xR < bestXR) {
            bestXR = xR;
            for (int i = 0; i < n; i++) {
                bestCombi[i] = curCombi[i];
            }
        }

        tryItemK (k + 1, a, n, xR, curCombi, bestXR, bestCombi);
        xR += a[k];
    }
}

int main() {
    int n;
    std::cout << "How many items: ";
    std::cin >> n;

    int* a = new int[n];
    std::cout << "Please input the prices of each item: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int money;
    std::cout << "How much money you have: ";
    std::cin >> money;

    int result = shopping(n, a, money);
    std::cout << "The best price you can buy is: " << result << "\n";

    delete[] a;

    return 0;
}

#include <iostream>
using namespace std;

void backTrack(int step, int n, int k, int* a, bool* chosen, int& maxSum, bool* ans)
{
    if (step == n)
    {
        int sumCash = 0;
        for (int i = 0; i < n; i++) if (chosen[i]) sumCash += a[i];
        if (sumCash > k || sumCash < maxSum) return;

        maxSum = sumCash;
        for (int i = 0; i < n; i++) ans[i] = chosen[i];

        return;
    }

    for (int i = 0; i < 2; i++)
    {
        chosen[step] = i;
        backTrack(step + 1, n, k, a, chosen, maxSum, ans);
    }
}

int main()
{
    int n, k;
    int* a = new int[20];
    bool* chosen = new bool[20], * ans = new bool[20];

    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];

    int maxSum = 0;
    backTrack(0, n, k, a, chosen, maxSum, ans);

    cout << maxSum << '\n';
    for (int i = 0; i < n; i++) if (ans[i]) cout << a[i] << " ";

    return 0;
}