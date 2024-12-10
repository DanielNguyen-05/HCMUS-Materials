#include <iostream>

struct Node
{
    int data;
    Node* pNext;
    Node* pPrev;
};

struct List
{
    Node* pHead;
    Node* pTail;
};

void init(List &l)
{
    l.pHead = nullptr;
    l.pTail = nullptr;
}

Node* makeNode (int n)
{
    Node* pNode = new Node;
    pNode->data = n;
    pNode->pNext = nullptr;
    pNode->pPrev = nullptr;
    return pNode;
}

void inputList (List &l)
{
    int n;
    std::cout << "Input list: ";
    while (std::cin >> n)
    {
        if (n == 0) return;
        Node* pNode = makeNode(n);
        if (l.pHead == nullptr) l.pHead = l.pTail = pNode;
        else
        {
            l.pTail->pNext = pNode;
            pNode->pPrev = l.pTail;
            l.pTail = pNode;
        }
    }
}

void printList (List l)
{
    std::cout << "Output list: ";
    for (Node* i = l.pHead; i != nullptr; i = i->pNext) 
    {   
        std::cout << i->data << " ";
    }
    std::cout << "\n" << "pHead: " << l.pHead->data << "\n" << "pTail: " << l.pTail->data;
}

void insertXAfterK(List &l, int k, int x) 
{
    if (l.pHead == nullptr) return; 
    Node* i = l.pHead;
    while (i != nullptr) 
    {
        if (i->data == k) 
        {
            Node* pNew = makeNode(x);
            pNew->pNext = i->pNext;
            pNew->pPrev = i;
            if (i->pNext != nullptr) i->pNext->pPrev = pNew;
            i->pNext = pNew;
            if (i == l.pTail) l.pTail = pNew;
        }
        i = i->pNext;
    }
}

void insertXBeforeK (List &l, int k, int x)
{
    if (l.pHead == nullptr) return;
    Node* i = l.pHead;
    while (i != nullptr)
    {
        if (i->data == k)
        {
            Node* pNew = makeNode(x);
            if (i == l.pHead)
            {
                pNew->pNext = i;
                i->pPrev = pNew;
                l.pHead = pNew;
            }
            else
            {
                i->pPrev->pNext = pNew;
                pNew->pPrev = i->pPrev;
                pNew->pNext = i;
                i->pPrev = pNew;
            }
            if (i == l.pTail) return;
        }
        i = i->pNext;
    }
}

void deleteFirstK (List &l, int k)
{
    Node* i = l.pHead;
    if (l.pHead == nullptr) return;
    while (i != nullptr)
    {  
        if (i->data == k)
        {
            Node* tmp = i;
            if (i == l.pHead)
            {  
                if (i->pNext == nullptr) delete tmp;
                else
                {
                    i = i->pNext;
                    i->pPrev = nullptr;
                    l.pHead = i;
                    delete tmp;
                }
            }
            if (i != l.pTail)
            {
                i->pPrev->pNext = i->pNext;
                i->pNext->pPrev = i->pPrev;
                delete tmp;
            }
            if (i == l.pTail)
            {
                i->pPrev->pNext = nullptr;
                l.pTail = i->pPrev;
                delete tmp;
                return;
            }
        }
        i = i->pNext;
    }
}

// void deleteFirstK(List &l, int k) {
//     if (l.pHead == nullptr) return; // handle case when the list is empty

//     Node* i = l.pHead;
//     while (i != nullptr) 
//     {
//         if (i->data == k) 
//         {
//             if (i == l.pHead) 
//             { 
//                 l.pHead = i->pNext;
//                 if (l.pHead != nullptr) l.pHead->pPrev = nullptr;
//                 else l.pTail = nullptr;
//             } 
//             else if (i == l.pTail) 
//             { 
//                 l.pTail = i->pPrev;
//                 l.pTail->pNext = nullptr;
//             } 
//             else 
//             { 
//                 i->pPrev->pNext = i->pNext;
//                 i->pNext->pPrev = i->pPrev;
//             }
//             delete i;
//             return;
//         }
//         i = i->pNext;
//     }
// }

void deleteAllK(List &l, int k) {
    Node* i = l.pHead;
    if (l.pHead == nullptr) return;
    while (i != nullptr) 
    {
        if (i->data == k) 
        {
            Node* tmp = i;
            if (i == l.pHead) 
            {
                l.pHead = i->pNext;
                if (l.pHead != nullptr) l.pHead->pPrev = nullptr;
                if (i == l.pTail) l.pTail = nullptr;
            } 
            else if (i == l.pTail) 
            {
                l.pTail = i->pPrev;
                l.pTail->pNext = nullptr;
            } 
            else 
            {
                i->pPrev->pNext = i->pNext;
                i->pNext->pPrev = i->pPrev;
            }
            i = i->pNext;
            delete tmp;
        } 
        else i = i->pNext;
    }
}




int main()
{
    int x, k;
    List (l);
    init (l);
    inputList(l);
    insertXAfterK(l, k, x);
    insertXBeforeK(l, k, x);
    deleteFirstK (l, k);
    deleteAllK (l, k);
    printList(l);
}