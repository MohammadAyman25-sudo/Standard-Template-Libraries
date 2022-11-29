//
// Created by ayman on 11/27/2022.
//

#ifndef RED_BLACK_TREE_REDBLACK_H
#define RED_BLACK_TREE_REDBLACK_H

template <class Tp>
struct RB_Node {
    int val, height = 0;
    bool isRed = true;
    bool isDB = false;
    RB_Node<Tp> *left = nullptr;
    RB_Node<Tp> *right = nullptr;
    RB_Node<Tp> *parent = nullptr;
};

template <class tp>
class RB_Tree {
private:
    RB_Node<tp> *root;
    int sz = 0;

    void fix_deletion(RB_Node<tp>*node){
        // case 0
        if (node == root){
            node->isDB = false;
        }
        else{
            while(node != root and node->isDB){
                if(node->parent->left == node){
                    auto y = node->parent->right;
                    if(y != nullptr){
                        if((y->left == nullptr and y->right == nullptr) or (!y->left->isRed and !y->right->isRed)){
                            if(node->parent->isRed)
                                node->parent->isRed = false;
                            else
                                node->parent->isDB = true;
                            y->isRed = true;
                            node->isDB = false;
                            node = node->parent;
                        }
                        else{
                            if(y->left != nullptr and y->left->isRed){
                                y->isRed = true;
                                y->left->isRed = false;
                                right_Rotation(y);
                            }
                            bool temp = y->isRed;
                            y->isRed = y->parent->isRed;
                            y->parent->isRed = temp;
                            left_Rotation(node->parent);
                            node->parent->parent->right->isRed = false;
                            break;
                        }
                    }
                    else{
                        if(node->parent->isRed)
                            node->parent->isRed = false;
                        else
                            node->parent->isDB = true;
                        node->isDB = false;
                        node = node->parent;
                    }
                }else{
                    auto y = node->parent->left;
                    if(y != nullptr){
                        if((y->left == nullptr and y->right == nullptr) or (!y->left->isRed and !y->right->isRed)){
                            if(node->parent->isRed)
                                node->parent->isRed = false;
                            else
                                node->parent->isDB = true;
                            y->isRed = true;
                            node->isDB = false;
                            node = node->parent;
                        }
                        else{
                            if(y->right != nullptr and y->right->isRed){
                                y->isRed = true;
                                y->right->isRed = false;
                                left_Rotation(y);
                            }
                            node->parent->isRed = true;
                            right_Rotation(node->parent);
                            node->parent->isRed = false;
                            if(y->left != nullptr)
                                y->left->isRed = false;
                            break;
                        }
                    }
                    else{
                        if(node->parent->isRed)
                            node->parent->isRed = false;
                        else
                            node->parent->isDB = true;
                        node->isDB = false;
                        node = node->parent;
                    }
                }
            }
        }
        root->isDB = false;
    }
    void fix_tree(RB_Node<tp> *node) {
        while ((node != root) and node->parent->isRed) {
            if (node->parent->parent->left == node->parent) {
                auto y = node->parent->parent->right;
                if (y != nullptr and y->isRed) {
                    y->parent->isRed = true;
                    y->isRed = false;
                    y->parent->left->isRed = false;
                    node = y->parent;
                } else if (y == nullptr or !y->isRed) {
                    if (node->parent->right == node) {
                        left_Rotation(node->parent);
                        // case 3
                        right_Rotation(node->parent);
                        node->isRed = false;
                        node->right->isRed = true;
                        break;
                    } else {
                        left_Rotation(node->parent->parent);
                        node->parent->isRed = false;
                        node->parent->right->isRed = true;
                        break;
                    }
                }
            } else {
                auto y = node->parent->parent->left;
                if (y != nullptr and y->isRed) {
                    y->parent->isRed = true;
                    y->isRed = false;
                    y->parent->right->isRed = false;
                    node = y->parent;
                } else if (y == nullptr or !y->isRed) {
                    if (node->parent->left == node) {
                        right_Rotation(node->parent);

                        // case 3
                        left_Rotation(node->parent);
                        node->isRed = false;
                        node->left->isRed = true;
                        break;
                    } else {
                        left_Rotation(node->parent->parent);
                        node->parent->isRed = false;
                        node->parent->left->isRed = true;
                        break;
                    }
                }
            }
        }
        root->isRed = false;
    }

    void right_Rotation(RB_Node<tp> *node) {
        auto tem = node->left;
        node->left = tem->right;
        bool isLeft = false;
        if (node != this->root and node->parent->left == node)
            isLeft = true;
        if (tem->right != nullptr)
            tem->right->parent = node;
        tem->right = node;
        tem->parent = node->parent;
        node->parent = tem;
        if (tem->parent != nullptr) {
            if (isLeft) {
                tem->parent->left = tem;
            } else {
                tem->parent->right = tem;
            }
        }
        if (node == this->root) {
            this->root = tem;
        }
    }

    void left_Rotation(RB_Node<tp> *node) {
        auto tem = node->right;
        node->right = tem->left;
        bool isLeft = false;
        if (node != this->root and node->parent->left == node)
            isLeft = true;
        if (tem->left != nullptr)
            tem->left->parent = node;
        tem->left = node;
        tem->parent = node->parent;
        node->parent = tem;
        if (tem->parent != nullptr) {
            if (isLeft) {
                tem->parent->left = tem;
            } else {
                tem->parent->right = tem;
            }
        }
        if (node == this->root) {
            this->root = tem;
        }
    }

    void post_delete(RB_Node<tp>* start){
        if(start == nullptr){
            return;
        }
        post_delete(start->left);
        post_delete(start->right);
        delete start;
    }
public:
    RB_Tree() {
        root = nullptr;
        sz = 0;
    }

    bool search(tp x) {
        RB_Node<tp> *cur = root;
        while (cur != nullptr) {
            if (cur->val == x)
                return true;
            if (cur->val > x) {
                cur = cur->left;
            } else if (cur->val < x) {
                cur = cur->right;
            }
        }
        return false;
    }

    RB_Node<tp> *get_successor(RB_Node<tp> *node) {
        auto cur = node->right;
        RB_Node<tp> *ans = nullptr;
        while (cur != nullptr) {
            ans = cur;
            cur = cur->left;
        }
        return ans;
    }

    RB_Node<tp> *get_predecessor(RB_Node<tp> *node) {
        auto cur = node->left;
        RB_Node<tp> *ans = nullptr;
        while (cur != nullptr) {
            ans = cur;
            cur = cur->right;
        }
        return ans;
    }

    int getMax() {
        auto cur = root;
        RB_Node<tp> *ans;
        while (cur != nullptr) {
            ans = cur;
            cur = cur->right;
        }
        return ans->val;
    }

    int getMin() {
        auto cur = root;
        RB_Node<tp> *ans;
        while (cur != nullptr) {
            ans = cur;
            cur = cur->left;
        }
        return ans->val;
    }

    void erase(tp x){
        auto tem = root;
        while(tem != nullptr){
            if(tem->val == x){
                break;
            }
            else if(tem->val > x){
                tem = tem->left;
            }
            else
                tem = tem->right;
        }
        if(tem == nullptr){
            std::cout << "Not Found \n ";
        }else{
            auto dec = get_predecessor(tem);
            if(tem->left != nullptr){
                auto cur = tem;
                if(dec != nullptr)
                    tem->val = dec->val;
                tem = dec;
                while(tem != nullptr){
                    cur = tem;
                    dec = get_predecessor(tem);
                    if(dec != nullptr)
                        tem->val = dec->val;
                    tem = dec;
                }
                tem = cur;
                if(!tem->isRed){
                    tem->isDB = true;
                    fix_deletion(tem);
                }
                if(tem->parent->left == tem)
                    tem->parent->left = nullptr;
                else
                    tem->parent->right = nullptr;
                cur = 0;
            }
            else{
                if(tem->right == nullptr){
                    if(tem->isRed){
                        if(tem->parent->left == tem)
                            tem->parent->left = nullptr;
                        else
                            tem->parent->right = nullptr;
                    }
                    else{
                        tem->isDB = true;
                        fix_deletion(tem);
                    }
                    if(tem->parent->left == tem)
                        tem->parent->left = nullptr;
                    else
                        tem->parent->right = nullptr;
                }
                else{
                    tem->parent = tem->right;
                    tem->right->parent = tem->parent;
                    if(!tem->right->isRed){
                        tem->right->isDB = true;
                        fix_deletion(tem->right);
                    }
                    else{
                        tem->right->isRed = false;
                    }
                }
            }
        }
        sz--;
        delete tem;
    }
    void insert(tp x) {
        if (root == nullptr) {
            root = new RB_Node<tp>();
            root->isRed = false;
            root->val = x;
            sz++;
            return;
        } else {
            RB_Node<tp> *tem = root, *pre;
            while (tem != nullptr) {
                if (x > tem->val) {
                    pre = tem;
                    tem = tem->right;
                } else if (x < tem->val) {
                    pre = tem;
                    tem = tem->left;
                } else {
                    return;
                }
            }
            if (pre->val > x) {
                pre->left = new RB_Node<tp>();
                pre->left->val = x;
                pre->left->parent = pre;
                fix_tree(pre->left);
            } else {
                pre->right = new RB_Node<tp>();
                pre->right->val = x;
                pre->right->parent = pre;
                fix_tree(pre->right);
            }
            sz++;
        }
    }

    int size() const {
        return sz;
    }

    RB_Node<tp> *getRoot() const {
        return root;
    }

    ~RB_Tree(){
        post_delete(root);
    }
};

#endif //RED_BLACK_TREE_REDBLACK_H
