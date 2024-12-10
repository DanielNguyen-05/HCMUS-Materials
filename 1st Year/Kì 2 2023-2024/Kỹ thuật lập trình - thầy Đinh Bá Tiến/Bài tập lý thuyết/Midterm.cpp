#include <iostream>

struct Node
{
    int data;
    Node* pNext;
    Node* pPrev;
};

void printList(Node* node) 
{
    while (node != nullptr) {
        std::cout << node->data << " ";
        node = node->pNext;
    }
    std::cout << std::endl;
}

void append(Node*& head, Node*& tail, int data) 
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->pPrev = nullptr;
    newNode->pNext = nullptr;

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->pNext = newNode;
        newNode->pPrev = tail;
        tail = newNode;
    }
}

void mergeOrderedList(Node*& pOH1, Node* pOH2) // Ly thuyet
{
    if (pOH1 == nullptr) {
        pOH1 = pOH2;
        pOH2 = nullptr;
        return;
    }
    if (pOH2 == nullptr) return;
    
    Node* pOH3 = nullptr;
    Node* pOH3Tail = nullptr;
    
    while (pOH1 != nullptr && pOH2 != nullptr) {
        if (pOH1->data <= pOH2->data) {
            if (pOH3 == nullptr) {
                pOH3 = pOH1;
                pOH3Tail = pOH1;
            } else {
                pOH3Tail->pNext = pOH1;
                pOH3Tail = pOH3Tail->pNext;
            }
            pOH1 = pOH1->pNext;
        } else {
            if (pOH3 == nullptr) {
                pOH3 = pOH2;
                pOH3Tail = pOH2;
            } else {
                pOH3Tail->pNext = pOH2;
                pOH3Tail = pOH3Tail->pNext;
            }
            pOH2 = pOH2->pNext;
        }
    }
    
    if (pOH1 == nullptr) {
        pOH3Tail->pNext = pOH2;
    } else {
        pOH3Tail->pNext = pOH1;
    }
    pOH1 = pOH3;
    pOH2 = nullptr;
}

Node* getBiggest(Node* pHead) // Ex: 2a APCS22-23
{
    if (pHead == nullptr) return nullptr;
    int biggest_num = INT_MIN;
    Node* cur = pHead;
    while (cur != nullptr) {
        if (cur->data >= biggest_num) biggest_num = cur->data;
        cur = cur->pNext;
    }
    Node* tmp = pHead;
    while (tmp != nullptr) {
        if (tmp->data == biggest_num) return tmp;
        tmp = tmp->pNext;
    }
    return nullptr;
}

void removeMid(Node* &pHead) // Ex: 2b APCS22-23
{
    if (pHead == nullptr) return;

    Node* cur = pHead;
    if  (cur->pNext == nullptr) {
        Node* tmp = cur;
        cur = cur->pNext;
        delete tmp;
        pHead = nullptr;
        return;
    }
// 1 2 3 4
    int i = 1;
    while (cur != nullptr) {
        cur = cur->pNext;
        i++;
    }

    int k = 1;
    Node* cur2 = pHead;
    while (cur2 != nullptr) {
        if (k == i/2 - 1) {
            Node* tmp = cur2->pNext;
            cur2->pNext = cur2->pNext->pNext;
            delete tmp;
            return;
        }
        cur2 = cur2->pNext;
        k++;
    }
} // hàm đúng, sửa lại chỗ i = 1 và k = 1

void swapEvery2AdjNodes(Node* &pHead)  // Ex: 2c APCS22-23 
{
    if (pHead == nullptr || pHead->pNext == nullptr) return;

    Node* prev = nullptr;
    Node* cur = pHead;
    Node* tmp = nullptr;
    Node* next = nullptr; // 1 2 3 4
    while (cur != nullptr && cur->pNext != nullptr)
    {
        tmp = cur->pNext;
        next = cur->pNext->pNext;
        tmp->pNext = cur;
        if (prev != nullptr) prev->pNext = tmp;
        else pHead = tmp; 

        cur->pNext = next;
        prev = cur;
        cur = next;
    }
}

void removeDups(Node* &pDLLHead) // Ex: 3a APCS22-23
{
    if (pDLLHead == nullptr || pDLLHead->pNext == nullptr) return;
    Node* cur = pDLLHead;
    while (cur != nullptr)
    {
        Node* tmp = cur->pNext;
        while (tmp != nullptr) {
            if (tmp->data == cur->data) {
                Node* tmp2 = tmp;
                tmp = tmp->pNext;
                if (tmp != nullptr) tmp->pPrev = tmp2->pPrev;
                tmp2->pPrev->pNext = tmp;
                delete tmp2;
            }
            else tmp = tmp->pNext;
        }
        cur = cur->pNext;
    }
} // hàm đúng

void reverseDoublyLinkedList(Node*& pHead) // Ex: 3b APCS22-23
{
    if (pHead == nullptr || pHead->pNext == nullptr) return;

    Node* cur = pHead;
    Node* prev = nullptr;
    Node* next = nullptr;

    while (cur != nullptr) {
        next = cur->pNext;
        cur->pNext = prev;
        if (prev != nullptr) prev->pPrev = cur;
        prev = cur;
        cur = next;
        if (cur == nullptr) prev->pPrev = nullptr;
    }
    pHead = prev;
} // hàm đúng

void partition(Node* &pHead, int x) // Ex: 3c APCS 22-23
{
    if (pHead == nullptr) return;

    Node* pTail = pHead;
    while (pTail->pNext != nullptr) pTail = pTail->pNext; 

    if (pHead == pTail) return;

    Node* L = pHead, *R = pTail;
    while (L != R && L != R->pNext) {
        if (L->data <= x) L = L->pNext;
        else if (R->data > x) R = R->pPrev;
        else {
            std::swap(L->data, R->data);
            L = L->pNext;
            R = R->pPrev;
        }
    }
}  // hàm đúng

int main() 
{
    Node* pDLLHead = nullptr;
    Node* tail = nullptr;
    int values[] = {18, 42, 97, 34, 63, 26};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; ++i) {
        append(pDLLHead, tail, values[i]);
    }

    reverseDoublyLinkedList(pDLLHead);
    printList(pDLLHead);
    return 0;
}

#include <iostream>

struct Node
{
    int data;
    Node* pNext;
};

struct Node
{
    int data;
    Node* pNext;
    Node* pPrev;
};

void append(Node*& head, Node*& tail, int data) 
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->pPrev = nullptr;
    newNode->pNext = nullptr;

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->pNext = newNode;
        newNode->pPrev = tail;
        tail = newNode;
    }
}

void printList2(Node* node) 
{
    while (node->pNext != nullptr) {
        node = node->pNext;
    }
    while (node != nullptr) {
        std::cout << node->data << " ";
        node = node->pPrev;
    }
    std::cout << std::endl;
}

void printList(Node* node) 
{
    while (node != nullptr) {
        std::cout << node->data << " ";
        node = node->pNext;
    }
    std::cout << std::endl;
}

void swapSmallest2First (Node* pHead) // Ex:2a APCS 23-24
{
    int smallest_num = INT_MAX;
    Node* cur = pHead;
    while (cur != nullptr) {
        if (cur->data < smallest_num) smallest_num = cur->data;
        cur = cur->pNext;
    }
    Node* tmp = pHead;
    while (tmp != nullptr) {
        if (tmp->data == smallest_num) {
            std::swap(pHead->data, tmp->data);
            return;
        }
        tmp = tmp->pNext;
    }
}

void printGreaterNode (Node* pHead) // Ex:2b APCS 23-24
{
    Node* cur = pHead;
    while (cur != nullptr)
    {
        Node* tmp = cur->pNext;
        if (tmp == nullptr) std::cout << "null";
        while (tmp != nullptr)
        {
            if (tmp->data > cur->data) {
                std::cout << tmp->data << " ";
                break;
            }
            if (tmp->pNext == nullptr && tmp->data <= cur->data) std::cout << "null" << " ";
            tmp = tmp->pNext;
        }
        cur = cur->pNext;
    }
}

void oddLeftEvenRight (Node* pHead) // Ex:2c APCS 23-24
{
    Node* cur = pHead;
    while (cur != nullptr)
    {
        Node* tmp = cur->pNext;
        while (tmp != nullptr)
        {
            if (cur->data % 2 == 0 && tmp->data % 2 != 0) {
                std::swap(cur->data, tmp->data);
                break;
            }
            tmp = tmp->pNext;
        }
        cur = cur->pNext;
    }
}

void reverse(Node* &pHead)
{
    if (pHead == nullptr) return;
    if (pHead->pNext == nullptr) return;
    Node* cur = pHead;
    Node* prev = nullptr;
    Node* next = nullptr;
    while (cur != nullptr)
    {
        next = cur->pNext;
        cur->pNext = prev;
        cur = next;
        prev = cur;
    }
    pHead = prev;
}

bool isPalindrome (Node* pHead) // Ex:2d APCS 23-24
{
    if (pHead == nullptr) return;
    if (pHead->pNext == nullptr) return true;
    Node* cur = pHead;
    int i = 0;
    while (cur != nullptr) {
        cur = cur->pNext;
        i++;
    }
    Node* slow = pHead;
    if (i % 2 != 0) return false;
    int k = 1;
    while (i != k / 2) {
        slow = slow->pNext;
        k++;
    }
    reverse(slow->pNext);
    slow = slow->pNext;
    while (pHead != nullptr && slow != nullptr) {
        if (pHead->data != slow->data) return false;
        pHead = pHead->pNext;
        slow = slow->pNext;
    }
    return true;
}

void removeBiggest (Node* &pDLLHead) // Ex: 3a APCS 23-24
{
    if (pDLLHead == nullptr) return;
    if (pDLLHead->pNext == nullptr) {
        pDLLHead = nullptr;
        return;
    }
    int biggest_num = INT_MIN;
    Node* cur = pDLLHead;
    while (cur != nullptr) {
        if (cur->data > biggest_num) biggest_num = cur->data;
        cur = cur->pNext;
    }
    label:
        Node* cur2 = pDLLHead;
        while (cur2 != nullptr) {
            if (cur2->data == biggest_num && cur2 == pDLLHead) {
                pDLLHead = cur2->pNext;
                pDLLHead->pPrev = nullptr;
                delete cur2;
                break;
            }
            if (cur2->data == biggest_num && cur2->pNext != nullptr) {
                cur2->pPrev->pNext = cur2->pNext;;
                cur2->pNext->pPrev = cur2->pPrev;
                delete cur2;
                break;
            }
            if (cur2->data == biggest_num && cur2->pNext == nullptr ) {
                cur2->pPrev->pNext = nullptr;
                delete cur2;
                break;
            }
            cur2 = cur2->pNext;
        }
    Node* check = pDLLHead;
    while (check != nullptr) {
        if (check->data == biggest_num) goto label;
        check = check->pNext;
    }
}

Node* elementKthFromEnd(Node* pDLLHead, int k) // Ex: 3b APCS 23-24
{
    if (pDLLHead == nullptr) return nullptr;
    Node* pTail = pDLLHead;
    while (pTail->pNext != nullptr) pTail = pTail->pNext;
    int i = 1;
    while (pTail != nullptr) {
        if (i == k) return pTail;
        pTail = pTail->pPrev;
        i++;
    }
    return nullptr;
}

void rotateK (Node* &pDLLHead, int k) // Ex: 3c APCS 23-24
{
    if (pDLLHead == nullptr || pDLLHead->pNext == nullptr) return;
    int i = 0;
    label: 
        Node* pTail = pDLLHead;
        while (pTail->pNext != nullptr) pTail = pTail->pNext;
        pTail->pPrev->pNext = nullptr;
        pDLLHead->pPrev = pTail;
        pTail->pNext = pDLLHead;
        pTail->pPrev = nullptr;
        pDLLHead = pTail;
        i++;
    if (i != k) goto label;
}

void reverseDoublyList (Node* &pDLLHead)
{
    if (pDLLHead == nullptr || pDLLHead->pNext == nullptr) return;
    Node* cur = pDLLHead;
    Node* prev = nullptr;
    Node* next = nullptr;
    while (cur != nullptr) {
        next = cur->pNext;
        cur->pNext = prev;
        if (prev != nullptr) prev->pPrev = cur;
        prev = cur;
        cur = next;
        if (cur == nullptr) prev->pPrev = nullptr;
    }
    pDLLHead = prev;
}

int main() 
{
    // Node* pHead = nullptr;
    // int values[] = {18, 7, 33, 99, 10, 78};
    // int n = sizeof(values) / sizeof(values[0]);
    // for (int i = 0; i < n; ++i) {
    //     Node* newNode = new Node;
    //     newNode->data = values[i];
    //     newNode->pNext = nullptr;
    //     if (pHead == nullptr) {
    //         pHead = newNode;
    //     } else {
    //         Node* cur = pHead;
    //         while (cur->pNext != nullptr) {
    //             cur = cur->pNext;
    //         }
    //         cur->pNext = newNode;
    //     }
    // }
    Node* pDLLHead = nullptr;
    Node* tail = nullptr;
    int values[] = {25, 72, 86, 19, 64, 9};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; ++i) {
        append(pDLLHead, tail, values[i]);
    }
    printList(pDLLHead);

    reverseDoublyList(pDLLHead);

    printList(pDLLHead);
    std::cout << "\n";
    printList2(pDLLHead);
    return 0;
}
