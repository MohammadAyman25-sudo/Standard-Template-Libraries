#include <iostream>
#include <queue>
#include "RedBlack.h"

using namespace std;

void dfs(RB_Node<int>* root){
    if(root == nullptr){
        return;
    }
    dfs(root->left);
    cout << root->val << " " << root->isRed << endl;
    dfs(root->right);

}

int find_height(RB_Node<int> *root) {
    if (root == nullptr)
        return 0;
    return root->height = max(find_height(root->left), find_height(root->right)) + 1;
}

void printSpaces(int n, RB_Node<int> *node) {
    for (; n > 0; n--) {
        cout << "   ";
    }
    if (node == nullptr)
        cout << "   ";
    else {
        cout << node->val << "|" << (node->isRed?"R":"B");
    }
}

void PrintTree(RB_Node<int> *head) {
    queue<RB_Node<int> *> q, tmp;
    int cnt = 0, height = head->height - 1;
    int number_of_elements = (1 << (head->height)) - 1;
    q.push(head);
    while (cnt <= height) {
        if(!q.empty()){
            auto removed = q.front();
            q.pop();
            if (tmp.empty())
                printSpaces(number_of_elements / (1 << (cnt + 1)), removed);
            else
                printSpaces(number_of_elements / (1 << (cnt)), removed);
            if (removed == nullptr) {
                tmp.push(nullptr);
                tmp.push(nullptr);
            } else {
                tmp.push(removed->left);
                tmp.push(removed->right);
            }
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
    RB_Tree<int> tree;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        tree.insert(a);
    }
    find_height(tree.getRoot());
    PrintTree(tree.getRoot());
    return 0;
}
