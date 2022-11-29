#include <iostream>

using namespace std;

template<class tp>
struct node {
    tp info;
    node<tp> *link;
};

template<class t>
class stack {
protected:
    node<t> *tp;
    int sz;
public:
    stack() {
        sz = 0;
        tp = NULL;
    }

    void push(t &x) {
        node<t> *cur = tp;
        if (!sz) {
            tp = new node<t>;
            tp->info = x;
            tp->link = NULL;
            cur = tp;
        } else {
            tp = new node<t>;
            tp->link = cur;
            tp->info = x;
            cur = tp;
        }
        sz++;
    }

    void pop() {
        node<t> *cur = tp;
        tp = tp->link;
        delete cur;
        cur = tp;
        sz--;
    }

    bool empty() {
        return tp == NULL;
    }

    int size() {
        return sz;
    }

    t &top() {
        return tp->info;
    }

    bool operator==(stack<t> &obj) {
        node<t> *cur = obj.tp;
        node<t> *cur1 = this->tp;
        while (obj.cur != NULL) {
            if (cur->info != cur1->info)
                return false;
            cur = cur->link;
            cur1 = cur1->link;
        }
        return true;
    }

    ~stack() {
        node<t> *cur = tp;
        while (cur != NULL) {
            cur = cur->link;
            delete tp;
            tp = cur;
        }
    }
};

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    stack<char> s;
    string t;
    cin >> t;
    for (auto &i: t) {
        if (i == ')' and !s.empty() and s.top() == '(')
            s.pop();
        else
            s.push(i);
    }
    cout << t.size() - s.size() << '\n';
    return 0;
}
