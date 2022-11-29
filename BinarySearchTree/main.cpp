#include <iostream>
#include <queue>
#include "AVL.h"

using namespace std;

template<typename T>
int findNodeHeight(BSTNode<T>* node){
    if(node == nullptr)
        return 0;
    return node->height = max(findNodeHeight(node->left), findNodeHeight(node->right))+1;
}

template<class T>
void BFT(BSTNode<T> *Tree) {
    if (Tree == nullptr) {
        cerr << "Tree is Empty!" << endl;
        return;
    }
    queue<BSTNode<T> *> q;
    q.push(Tree);
    while (!q.empty()) {
        Tree = q.front();
        q.pop();
        cout << Tree->key << " " << Tree->height << endl;
        if (Tree->left != nullptr)
            q.push(Tree->left);
        if (Tree->right != nullptr)
            q.push(Tree->right);
    }
}

// inOrder DFT
template<class T>
void inOrder(BSTNode<T> *Node) {
    if (Node == nullptr)
        return;
    inOrder(Node->left);
    cout << Node->key << " " << Node->height << endl;
    inOrder(Node->right);
}


//PreOrder DFT
template<class T>
void PreOrder(BSTNode<T> *Node) {
    if (Node == nullptr)
        return;
    cout << Node->key << " ";
    PreOrder(Node->left);
    PreOrder(Node->right);
}

// PostOrder DFT
template<class T>
void PostOrder(BSTNode<T> *Node) {
    if (Node == nullptr)
        return;
    PostOrder(Node->left);
    PostOrder(Node->right);
    cout << Node->key << " ";
}

template<class T>
void printSpaces(int n, BSTNode<T> *node) {
    for (; n > 0; n--) {
        cout << " ";
    }
    if (node == NULL)
        cout << " ";
    else {
        cout << node->key;
    }
}

template<class T>
void PrintTree(BSTNode<T> *head) {
    queue<BSTNode<T> *> q, tmp;
    int cnt = 0, height = head->height - 1;
    int number_of_elements = (1 << (head->height)) - 1;
    q.push(head);
    while (cnt <= height) {
        auto removed = q.front();
        q.pop();
        if (tmp.empty())
            printSpaces(number_of_elements / (1 << (cnt + 1)), removed);
        else
            printSpaces(number_of_elements / (1 << (cnt)), removed);
        if (removed == NULL) {
            tmp.push(NULL);
            tmp.push(NULL);
        } else {
            tmp.push(removed->left);
            tmp.push(removed->right);
        }
        if (q.empty()) {
            cout << "\n\n";
            q = tmp;
            while (!tmp.empty())
                tmp.pop();
            cnt++;
        }
    }
}

int main() {
    AVL<double> b;
    b.insert(3);
    b.insert(4);
    b.insert(5);
    findNodeHeight(b.getRoot());
    PrintTree(b.getRoot());
    cout << "After Rotation:" << endl;
    b.leftRotation(b.getRoot());
    findNodeHeight(b.getRoot());
    PrintTree(b.getRoot());
    return 0;
}
