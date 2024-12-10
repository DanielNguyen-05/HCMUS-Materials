#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* reverseList(Node* head) {
    Node* cur = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    while (cur != nullptr) {
       next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        if (prev != nullptr) head = prev;
    }
    return head;
}

void printList(Node* head) {
    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << "\n";
}

int main() {
    Node* head = new Node;
    Node* cur = head;
    for (int i = 1; i <= 5; i++) {
        cur->data = i;
        cur->next = new Node;
        cur = cur->next;
    }
    cur->next = nullptr;
    printList(head);
    head = reverseList(head);
    printList(head);
    return 0;
}
//     node4->data = 7;
//     node4->next = node5;
//     node5->data = 2;
//     node5->next = nullptr;