//
// Created by ayman on 4/23/2022.
//

#ifndef BINARYSEARCHTREE_BST_H
#define BINARYSEARCHTREE_BST_H
#include <iostream>

template<class T>
struct BSTNode {
    T key;
    BSTNode<T> *left;
    BSTNode<T> *right;
    int height;
    BSTNode() {
        key = 0;
        left = 0;
        right = 0;
        height = 0;
    }

    BSTNode(T &element, BSTNode<T> *r = 0, BSTNode<T> *l = 0, int h = 1) {
        key = element;
        right = r;
        left = l;
        height = h;
    }
};

template<typename T>
class BST {
private:
    BSTNode<T> *root;
public:
    BST() { root = 0; }

    bool empty() { return root == 0; }

    void setRoot(BSTNode<T> * r){
        root = r;
    }
    void clear(BSTNode<T> *r) {
        if (r == nullptr)
            return;
        clear(r->left);
        clear(r->right);
        delete r;
    }

    T *search(T &&element) {
        BSTNode<T> *p = root;
        while (p != 0) {
            if (p->key == element)
                return &p->key;
            if (p->key > element)
                p = p->left;
            else
                p = p->right;
        }
        return 0;
    }

    void insert(T &&x) {
        if (root == 0) {
            root = new BSTNode<T>(x);
        } else {
            BSTNode<T> *cur, *p_cur = nullptr;
            cur = root;
            while (cur != 0) {
                if (x == cur->key)
                    return;
                else if (x < cur->key) {
                    p_cur = cur;
                    cur = cur->left;
                } else {
                    p_cur = cur;
                    cur = cur->right;
                }
            }
            if (x < p_cur->key) {
                auto *l = new BSTNode<T>(x);
                p_cur->left = l;
            } else if (x > p_cur->key) {
                auto *r = new BSTNode<T>(x);
                p_cur->right = r;
            }
        }
    }

    void insert(T &x) {
        if (root == 0) {
            root = new BSTNode<T>(x);
        } else {
            BSTNode<T> *cur, *p_cur;
            cur = root;
            while (cur != 0) {
                if (x == root->key)
                    return;
                else if (x < root->key) {
                    p_cur = cur;
                    cur = root->left;
                } else {
                    p_cur = cur;
                    cur = root->right;
                }
            }
            if (x < p_cur->key) {
                auto *l = new BSTNode<T>(x);
                p_cur->left = l;
            } else if (x > p_cur->key) {
                auto *r = new BSTNode<T>(x);
                p_cur->right = r;
            }
        }
    }

    void erase(BSTNode<T>* node){
        BSTNode<T>* cur = root, *p_cur;
        if(node == root and (root->left == nullptr or root->right == nullptr)){
            delete cur;
            return;
        }
        if (node->right == nullptr and node->left == nullptr){ // Deleting leaves
            while(cur != nullptr){
                if(cur->key == node->key)
                    break;
                if(cur->key < node->key){
                    p_cur = cur;
                    cur = cur->right;
                }
                else{
                    p_cur = cur;
                    cur = cur->left;
                }
            }
            if(cur == p_cur->left){
                delete cur;
                p_cur->left = nullptr;
            }
            else if(cur == p_cur->right){
                delete  cur;
                p_cur->right = nullptr;
            }
        }
        else if(node->left != nullptr and node->right != nullptr){
            // Node with two children
            auto predecessor = getPredecessor(node);
            BSTNode<T>* cur = node->left, *p_cur = nullptr;
            while(cur != predecessor){
                p_cur = cur;
                cur = cur->right;
            }

            T tm = node->key;
            node->key = predecessor->key;
            predecessor->key = tm;

            delete predecessor;
            p_cur->right = nullptr;
        }
        else{
            // Node with one child
            while(cur != nullptr){
                if(cur -> key == node->key)
                    break;
                if(cur->key < node->key){
                    p_cur = cur;
                    cur = cur->right;
                }
                else{
                    p_cur = cur;
                    cur = cur->left;
                }
            }
            if(p_cur->left == cur){
                if(cur->left != nullptr)
                    p_cur->left = cur->left;
                if(cur->right != nullptr)
                    p_cur->left = cur->right;
            }else if(p_cur->right == cur){
                if(cur->left != nullptr)
                    p_cur->right = cur->left;
                if(cur->right != nullptr)
                    p_cur->right = cur->right;
            }
            delete cur;
        }
    }
    BSTNode<T>* getPredecessor(BSTNode<T>* node){
        BSTNode<T>* cur = node, *p_cur = nullptr;
        cur = cur->left;
        while(cur != nullptr){
            p_cur = cur;
            cur = cur->right;
        }
        return p_cur;
    }
    BSTNode<T>* getSuccessor(BSTNode<T> *node){
        BSTNode<T>* cur = node, *p_cur = nullptr;
        cur = cur->right;
        while(cur != nullptr){
            p_cur = cur;
            cur = cur->left;
        }
        return p_cur;
    }
    BSTNode<T> *getRoot() const;
    ~BST() {
        clear(root);
    }
};

template<typename T>
BSTNode<T> *BST<T>::getRoot() const {
    return root;
}

#endif //BINARYSEARCHTREE_BST_H
