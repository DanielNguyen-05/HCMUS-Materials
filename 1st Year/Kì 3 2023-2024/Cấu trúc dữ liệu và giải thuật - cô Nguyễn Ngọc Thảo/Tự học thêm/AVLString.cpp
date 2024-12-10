#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string key;
    Node* left;
    Node* right;
};

Node* createNode(string key);
int max(int a, int b);
int Height(Node* root);
void rotateLeft(Node* &root);
void rotateRight(Node* &root);
void Insert(Node* &root, string key);
void del(Node* &predecessor, Node* &q);
void searchDel(Node* &root, string key);
Node* AVLTree(vector<string>);
void preOrder(Node* root);
void inOrder(Node* root);
void postOrder(Node* root);
void BFSprint(Node *root);

Node* createNode(string key) {
    Node *n = new Node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int Height(Node* root) {
    if(root == nullptr) return 0;
    return max(Height(root->left), Height(root->right)) + 1;
}

void rotateLeft(Node* &root) {
    Node *y = root->right;
    Node *T2 = y->left;

    y->left = root;
    root->right = T2;

    root = y;
}

void rotateRight(Node* &root) {
    Node *y = root->left;
    Node *T2 = y->right;

    y->right = root;
    root->left = T2;

    root = y;
}

void Insert(Node* &root, string key) {
    if(root == nullptr) root = createNode(key);
    else {
        if(key < root->key) Insert(root->left, key);
        else if(key > root->key) Insert(root->right, key);
        else return;
    }

    int bal = Height(root->right) - Height(root->left);
    if(bal >= -1 && bal <= 1) return; //nothing todo;
    if(bal < -1 && key < root->left->key) rotateRight(root);
    if(bal < -1 && key > root->left->key) {
        rotateLeft(root->left);
        rotateRight(root);
    }
    if(bal > 1 && key > root->right->key) rotateLeft(root);
    if(bal > 1 && key < root->right->key) {
        rotateRight(root->right);
        rotateLeft(root);
    }
}

void del(Node* &predecessor, Node* &q) {
    if(predecessor->right) predecessor->right;
    else {
        q->key = predecessor->key;
        q = predecessor;
        predecessor = predecessor->left;
    }
}

void searchDel(Node* &root, string key) {
    if(key < root->key) searchDel(root->left, key);
    else if(key > root->key) searchDel(root->right, key);
    else {
        Node* q = root;
        if(q->left == nullptr) root = root->right;
        else if(q->right == nullptr) root = root->left;
        else del(root->left, q);
        delete q;
    }

    if(root == nullptr) return; //empty tree
    int bal = Height(root->right) - Height(root->left);
    if(bal >= -1 && bal <= 1) return; //nothing todo;
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

Node* AVLTree(vector<string> a) {
    Node* root = nullptr;
    for(int i = 0; i < a.size(); i++) {
        Insert(root, a[i]);
    }
    return root;
}

void preOrder(Node* root) {
    if(root == nullptr) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if(root == nullptr) return;
    preOrder(root->left);
    cout << root->key << " ";
    preOrder(root->right);
}

void postOrder(Node* root) {
    if(root == nullptr) return;
    preOrder(root->left);
    preOrder(root->right);
    cout << root->key << " ";
}

void BFSprint(Node *root) {
    if(root == nullptr) return;
    queue<Node*> q;

    q.push(root);
    while(!q.empty()) {
        Node *n = q.front();
        cout << n->key <<  " ";
        q.pop();
        if(n->left != nullptr) q.push(n->left);
        if(n->right != nullptr) q.push(n->right);
    }
}

int main() {
    vector <string> a;
    a.push_back("a");
    a.push_back("b");
    a.push_back("c");
    a.push_back("d");
    a.push_back("e");
    Node *r = AVLTree(a);
    BFSprint(r);
}