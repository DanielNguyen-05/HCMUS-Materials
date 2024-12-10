#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct DataStruct {
    int key1;
    string key2;
    int key3;
    bool key4;
};

struct Node {
    DataStruct key;
    Node* left;
    Node* right;
};

Node* createNode(DataStruct key);
int compare(DataStruct d1, DataStruct d2);
DataStruct createData(string key2);
int max(int a, int b);
int Height(Node* root);
void rotateLeft(Node*& root);
void rotateRight(Node*& root);
void Insert(Node*& root, DataStruct key);
void del(Node*& predecessor, Node*& q);
void searchDel(Node*& root, DataStruct key);
Node* AVLTree(vector<DataStruct>);
void preOrder(Node* root);
void inOrder(Node* root);
void postOrder(Node* root);
void BFSprint(Node* root);

Node* createNode(DataStruct key) {
    Node* n = new Node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

DataStruct createData(string key2) {
    DataStruct k;
    k.key2 = key2;
    k.key1 = 0;
    k.key3 = 0;
    k.key4 = false;
    return k;
}

int compare(DataStruct d1, DataStruct d2) {
    int cmp = d1.key2.compare(d2.key2);
    return cmp;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int Height(Node* root) {
    if (root == nullptr) return 0;
    return max(Height(root->left), Height(root->right)) + 1;
}

void rotateLeft(Node*& root) {
    Node* y = root->right;
    Node* T2 = y->left;

    y->left = root;
    root->right = T2;

    root = y;
}

void rotateRight(Node*& root) {
    Node* y = root->left;
    Node* T2 = y->right;

    y->right = root;
    root->left = T2;

    root = y;
}

void Insert(Node*& root, DataStruct key) {
    if (root == nullptr) root = createNode(key);
    else {
        int cmp = compare(key, root->key);
        if (cmp < 0) Insert(root->left, key);
        else if (cmp > 0) Insert(root->right, key);
        else return;
    }

    int bal = Height(root->right) - Height(root->left);
    if (bal >= -1 && bal <= 1) return; //nothing todo;
    if (root->left != nullptr) {
        int cmpToLeft = compare(key, root->left->key);
        if (bal < -1 && cmpToLeft < 0) rotateRight(root);
        if (bal < -1 && cmpToLeft > 0) {
            rotateLeft(root->left);
            rotateRight(root);
        }
    }
    if (root->right != nullptr) {
        int cmpToRight = compare(key, root->right->key);
        if (bal > 1 && cmpToRight > 0) rotateLeft(root);
        if (bal > 1 && cmpToRight < 0) {
            rotateRight(root->right);
            rotateLeft(root);
        }
    }
}

void del(Node*& predecessor, Node*& q) {
    if (predecessor->right) predecessor->right;
    else {
        q->key = predecessor->key;
        q = predecessor;
        predecessor = predecessor->left;
    }
}

void searchDel(Node*& root, DataStruct key) {
    int cmp = compare(key, root->key);
    if (cmp < 0) searchDel(root->left, key);
    else if (cmp > 0) searchDel(root->right, key);
    else {
        Node* q = root;
        if (q->left == nullptr) root = root->right;
        else if (q->right == nullptr) root = root->left;
        else del(root->left, q);
        delete q;
    }

    if (root == nullptr) return; //empty tree
    int bal = Height(root->right) - Height(root->left);
    if (bal >= -1 && bal <= 1) return; //nothing todo;
    int cmpToLeft = compare(key, root->left->key);
    int cmpToRight = compare(key, root->right->key);
    if (bal < -1 && cmpToLeft < 0) rotateRight(root);
    if (bal < -1 && cmpToLeft > 0) {
        rotateLeft(root->left);
        rotateRight(root);
    }
    if (bal > 1 && cmpToRight > 0) rotateLeft(root);
    if (bal > 1 && cmpToRight < 0) {
        rotateRight(root->right);
        rotateLeft(root);
    }
}

Node* AVLTree(vector<DataStruct> a) {
    Node* root = nullptr;
    for (int i = 0; i < a.size(); i++) {
        Insert(root, a[i]);
    }
    return root;
}

void preOrder(Node* root) {
    if (root == nullptr) return;
    cout << root->key.key2 << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    preOrder(root->left);
    cout << root->key.key2 << " ";
    preOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    preOrder(root->left);
    preOrder(root->right);
    cout << root->key.key2 << " ";
}

void BFSprint(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;

    q.push(root);
    while (!q.empty()) {
        Node* n = q.front();
        cout << n->key.key2 << " ";
        q.pop();
        if (n->left != nullptr) q.push(n->left);
        if (n->right != nullptr) q.push(n->right);
    }
}

int main() {
    vector <DataStruct> a;
    a.push_back(createData("a"));
    a.push_back(createData("b"));
    a.push_back(createData("c"));
    a.push_back(createData("d"));
    a.push_back(createData("e"));
    Node* r = AVLTree(a);
    BFSprint(r);
}