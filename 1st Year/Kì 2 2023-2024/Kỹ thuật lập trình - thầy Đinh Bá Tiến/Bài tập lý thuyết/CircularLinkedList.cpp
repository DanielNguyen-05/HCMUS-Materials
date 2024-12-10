#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* pNext;
};

void inputCLL(Node *&pFirst)
{
    Node *cur = pFirst;
    Node *pre = nullptr;
    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            if (cur && pre)
            {
                delete cur;
                pre->pNext = pFirst;
            }
            return;
        }
        if (pFirst == nullptr)
        {
            pFirst = new Node;
            cur = pFirst;
            pre = nullptr;
        }
        cur->data = n;
        cur->pNext = new Node;
        pre = cur;
        cur = cur->pNext;
    }
}

void remove1stX (Node* &pHead, int x)
{
    if (pHead == NULL) return;
    Node* p = pHead;
    while (p->pNext != pHead)
    {
        if (p->pNext->data == x)
        {
            Node* q = p->pNext;
            p->pNext = q->pNext;
            delete q;
            return;
        }
        p = p->pNext;
    }
    if (p->data == x)
    {
        Node* q = pHead;
        while (q->pNext != p)
            q = q->pNext;
        q->pNext = p->pNext;
        delete p;
        pHead = q->pNext;
    }
}

// void remove1stX (Node* &pFirst, int x)
// {
//     if (pFirst == nullptr) return;
//     Node* prev = pFirst;
//     Node* cur = pFirst;
//     if (pFirst->data == x)
//     {
//         while (prev->pNext != pFirst) prev = prev->pNext;
//         Node* tmp = pFirst;
//         prev->pNext = pFirst->pNext;
//         pFirst = pFirst->pNext;
//         delete tmp;
//         return;
//     }
//     while (prev->pNext != cur) prev = prev->pNext;
//     while (cur->pNext != pFirst)
//     {
//         if (cur->data == x)
//         {
//             Node* tmp = cur;
//             prev->pNext = cur->pNext;
//             cur = cur->pNext;
//             delete tmp;
//             return;
//         }
//         cur = cur->pNext;
//         prev = prev->pNext;
//     }
// }

void removeAllXWithKth(Node* &pFirst, int k)
{
    if (pFirst == nullptr) return;
    int i = 1;
    Node* cur = pFirst;
    Node* prev = pFirst;
    while (prev->pNext != cur) prev = prev->pNext;
    while (pFirst != nullptr)
    {
        if (i % k == 0)
        {
            Node* tmp = cur;
            prev->pNext = cur->pNext;
            std::cout << cur->data << " ";
            if (cur == pFirst)
            {
                delete cur;
                cur = prev->pNext;
                pFirst = cur;
            }
            else
            {
                delete cur;
                cur = prev->pNext;
            }
        }
        if (i % k != 0) 
        {
            prev = cur;
            cur = cur->pNext;
        }
        i++;
    }
}

int main()
{
    Node* pFirst = nullptr;
    inputCLL (pFirst);
    removeAllXWithKth (pFirst, 3);
}
