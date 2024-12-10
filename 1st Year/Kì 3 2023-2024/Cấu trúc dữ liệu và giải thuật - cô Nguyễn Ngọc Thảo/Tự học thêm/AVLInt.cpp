#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* createNode(int key);
int max(int a, int b);
int Height(Node* root);
void rotateLeft(Node*& root);
void rotateRight(Node*& root);
void Insert(Node*& root, int key);
void del(Node*& predecessor, Node*& q);
void searchDel(Node*& root, int key);
Node* AVLTree(int a[], int n);
void preOrder(Node* root);
void inOrder(Node* root);
void postOrder(Node* root);
void BFSprint(Node* root);
void printLevel(Node* root, int level);
void printTreeBFS(Node *root);

Node* createNode(int key) {
    Node* n = new Node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;
    return n;
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

void Insert(Node*& root, int key) {
    if (root == nullptr) root = createNode(key);
    else {
        if (key < root->key) Insert(root->left, key);
        else if (key > root->key) Insert(root->right, key);
        else return;
    }

    int bal = Height(root->right) - Height(root->left);
    if (bal >= -1 && bal <= 1) return; //nothing todo;
    if (root->left != nullptr) {
        if (bal < -1 && key < root->left->key) rotateRight(root);
        if (bal < -1 && key > root->left->key) {
            rotateLeft(root->left);
            rotateRight(root);
        }
    }
    if (root->right != nullptr) {
        if (bal > 1 && key > root->right->key) rotateLeft(root);
        if (bal > 1 && key < root->right->key) {
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

void searchDel(Node*& root, int key) {
    if (root->key > key) searchDel(root->left, key);
    else if (root->key < key) searchDel(root->right, key);
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
    if (bal < -1 && key < root->left->key) rotateRight(root);
    if (bal < -1 && key > root->left->key) {
        rotateLeft(root->left);
        rotateRight(root);
    }
    if (bal > 1 && key > root->right->key) rotateLeft(root);
    if (bal > 1 && key < root->right->key) {
        rotateRight(root->right);
        rotateLeft(root);
    }
}

Node* AVLTree(int a[], int n) {
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        Insert(root, a[i]);
    }
    return root;
}

void preOrder(Node* root) {
    if (root == nullptr) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    preOrder(root->left);
    cout << root->key << " ";
    preOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    preOrder(root->left);
    preOrder(root->right);
    cout << root->key << " ";
}

void BFSprint(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;

    q.push(root);
    while (!q.empty()) {
        Node* n = q.front();
        cout << n->key << " ";
        q.pop();
        if (n->left != nullptr) q.push(n->left);
        if (n->right != nullptr) q.push(n->right);
    }
}

void printLevel(Node* root, int level) {
    if(root == nullptr) return;
    if(level == 0) {
        cout << root->key << " ";
    } else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void printTreeBFS(Node *root) {
    for(int i = 0; i < Height(root); i++) {
        printLevel(root, i);
        cout << endl;
    }
}

int main() {
    int a[9] = { 9, 5, 10, 0, 6, 11, -1, 1, 2 };
    Node* r = AVLTree(a, 9);
    preOrder(r);
    cout << endl;
    searchDel(r, 10);
    preOrder(r);
}