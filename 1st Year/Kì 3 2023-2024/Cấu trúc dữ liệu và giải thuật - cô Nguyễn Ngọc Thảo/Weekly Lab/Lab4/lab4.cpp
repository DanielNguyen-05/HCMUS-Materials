#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct NODE {
    int key;
    NODE* left;
    NODE* right;
    int height;
};

NODE* createNode (int data) {
    NODE* new_node = new NODE;
    new_node->key = data;
    new_node->left = new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

int getHeight (NODE* node) {
    if (node == NULL) return 0;
    return node->height;
}

int getBalance (NODE* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

NODE* rotateRight (NODE* node) {
    NODE* x = node->left;
    NODE* y = x->right;

    x->right = node;
    x->left = y;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

NODE* rotateLeft (NODE* node) {
    NODE* x = node->right;
    NODE* y = x->left;

    x->left = node;
    x->right = y;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

void Insert (NODE* &pRoot, int x) {
    if (pRoot == NULL) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key) insert(pRoot->left, x);
    else if (x > pRoot->key) insert(pRoot->right, x);
    else {
        cout << "Value already exists!" << endl;
        return;
    }

    pRoot->height = 1 + max(getHeight(pRoot->left), getHeight(pRoot->right));

    int balance = getBalance(pRoot);

    if (balance > 1 && x < pRoot->left->key) pRoot = rotateRight(pRoot);
    else if (balance < -1 && x > pRoot->right->key) pRoot = rotateLeft(pRoot);
    else if (balance > 1 && x > pRoot->left->key) {
        pRoot->left = rotateLeft(pRoot->left);
        pRoot = rotateRight(pRoot);
    } else if (balance < -1 && x < pRoot->right->key) {
        pRoot->right = rotateRight(pRoot->right);
        pRoot = rotateLeft(pRoot);
    }
}

NODE* minValueNode (NODE* pRoot) {
    if (pRoot == NULL) return NULL;
    while (pRoot != NULL && pRoot->left != NULL)
        pRoot = pRoot->left;
    return pRoot;
}

void Remove (NODE* &pRoot, int x) {
    if (pRoot == NULL) {
        cout << "Value is not found!";
        reutrn;
    }

    if (x < pRoot->key) Remove(pRoot->left, x);
    else if (x > pRoot->key) Remove(pRoot->right, x);
    else {
        if (!pRoot->left || !pRoot->right) {
            NODE* temp = pRoot->left ? pRoot->left : pRoot->right;
            if (!temp) {
                temp = pRoot;
                pRoot = nullptr;
            } else {
                *pRoot = *temp;
            }
            delete temp;
        } else {
            NODE* temp = minValueNode(pRoot->right);
            pRoot->key = temp->key;
            remove(pRoot->right, temp->key);
        }
    }

    if (pRoot == NULL) return;
    pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;

    int balance = getBalance(pRoot);

    int balance = getBalance(pRoot);

    if (balance > 1 && getBalance(pRoot->left) >= 0) pRoot = rotateRight(pRoot);
    else if (balance > 1 && getBalance(pRoot->left) < 0) {
        pRoot->left = rotateLeft(pRoot->left);
        pRoot = rotateRight(pRoot);
    } 
    else if (balance < -1 && getBalance(pRoot->right) <= 0) pRoot = rotateLeft(pRoot);
    else if (balance < -1 && getBalance(pRoot->right) > 0) {
        pRoot->right = rotateRight(pRoot->right);
        pRoot = rotateLeft(pRoot);
    }
}

bool isAVL (NODE* pRoot) {
    if (pRoot == NULL) return true;

    int difference = getHeight(pRoot->left) - getHeight(pRoot->right);

    if (difference >= - 1 && difference <= 1 && isAVL(pRoot->left) && isAVL(pRoot->right)) return true;
    return false;
}