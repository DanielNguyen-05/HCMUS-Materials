#include <iostream>

struct Node
{
    int data;
    Node* pNext;
};

void inputBookStore (Node* &pStore)
{
    int n;
    Node* cur = pStore;
    while (std::cin >> n)
    {
        if (n == 0) return;
        if (cur == nullptr)
        {
            pStore = new Node;
            cur = pStore;
        }
        else
        {
            cur->pNext = new Node;
            cur = cur->pNext;
        }
        cur->data = n;
        cur->pNext = nullptr;
    }
}

void displayBookStore (Node* pStore)
{
    std::cout << "Your final list is: ";
    Node* cur = pStore;
    while (cur != nullptr)
    {
        std::cout << cur->data << " ";
        cur = cur->pNext;
    }
}

void deleteBookStore (Node* pStore)
{
    Node* cur = pStore;
    Node* tmp;
    while (cur != nullptr)
    {
        tmp = cur;
        cur = cur->pNext;
        delete tmp;
    }
}

void insertAfter(Node* &pStore, int k, int x) // insert a new node [x] AFTER the node with data = [k]
{
    Node* cur = pStore;
    if(cur == nullptr) return;
    while(cur->data != k && cur != nullptr) 
    {
        cur = cur->pNext;
    }
    Node* tmp =  cur->pNext;
    cur->pNext = new Node;
    cur =  cur->pNext;
    cur->data = x;
    cur->pNext = tmp;
}

void insertBefore(Node* &pStore, int k, int x) // insert a new node [x] BEFORE the node with data = [k]
{
    Node* tmp = new Node;
    if (pStore->data == k)
    {
        tmp->data = x;
        tmp->pNext = pStore;
        pStore = tmp;
    }
    else
    {
        Node* pre = pStore;
        while (pre->pNext != nullptr)
        {
            if (pre->pNext->data == k)
            {
                tmp->data = x;
                tmp->pNext = pre->pNext;
                pre->pNext = tmp;
                return;
            }
            pre = pre->pNext;
        }
    }
}

void deleteFirstX (Node* &pStore, int x) 
{
    Node* cur = pStore;
    Node* tmp;  
    if (pStore == nullptr) return;
    if (cur->data == x)
    {
        tmp = pStore;
        pStore = cur->pNext;
        delete tmp;
        return;
    }
    while (cur->pNext != nullptr && cur->pNext->data != x) 
    {
        cur = cur->pNext;
    }
    if (cur->pNext != nullptr) 
    {
        tmp = cur->pNext;
        cur->pNext = cur->pNext->pNext;
        delete tmp;
        return;
    }
}

void deleteAllX (Node* &pStore, int x)
{
    if (pStore == nullptr) return;
    Node* cur = pStore;
    label:
        if (pStore->data == x) 
        {  
            Node* temp; 
            temp = pStore;
            pStore = pStore->pNext;
            delete temp;
        }
        while (cur->pNext != nullptr &&  cur->pNext->data != x)
        {
            cur = cur->pNext;
        }
        if (cur->pNext != nullptr) 
        {
            Node* temp;
            temp = cur->pNext;
            cur->pNext = cur->pNext->pNext;
            delete temp;
        }
    Node* tmp = pStore;
    while (tmp != nullptr)
    {
        if (tmp->data == x) goto label;
        tmp = tmp->pNext;
    }
    delete tmp;
}

void reverseList(Node* &pStore)
{
    Node* pre = nullptr;
    Node* cur = pStore;
    if (pStore == nullptr) return;
    while (cur != nullptr)
    {
        Node* nextNode = cur->pNext;
        cur->pNext = pre;
        pre = cur;
        cur = nextNode;
    }
    pStore = pre;
}

Node* findX (Node* pOH, int x)
{
    Node* i = pOH;
    while (i != nullptr && i->data < x) i = i->pNext;
    if (i != nullptr && i->data == x) return i;
    return nullptr;
}

void mergeOrderedList(Node*& pOH1, Node* pOH2) 
{
    if (pOH1 == nullptr) 
    {
        pOH1 = pOH2;
        pOH2 = nullptr;
        return;
    }
    if (pOH2 == nullptr) return;
    
    Node* pOH3 = nullptr;
    Node* pOH3Tail = nullptr;
    
    while (pOH1 != nullptr && pOH2 != nullptr) {
        if (pOH1->data <= pOH2->data) {
            if (pOH3 == nullptr) 
            {
                pOH3 = pOH1;
                pOH3Tail = pOH1;
            } 
            else 
            {
                pOH3Tail->pNext = pOH1;
                pOH3Tail = pOH3Tail->pNext;
            }
            pOH1 = pOH1->pNext;
        } 
        else 
        {
            if (pOH3 == nullptr)
            {
                pOH3 = pOH2;
                pOH3Tail = pOH2;
            } 
            else 
            {
                pOH3Tail->pNext = pOH2;
                pOH3Tail = pOH3Tail->pNext;
            }
            pOH2 = pOH2->pNext;
        }
    }
    
    if (pOH1 == nullptr) 
    {
        pOH3Tail->pNext = pOH2;
    } 
    else 
    {
        pOH3Tail->pNext = pOH1;
    }
    pOH1 = pOH3;
    pOH2 = nullptr;
}

int main()
{
    int x, k;
    Node* pStore = nullptr;
    inputBookStore (pStore);
    // insertAfter (pStore, k, x);
    // insertBefore (pStore, k, x);
    // deleteFirstX (pStore, 23);
    // deleteAllX (pStore, x);
    // reverseList (pStore);
    Node* cur = findX (pStore, 3);
    std::cout << cur->data << " " << cur->pNext->data;
    // displayBookStore (pStore);
    deleteBookStore (pStore);
    return 0;
}

// #include <iostream>
// using namespace std;

// struct Node
// {
//     int data;
//     Node* pNext;
// };

// struct List
// {
//     Node* pHead;
//     Node* pTail;
// };

// void init(List &l)
// {
//     l.pHead = nullptr;
//     l.pTail = nullptr;
// }

// Node* makeNode (int n)
// {
//     Node* pNode = new Node;
//     pNode->data = n;
//     pNode->pNext = nullptr;
//     return pNode;
// }

// void inputList (List &l)
// {
//     int n;
//     Node* pNode = new Node;
//     std::cout << "Input list: ";
//     while (std::cin >> n)
//     {
//         if (n == 0) return;
//         pNode = makeNode(n);
//         if (l.pHead == nullptr) l.pHead = l.pTail = pNode;
//         else
//         {
//             l.pTail->pNext = pNode;
//             l.pTail = pNode;
//         }
//     }
//     delete pNode;
// }

// void printList (List l)
// {
//     for (Node* i = l.pHead; i != nullptr; i = i->pNext) 
//     {   
//         std::cout << i->data << " ";
//     }
//     std::cout << "\n" << "ppStore: " << l.pHead->data << "\n" << "pTail: " << l.pTail->data;
// }


// void insertXAfterK (List &l, int k, int x)
// {
//     for (Node* i = l.pHead; i != nullptr; i = i->pNext)
//     {
//         if (i == nullptr) return;
//         if (i->data == k)
//         {
//             Node* pNew = makeNode(x);
//             pNew->pNext = i->pNext;
//             i->pNext = pNew;
//             if (i == l.pTail && i->data == k) l.pTail = pNew;
//         }
//     }
// }

// void insertXBeforeK (List &l, int k, int x)
// {
//     for (Node* i = l.pHead; i != nullptr; i = i->pNext)
//     {
//         if (i == nullptr) return;
//         if (i == l.pHead && i->data == k)
//         {
//             Node* pNew = makeNode(x);
//             pNew->pNext = i;
//             l.pHead = pNew;
//         }
//         if (i->pNext->data == k)
//         {
//             Node* pNew1 = makeNode(x);
//             pNew1->pNext = i->pNext;
//             i->pNext = pNew1;
//             i = i->pNext;
//         }
//         if (i->pNext == l.pTail) return;
//     }
// } 

// void deleteFirstK (List& l, int k)
// {
//     for (Node *i = l.pHead; i->pNext != NULL; i = i->pNext)
//     {
//         if (i == nullptr) return;
//         if (i->data == k && i == l.pHead)
//         {
//             Node* tmp = l.pHead;
//             l.pHead = i->pNext;
//             delete tmp;
//             return;
//         }
//         if (i->pNext->data == k && i->pNext != l.pTail)
//         {
//             Node* tmp = i->pNext;
//             i->pNext = i->pNext->pNext;
//             delete tmp;
//             return;
//         }
//         if (i->pNext->data == k && i->pNext == l.pTail)
//         {
//             Node* tmp = l.pTail;
//             i->pNext = i->pNext->pNext;
//             l.pTail = i;
//             delete tmp;
//             return;
//         }
//     }
// }

// void deleteAllK (List &l, int k)
// {
//     label:
//         for (Node *i = l.pHead; i->pNext != NULL; i = i->pNext)
//         {
//             if (i == nullptr) break;
//             if (i->data == k && i == l.pHead)
//             {
//                 Node* tmp = l.pHead;
//                 l.pHead = i->pNext;
//                 delete tmp;
//                 break;
//             }
//             if (i->pNext->data == k && i->pNext != l.pTail)
//             {
//                 Node* tmp = i->pNext;
//                 i->pNext = i->pNext->pNext;
//                 delete tmp;
//                 break;
//             }
//             if (i->pNext->data == k && i->pNext == l.pTail)
//             {
//                 Node* tmp = l.pTail;
//                 i->pNext = i->pNext->pNext;
//                 l.pTail = i;
//                 delete tmp;
//                 break;
//             }
//         }
//     for (Node* tmp = l.pHead; tmp != nullptr; tmp = tmp->pNext)
//     {
//         if (tmp->data == k) goto label;
//     }
// }

// int main()
// {
//     int x, k;
//     List l;
//     init (l);
//     inputList (l);
//     insertXAfterK (l, k, x);
//     insertXBeforeK (l, k, x);
//     deleteFirstK (l, k);
//     deleteAllK (l, k);
//     printList (l);
//     return 0;
// }

