// #include <iostream>
// #include <fstream>
// #include <cstring>
// #include <string>
// using namespace std;

// struct Products {
//     string id;
//     string name;
//     string num_of_items;
//     string unit_price;
// };

// struct Node {
//     Products products;
//     Node* pNext;
// };

// void loadList (Node* &pHead) {
//     ifstream fin;
//     fin.open("product.txt");
//     if (!fin.is_open()) {
//         cout << "Cannot open the input file!";
//         return;
//     }
//     Node* cur = nullptr;
//     int result = 5;
//     while (result) {
//         Node* new_node = new Node;
//         string temp;
//         getline(fin, temp, ',');
//         new_node->products.id = stoi(temp);
//         getline(fin, new_node->products.name, ',');
//         getline(fin, temp, ',');
//         new_node->products.num_of_items = stoi(temp);
//         getline(fin, temp, '\n');
//         new_node->products.unit_price = stof(temp);
//         new_node->pNext = nullptr;

//         if (pHead == nullptr) {
//             pHead = new_node;
//             cur = pHead;
//         } else {
//             cur->pNext = new_node;
//             cur = cur->pNext;
//         }
//         result--;
//     }
//     fin.close();
// }

// void printList (Node* pHead) {
//     while (pHead != nullptr) {
//         cout << pHead->products.id << "\t" << pHead->products.name << "\t"
//              << pHead->products.num_of_items << "\t" << pHead->products.unit_price << "\n";
//     }
// }

// int main() {
//     Node* pHead = nullptr;
//     loadList (pHead);
//     printList (pHead);
//     return 0;
// }