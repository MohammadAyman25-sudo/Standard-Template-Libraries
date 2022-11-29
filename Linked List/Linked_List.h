//
// Created by Mohammad Ayman on 4/2/2022.
//

#ifndef LINKED_LIST_LINKED_LIST_H
#define LINKED_LIST_LINKED_LIST_H

#include <iostream>

template<typename T>
struct Node {
    T item;
    Node<T> *next = NULL;
};

template<typename T>
struct DeNode {
    T item;
    DeNode<T> *next = NULL;
    DeNode<T> *previous = NULL;
};


template<class T, class element>
class LinkedList {
protected:
    int sz;
    element *head;
    element *tail;
public:
    LinkedList() {
        sz = 0;
        head = NULL;
        tail = NULL;
    }

    virtual void insert_head(T &x) = 0;

    virtual void insert_tail(T &x) = 0;

    virtual void insert_middle(T &after, T &x) = 0;

    virtual void erase_head() = 0;

    virtual void erase_tail() = 0;

    virtual void erase_middle(T &x) = 0;

    virtual bool search(T &x) = 0;

    bool isFull() const { return false; }

    bool isEmpty() const { return head == NULL; }

    int size() const { return sz; }

    T &front() { return head->item; }

    virtual void insert_sorted(T &x) = 0;

    T &back() { return tail->item; }

    element *begin() { return head; }

    element *end() { return tail; }

    void clear() {
        element *current = head;
        while (head != tail) {
            current = head;
            head = head->next;
            delete current;
            sz--;
        }
        delete head;
        sz--;
        head = NULL;
        tail = NULL;
    }
};

template<typename T>
class List : public LinkedList<T, Node<T>> {
public:
    List() = default;

    List(const List<T> &obj) {
        Node<T> *current = obj.LinkedList<T, Node<T>>::head;
        LinkedList<T, Node<T>>::sz = obj.LinkedList<T, Node<T>>::sz;
        LinkedList<T, Node<T>>::head = new Node<T>;
        LinkedList<T, Node<T>>::head->next = NULL;
        LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::head;
        while (current != NULL) {
            LinkedList<T, Node<T>>::tail->item = current->item;
            current = current->next;
            if (current == NULL)
                break;
            LinkedList<T, Node<T>>::tail->next = new Node<T>;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::tail->next;
            LinkedList<T, Node<T>>::tail->next = NULL;
        }
    }

    void insert_sorted(T &x) {
        Node<T> *current = LinkedList<T, Node<T>>::head->next;
        Node<T> *previousCurrent = LinkedList<T, Node<T>>::head;
        if (previousCurrent->item <= x) {
            while (current != NULL) {
                if (current->item <= x) {
                    current = current->next;
                    previousCurrent = previousCurrent->next;
                } else {
                    break;
                }
            }
            auto node = new Node<T>;
            node->next = current;
            previousCurrent->next = node;
            node->item = x;
            LinkedList<T, Node<T>>::sz++;
        } else
            insert_head(x);
    }

    void insert_tail(T &x) {
        if (!LinkedList<T, Node<T>>::sz) {
            LinkedList<T, Node<T>>::head = new Node<T>;
            LinkedList<T, Node<T>>::head->item = x;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::head;
            LinkedList<T, Node<T>>::head->next = NULL;
        } else {
            LinkedList<T, Node<T>>::tail->next = new Node<T>;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::tail->next;
            LinkedList<T, Node<T>>::tail->item = x;
            LinkedList<T, Node<T>>::tail->next = NULL;
        }
        LinkedList<T, Node<T>>::sz++;
    }

    void insert_middle(T &after, T &x) {
        if (!search(after)) {
            std::cerr << after << " Not Found\n";
        } else {
            Node<T> *current = LinkedList<T, Node<T>>::head;
            while (current != NULL) {
                if (current->item == after) {
                    auto *node = new Node<T>;
                    node->item = x;
                    node->next = current->next;
                    current->next = node;
                    LinkedList<T, Node<T>>::sz++;
                    break;
                }
            }
        }
    }

    void insert_head(T &x) {
        if (!LinkedList<T, Node<T>>::sz) {
            LinkedList<T, Node<T>>::head = new Node<T>;
            LinkedList<T, Node<T>>::head->item = x;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::head;
            LinkedList<T, Node<T>>::head->next = NULL;
        } else {
            auto new_node = new Node<T>;
            new_node->next = LinkedList<T, Node<T>>::head;
            LinkedList<T, Node<T>>::head = new_node;
            LinkedList<T, Node<T>>::head->item = x;
        }
        LinkedList<T, Node<T>>::sz++;
    }

    void erase_head() {
        Node<T> *current;
        current = LinkedList<T, Node<T>>::head;
        LinkedList<T, Node<T>>::head = LinkedList<T, Node<T>>::head->next;
        delete current;
        LinkedList<T, Node<T>>::sz--;
    }

    void erase_tail() {
        Node<T> *current;
        current = LinkedList<T, Node<T>>::head;
        if (LinkedList<T, Node<T>>::head != LinkedList<T, Node<T>>::tail) {
            while (current->next->next != NULL) {
                current = current->next;
            }
            delete LinkedList<T, Node<T>>::tail;
            LinkedList<T, Node<T>>::tail = current;
            LinkedList<T, Node<T>>::tail->next = NULL;
        } else {
            delete LinkedList<T, Node<T>>::tail;
            LinkedList<T, Node<T>>::tail = NULL;
            LinkedList<T, Node<T>>::head = NULL;
        }
        LinkedList<T, Node<T>>::sz--;
    }

    void erase_middle(T &x) {
        Node<T> *current, *priorCurrent;
        bool found = false;
        priorCurrent = LinkedList<T, Node<T>>::head;
        current = LinkedList<T, Node<T>>::head->next;
        while (current != NULL) {
            if (current->item == x) {
                found = true;
                break;
            }
            current = current->next;
            priorCurrent = priorCurrent->next;
        }
        if (found) {
            priorCurrent->next = current->next;
            delete current;
            LinkedList<T, Node<T>>::sz--;
        } else {
            std::cerr << x << " Not found \n";
        }
    }

    bool search(T &x) {
        Node<T> *current = LinkedList<T, Node<T>>::head;
        while (current != NULL) {
            if (current->item == x)
                return true;
            current = current->next;
        }
        return false;
    }

    bool operator==(List<T> &obj) {
        if (LinkedList<T, Node<T>>::sz != obj.size())
            return false;
        Node<T> *cur = LinkedList<T, Node<T>>::head;
        Node<T> *objCur = obj.LinkedList<T, Node<T>>::begin();
        while (cur != NULL) {
            if (cur->item != objCur->item)
                return false;
            cur = cur->next;
            objCur = objCur->next;
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, List<T> &o) {
        Node<T> *current = o.LinkedList<T, Node<T>>::head;
        if (!o.LinkedList<T, Node<T>>::size())
            std::cerr << "List is Empty\n";
        else {
            while (current->next != NULL) {
                os << current->item << "->";
                current = current->next;
            }
            os << current->item;
        }
        return os;
    }

    List<T> &operator=(const List<T> &obj) {
        Node<T> *current = obj.LinkedList<T, Node<T>>::head;
        LinkedList<T, Node<T>>::sz = obj.LinkedList<T, Node<T>>::sz;
        LinkedList<T, Node<T>>::head = new Node<T>;
        LinkedList<T, Node<T>>::head->next = NULL;
        LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::head;
        while (current != NULL) {
            LinkedList<T, Node<T>>::tail->item = current->item;
            current = current->next;
            if (current == NULL)
                break;
            LinkedList<T, Node<T>>::tail->next = new Node<T>;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::tail->next;
            LinkedList<T, Node<T>>::tail->next = NULL;
        }
        return *this;
    }

    List<T> &operator+=(const List<T> &obj) {
        Node<T> *current = obj.LinkedList<T, Node<T>>::begin();
        while (current != NULL) {
            this->insert_tail(current->item);
            current = current->next;
        }
        return *this;
    }

    ~List() {
        Node<T> *cur = LinkedList<T, Node<T>>::head;
        while (cur != NULL) {
            LinkedList<T, Node<T>>::head = LinkedList<T, Node<T>>::head->next;
            delete cur;
            cur = LinkedList<T, Node<T>>::head;
        }
    }
};

template<class T>
class CList : public LinkedList<T, Node<T>> {
public:
    CList() = default;

    CList(const CList<T> &obj) {
        Node<T> *current = obj.LinkedList<T, Node<T>>::head;
        LinkedList<T, Node<T>>::sz = obj.LinkedList<T, Node<T>>::sz;
        LinkedList<T, Node<T>>::head = new Node<T>;
        LinkedList<T, Node<T>>::head->next = LinkedList<T, Node<T>>::head;
        LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::head;
        while (current->next != obj.LinkedList<T, Node<T>>::head) {
            LinkedList<T, Node<T>>::tail->item = current->item;
            current = current->next;
            if (current == obj.LinkedList<T, Node<T>>::head)
                break;
            LinkedList<T, Node<T>>::tail->next = new Node<T>;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::tail->next;
            LinkedList<T, Node<T>>::tail->next = LinkedList<T, Node<T>>::head;
        }
        LinkedList<T, Node<T>>::tail->item = current->item;
    }

    void insert_middle(T &after, T &x) {
        if (!search(after)) {
            std::cerr << after << " Not Found\n";
        } else {
            Node<T> *current = LinkedList<T, Node<T>>::head;
            while (current->next != LinkedList<T, Node<T>>::head) {
                if (current->item == after) {
                    auto *node = new Node<T>;
                    node->item = x;
                    node->next = current->next;
                    current->next = node;
                    LinkedList<T, Node<T>>::sz++;
                    break;
                }
                current = current->next;
            }
            if (current->item == after) {
                auto *node = new Node<T>;
                node->item = x;
                node->next = current->next;
                current->next = node;
                LinkedList<T, Node<T>>::sz++;
            }
        }
    }

    void insert_sorted(T &x) {
        Node<T> *current = LinkedList<T, Node<T>>::head->next;
        Node<T> *previousCurrent = LinkedList<T, Node<T>>::head;
        if (previousCurrent->item <= x) {
            while (current->next != LinkedList<T, Node<T>>::head) {
                if (current->item <= x) {
                    current = current->next;
                    previousCurrent = previousCurrent->next;
                } else {
                    break;
                }
            }
            if (current->item <= x) {
                current = current->next;
                previousCurrent = previousCurrent->next;
            }
            auto node = new Node<T>;
            node->next = current;
            previousCurrent->next = node;
            node->item = x;
            LinkedList<T, Node<T>>::sz++;
        } else
            insert_head(x);
    }

    void insert_head(T &x) {
        if (!LinkedList<T, Node<T>>::sz) {
            LinkedList<T, Node<T>>::head = new Node<T>;
            LinkedList<T, Node<T>>::head->item = x;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::head;
            LinkedList<T, Node<T>>::head->next = NULL;
        } else {
            auto new_node = new Node<T>;
            new_node->next = LinkedList<T, Node<T>>::head;
            LinkedList<T, Node<T>>::head = new_node;
            LinkedList<T, Node<T>>::head->item = x;
        }
        LinkedList<T, Node<T>>::sz++;
    }

    void erase_head() {
        Node<T> *current;
        current = LinkedList<T, Node<T>>::head;
        LinkedList<T, Node<T>>::head = LinkedList<T, Node<T>>::head->next;
        delete current;
        LinkedList<T, Node<T>>::sz--;
    }

    void erase_middle(T &x) {
        Node<T> *current, *priorCurrent;
        bool found = false;
        priorCurrent = LinkedList<T, Node<T>>::head;
        current = LinkedList<T, Node<T>>::head->next;
        while (current->next != LinkedList<T, Node<T>>::head) {
            if (current->item == x) {
                found = true;
                break;
            }
            current = current->next;
            priorCurrent = priorCurrent->next;
        }
        if (found) {
            priorCurrent->next = current->next;
            delete current;
            LinkedList<T, Node<T>>::sz--;
        } else if (!found and current->item == x) {
            delete current;
            priorCurrent->next = LinkedList<T, Node<T>>::head;
            LinkedList<T, Node<T>>::sz--;
        } else {
            std::cerr << x << " Not found \n";
        }
    }

    void insert_tail(T &x) {
        if (!LinkedList<T, Node<T>>::sz) {
            LinkedList<T, Node<T>>::head = new Node<T>;
            LinkedList<T, Node<T>>::head->item = x;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::head;
            LinkedList<T, Node<T>>::head->next = LinkedList<T, Node<T>>::head;
        } else {
            LinkedList<T, Node<T>>::tail->next = new Node<T>;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::tail->next;
            LinkedList<T, Node<T>>::tail->item = x;
            LinkedList<T, Node<T>>::tail->next = LinkedList<T, Node<T>>::head;
        }
        LinkedList<T, Node<T>>::sz++;
    }

    void erase_tail() {
        Node<T> *current;
        current = LinkedList<T, Node<T>>::head;
        if (LinkedList<T, Node<T>>::head != LinkedList<T, Node<T>>::tail) {
            while (current->next->next != LinkedList<T, Node<T>>::head) {
                current = current->next;
            }
            delete LinkedList<T, Node<T>>::tail;
            LinkedList<T, Node<T>>::tail = current;
            LinkedList<T, Node<T>>::tail->next = LinkedList<T, Node<T>>::head;
        } else {
            delete LinkedList<T, Node<T>>::tail;
            LinkedList<T, Node<T>>::tail = NULL;
            LinkedList<T, Node<T>>::head = NULL;
        }
        LinkedList<T, Node<T>>::sz--;
    }

    bool search(T &x) {
        Node<T> *current = LinkedList<T, Node<T>>::head;
        while (current->next != LinkedList<T, Node<T>>::head) {
            if (current->item == x)
                return true;
            current = current->next;
        }
        if (current->item == x)
            return true;
        return false;
    }

    bool operator==(CList<T> &obj) {
        if (LinkedList<T, Node<T>>::sz != obj.LinkedList<T, Node<T>>::sz)
            return false;
        Node<T> *cur = LinkedList<T, Node<T>>::head;
        Node<T> *objCur = obj.LinkedList<T, Node<T>>::head;
        while (cur->next != LinkedList<T, Node<T>>::head) {
            if (cur->item != objCur->item)
                return false;
            cur = cur->next;
            objCur = objCur->next;
        }
        if (cur->item != objCur->item)
            return false;
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, CList<T> &o) {
        Node<T> *current = o.LinkedList<T, Node<T>>::head;
        if (!o.LinkedList<T, Node<T>>::size())
            std::cerr << "List is Empty\n";
        else {
            while (current->next != o.LinkedList<T, Node<T>>::head) {
                os << current->item << "->";
                current = current->next;
            }
            os << current->item;
        }
        return os;
    }

    CList<T> &operator=(const CList<T> &obj) {
        Node<T> *current = obj.LinkedList<T, Node<T>>::head;
        LinkedList<T, Node<T>>::sz = obj.LinkedList<T, Node<T>>::sz;
        LinkedList<T, Node<T>>::head = new Node<T>;
        LinkedList<T, Node<T>>::head->next = LinkedList<T, Node<T>>::head;
        LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::head;
        while (current->next != obj.LinkedList<T, Node<T>>::head) {
            LinkedList<T, Node<T>>::tail->item = current->item;
            current = current->next;
            if (current == obj.LinkedList<T, Node<T>>::head)
                break;
            LinkedList<T, Node<T>>::tail->next = new Node<T>;
            LinkedList<T, Node<T>>::tail = LinkedList<T, Node<T>>::tail->next;
            LinkedList<T, Node<T>>::tail->next = LinkedList<T, Node<T>>::head;
        }
        LinkedList<T, Node<T>>::tail->item = current->item;
        return *this;
    }

    CList<T> &operator+=(const CList<T> &obj) {
        Node<T> *current = obj.LinkedList<T, Node<T>>::head;
        while (current->next != obj.LinkedList<T, Node<T>>::head) {
            this->insert_tail(current->item);
            current = current->next;
        }
        this->insert_tail(current->item);
        return *this;
    }

    ~CList() {
        Node<T> *current = LinkedList<T, Node<T>>::head;
        while (LinkedList<T, Node<T>>::head != LinkedList<T, Node<T>>::tail) {
            LinkedList<T, Node<T>>::head = LinkedList<T, Node<T>>::head->next;
            delete current;
            current = LinkedList<T, Node<T>>::head;
        }
    }

};

template<typename T>
class DLList : public LinkedList<T, DeNode<T>> {
public:
    DLList() = default;

    DLList(const DLList<T> &obj) {
        DeNode<T> *current = obj.LinkedList<T, DeNode<T>>::begin();
        LinkedList<T, DeNode<T>>::sz = obj.LinkedList<T, DeNode<T>>::size();
        LinkedList<T, DeNode<T>>::head = new DeNode<T>;
        LinkedList<T, DeNode<T>>::head->next = NULL;
        LinkedList<T, DeNode<T>>::head->previous = NULL;
        LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::head;
        while (current != NULL) {
            LinkedList<T, DeNode<T>>::tail->item = current->item;
            current = current->next;
            if (current == NULL)
                break;
            LinkedList<T, DeNode<T>>::tail->next = new DeNode<T>;
            LinkedList<T, DeNode<T>>::tail->next->previous = LinkedList<T, DeNode<T>>::tail;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::tail->next;
            LinkedList<T, DeNode<T>>::tail->next = NULL;
        }
    }

    void insert_tail(T &x) {
        if (!LinkedList<T, DeNode<T>>::sz) {
            LinkedList<T, DeNode<T>>::head = new DeNode<T>;
            LinkedList<T, DeNode<T>>::head->item = x;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head->next = NULL;
            LinkedList<T, DeNode<T>>::head->previous = NULL;
        } else {
            LinkedList<T, DeNode<T>>::tail->next = new DeNode<T>;
            LinkedList<T, DeNode<T>>::tail->next->previous = LinkedList<T, DeNode<T>>::tail;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::tail->next;
            LinkedList<T, DeNode<T>>::tail->item = x;
            LinkedList<T, DeNode<T>>::tail->next = NULL;
        }
        LinkedList<T, DeNode<T>>::sz++;
    }

    void insert_sorted(T &x) {
        DeNode<T> *current = LinkedList<T, DeNode<T>>::head->next;
        DeNode<T> *previousCurrent = LinkedList<T, DeNode<T>>::head;
        if (previousCurrent->item <= x) {
            while (current != NULL) {
                if (current->item <= x) {
                    current = current->next;
                    previousCurrent = previousCurrent->next;
                } else {
                    break;
                }
            }
            auto node = new DeNode<T>;
            node->next = current;
            current->previous = node;
            previousCurrent->next = node;
            node->previous = previousCurrent;
            node->item = x;
            LinkedList<T, DeNode<T>>::sz++;
        } else {
            insert_head(x);
        }
    }

    void insert_middle(T &after, T &x) {
        if (!search(after)) {
            std::cerr << after << " Not Found\n";
        } else {
            DeNode<T> *current = LinkedList<T, DeNode<T>>::head;
            while (current != NULL) {
                if (current->item == after) {
                    auto node = new DeNode<T>;
                    node->item = x;
                    node->next = current->next;
                    node->previous = current;
                    current->next->previous = node;
                    current->next = node;
                    LinkedList<T, DeNode<T>>::sz++;
                    break;
                }
                current = current->next;
            }
        }
    }

    void insert_head(T &x) {
        if (!LinkedList<T, DeNode<T>>::sz) {
            LinkedList<T, DeNode<T>>::head = new DeNode<T>;
            LinkedList<T, DeNode<T>>::head->item = x;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head->next = NULL;
            LinkedList<T, DeNode<T>>::head->previous = NULL;
        } else {
            LinkedList<T, DeNode<T>>::head->previous = new DeNode<T>;
            LinkedList<T, DeNode<T>>::head->previous->next = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head = LinkedList<T, DeNode<T>>::head->previous;
            LinkedList<T, DeNode<T>>::head->item = x;
            LinkedList<T, DeNode<T>>::head->previous = NULL;
        }
        LinkedList<T, DeNode<T>>::sz++;
    }

    void erase_head() {
        DeNode<T> *current;
        current = LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::head = LinkedList<T, DeNode<T>>::head->next;
        delete current;
        LinkedList<T, DeNode<T>>::head->previous = NULL;
        LinkedList<T, DeNode<T>>::sz--;
    }

    void erase_tail() {
        DeNode<T> *current;
        current = LinkedList<T, DeNode<T>>::tail;
        LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::tail->previous;
        delete current;
        LinkedList<T, DeNode<T>>::tail->next = NULL;
        LinkedList<T, DeNode<T>>::sz--;
    }

    void erase_middle(T &x) {
        if (!search(x)) {
            std::cerr << "Element not Found\n";
            return;
        }
        DeNode<T> *current;
        current = LinkedList<T, DeNode<T>>::head->next;
        while (current != NULL) {
            if (current->item == x) {
                break;
            }
            current = current->next;
        }
        current->previous->next = current->next;
        current->next->previous = current->previous;
        delete current;
        LinkedList<T, DeNode<T>>::sz--;
    }

    bool search(T &x) {
        DeNode<T> *current = LinkedList<T, DeNode<T>>::head;
        while (current != NULL) {
            if (current->item == x)
                return true;
            current = current->next;
        }
        return false;
    }

    bool operator==(DLList<T> &obj) {
        if (LinkedList<T, DeNode<T>>::sz != obj.LinkedList<T, Node<T>>::size())
            return false;
        DeNode<T> *cur = LinkedList<T, DeNode<T>>::head;
        DeNode<T> *objCur = obj.LinkedList<T, Node<T>>::begin();
        while (cur != NULL) {
            if (cur->item != objCur->item)
                return false;
            cur = cur->next;
            objCur = objCur->next;
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, DLList<T> &o) {
        DeNode<T> *current = o.LinkedList<T, DeNode<T>>::head;
        if (!o.LinkedList<T, DeNode<T>>::size())
            std::cerr << "List is Empty\n";
        else {
            while (current->next != NULL) {
                os << current->item << "->";
                current = current->next;
            }
            os << current->item;
        }
        return os;
    }

    DLList<T> &operator=(const DLList<T> &obj) {
        DeNode<T> *current = obj.LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::sz = obj.LinkedList<T, DeNode<T>>::sz;
        LinkedList<T, DeNode<T>>::head = new DeNode<T>;
        LinkedList<T, DeNode<T>>::head->next = NULL;
        LinkedList<T, DeNode<T>>::head->previous = NULL;
        LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::head;
        while (current != NULL) {
            LinkedList<T, DeNode<T>>::tail->item = current->item;
            current = current->next;
            if (current == NULL)
                break;
            LinkedList<T, DeNode<T>>::tail->next = new DeNode<T>;
            LinkedList<T, DeNode<T>>::tail->next->previous = LinkedList<T, DeNode<T>>::tail;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::tail->next;
            LinkedList<T, DeNode<T>>::tail->next = NULL;
        }
        return *this;
    }

    DLList<T> &operator+=(const DLList<T> &obj) {
        DeNode<T> *current = obj.LinkedList<T, DeNode<T>>::head;
        while (current != NULL) {
            this->insert_tail(current->item);
            current = current->next;
        }
        return *this;
    }

    ~DLList() {
        DeNode<T> *cur = LinkedList<T, DeNode<T>>::head;
        while (cur != NULL) {
            LinkedList<T, DeNode<T>>::head = LinkedList<T, DeNode<T>>::head->next;
            delete cur;
            cur = LinkedList<T, DeNode<T>>::head;
        }
    }
};

template<typename T>
class CDLList : public LinkedList<T, DeNode<T>> {
public:
    CDLList() = default;

    CDLList(const CDLList<T> &obj) {
        DeNode<T> *current = obj.LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::sz = obj.LinkedList<T, DeNode<T>>::sz;
        LinkedList<T, DeNode<T>>::head = new DeNode<T>;
        LinkedList<T, DeNode<T>>::head->next = LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::head->previous = LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::head;
        while (current->next != obj.LinkedList<T, DeNode<T>>::head) {
            LinkedList<T, DeNode<T>>::tail->item = current->item;
            current = current->next;
            if (current == obj.LinkedList<T, DeNode<T>>::head)
                break;
            LinkedList<T, DeNode<T>>::tail->next = new DeNode<T>;
            LinkedList<T, DeNode<T>>::tail->next->previous = LinkedList<T, DeNode<T>>::tail;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::tail->next;
            LinkedList<T, DeNode<T>>::tail->next = LinkedList<T, DeNode<T>>::head;
        }
        LinkedList<T, DeNode<T>>::tail->item = current->item;
    }

    void insert_tail(T &x) {
        if (!LinkedList<T, DeNode<T>>::sz) {
            LinkedList<T, DeNode<T>>::head = new DeNode<T>;
            LinkedList<T, DeNode<T>>::head->item = x;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head->next = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head->previous = LinkedList<T, DeNode<T>>::head;
        } else {
            LinkedList<T, DeNode<T>>::tail->next = new DeNode<T>;
            LinkedList<T, DeNode<T>>::tail->next->previous = LinkedList<T, DeNode<T>>::tail;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::tail->next;
            LinkedList<T, DeNode<T>>::tail->item = x;
            LinkedList<T, DeNode<T>>::tail->next = LinkedList<T, DeNode<T>>::head;
        }
        LinkedList<T, DeNode<T>>::sz++;
    }

    void insert_middle(T &after, T &x) {
        if (!search(after)) {
            std::cerr << after << " Not Found\n";
        } else {
            DeNode<T> *current = LinkedList<T, DeNode<T>>::head;
            bool found = false;
            while (current->next != LinkedList<T, DeNode<T>>::head) {
                if (current->item == after) {
                    found = true;
                    auto node = new DeNode<T>;
                    node->item = x;
                    node->next = current->next;
                    node->previous = current;
                    current->next->previous = node;
                    current->next = node;
                    LinkedList<T, DeNode<T>>::sz++;
                    break;
                }
                current = current->next;
            }
            if (!found and current->item == after) {
                auto node = new DeNode<T>;
                node->item = x;
                node->next = current->next;
                node->previous = current;
                current->next->previous = node;
                current->next = node;
                LinkedList<T, DeNode<T>>::sz++;
            }
        }
    }

    void insert_sorted(T &x) {
        DeNode<T> *current = LinkedList<T, DeNode<T>>::head->next;
        DeNode<T> *previousCurrent = LinkedList<T, DeNode<T>>::head;
        if (previousCurrent->item <= x) {
            while (current->next != LinkedList<T, DeNode<T>>::head) {
                if (current->item <= x) {
                    current = current->next;
                    previousCurrent = previousCurrent->next;
                } else {
                    break;
                }
            }
            if (current->item <= x) {
                current = current->next;
                previousCurrent = previousCurrent->next;
            }
            auto node = new DeNode<T>;
            node->next = current;
            current->previous = node;
            previousCurrent->next = node;
            node->previous = previousCurrent;
            node->item = x;
            LinkedList<T, DeNode<T>>::sz++;
        } else
            insert_head(x);
    }

    void insert_head(T &x) {
        if (!LinkedList<T, DeNode<T>>::sz) {
            LinkedList<T, DeNode<T>>::head = new DeNode<T>;
            LinkedList<T, DeNode<T>>::head->item = x;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head->next = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head->previous = LinkedList<T, DeNode<T>>::head;
        } else {
            LinkedList<T, DeNode<T>>::head->previous = new DeNode<T>;
            LinkedList<T, DeNode<T>>::head->previous->next = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head = LinkedList<T, DeNode<T>>::head->previous;
            LinkedList<T, DeNode<T>>::head->previous = LinkedList<T, DeNode<T>>::tail;
            LinkedList<T, DeNode<T>>::head->item = x;
            LinkedList<T, DeNode<T>>::tail->next = LinkedList<T, DeNode<T>>::head;
        }
        LinkedList<T, DeNode<T>>::sz++;
    }

    void erase_head() {
        DeNode<T> *current;
        current = LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::head = LinkedList<T, DeNode<T>>::head->next;
        delete current;
        LinkedList<T, DeNode<T>>::head->previous = LinkedList<T, DeNode<T>>::tail;
        LinkedList<T, DeNode<T>>::tail->next = LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::sz--;
    }

    void erase_tail() {
        DeNode<T> *current;
        current = LinkedList<T, DeNode<T>>::tail;
        LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::tail->previous;
        delete current;
        LinkedList<T, DeNode<T>>::tail->next = LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::sz--;
    }

    void erase_middle(T &x) {
        if (!search(x)) {
            std::cerr << "Element not Found\n";
            return;
        }
        DeNode<T> *current;
        current = LinkedList<T, DeNode<T>>::head->next;
        while (current->next != LinkedList<T, DeNode<T>>::head) {
            if (current->item == x) {
                break;
            }
            current = current->next;
        }
        current->previous->next = current->next;
        current->next->previous = current->previous;
        delete current;
        LinkedList<T, DeNode<T>>::sz--;
    }

    bool search(T &x) {
        DeNode<T> *current = LinkedList<T, DeNode<T>>::head;
        while (current->next != LinkedList<T, DeNode<T>>::head) {
            if (current->item == x)
                return true;
            current = current->next;
        }
        if (current->item == x) {
            return true;
        }
        return false;
    }

    bool operator==(CDLList<T> &obj) {
        if (LinkedList<T, DeNode<T>>::sz != obj.LinkedList<T, Node<T>>::size())
            return false;
        DeNode<T> *cur = LinkedList<T, DeNode<T>>::head;
        DeNode<T> *objCur = obj.LinkedList<T, Node<T>>::begin();
        while (cur->next != LinkedList<T, DeNode<T>>::head) {
            if (cur->item != objCur->item)
                return false;
            cur = cur->next;
            objCur = objCur->next;
        }
        if (cur->item != objCur->item) {
            return false;
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, CDLList<T> &o) {
        DeNode<T> *current = o.LinkedList<T, DeNode<T>>::head;
        if (!o.LinkedList<T, DeNode<T>>::sz)
            std::cerr << "List is Empty\n";
        else {
            while (current->next != o.LinkedList<T, DeNode<T>>::head) {
                os << current->item << "->";
                current = current->next;
            }
            os << current->item;
        }
        return os;
    }

    CDLList<T> &operator=(const CDLList<T> &obj) {
        DeNode<T> *current = obj.LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::sz = obj.LinkedList<T, DeNode<T>>::sz;
        LinkedList<T, DeNode<T>>::head = new DeNode<T>;
        LinkedList<T, DeNode<T>>::head->next = LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::head->previous = LinkedList<T, DeNode<T>>::head;
        LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::head;
        while (current->next != obj.LinkedList<T, DeNode<T>>::head) {
            LinkedList<T, DeNode<T>>::tail->item = current->item;
            current = current->next;
            if (current == obj.LinkedList<T, DeNode<T>>::head)
                break;
            LinkedList<T, DeNode<T>>::tail->next = new DeNode<T>;
            LinkedList<T, DeNode<T>>::tail->next->previous = LinkedList<T, DeNode<T>>::tail;
            LinkedList<T, DeNode<T>>::tail = LinkedList<T, DeNode<T>>::tail->next;
            LinkedList<T, DeNode<T>>::tail->next = LinkedList<T, DeNode<T>>::head;
            LinkedList<T, DeNode<T>>::head->previous = LinkedList<T, DeNode<T>>::tail;
        }
        LinkedList<T, DeNode<T>>::tail->item = current->item;
        return *this;
    }

    CDLList<T> &operator+=(const CDLList<T> &obj) {
        DeNode<T> *current = obj.LinkedList<T, DeNode<T>>::head;
        while (current->next != LinkedList<T, DeNode<T>>::head) {
            this->insert_tail(current->item);
            current = current->next;
        }
        this->insert_tail(current->item);
        return *this;
    }

    ~CDLList() {
        DeNode<T> *cur = LinkedList<T, DeNode<T>>::head;
        while (LinkedList<T, DeNode<T>>::head != LinkedList<T, DeNode<T>>::tail) {
            LinkedList<T, DeNode<T>>::head = LinkedList<T, DeNode<T>>::head->next;
            delete cur;
            cur = LinkedList<T, DeNode<T>>::head;
        }
        delete cur;
    }
};

#endif //LINKED_LIST_LINKED_LIST_H
