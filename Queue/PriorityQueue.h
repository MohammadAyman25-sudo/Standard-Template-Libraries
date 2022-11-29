//
// Created by ayman on 4/23/2022.
//

#ifndef QUEUE_PRIORITYQUEUE_H
#define QUEUE_PRIORITYQUEUE_H

#include <cstdlib>

template<class Tp>
class Node {
public:
    Node<Tp> *prev;
    Tp info;
    int priority;
    Node<Tp> *next;

    Node() {
        priority = 0;
        next = NULL;
        prev = NULL;
        info = NULL;
    }
};

template<class Tp>
class priority_queue {
public:
    priority_queue() {
        first = NULL;
        last = NULL;
        _size = 0;
        pri = 0;
    }

    class iterator {
        Node<Tp> *node;
    public:
        iterator() = default;

        iterator(Node<Tp> *obj) {
            node = obj;
        }

        iterator &operator++(int) {
            iterator *tm = this;
            node = node->next;
            return *tm;
        }

        iterator &operator++() {
            node = node->next;
            return *this;
        }

        iterator &operator--(int) {
            iterator *tm = this;
            node = node->prev;
            return *tm;
        }

        iterator &operator--() {
            node = node->prev;
            return *this;
        }

        Tp &operator*() {
            return node->info;
        }

        iterator &operator=(const iterator &obj) {
            this->node = obj.node;
            return *this;
        }

        bool operator==(const iterator &obj) {
            return (node == obj.node);
        }

        bool operator!=(const iterator &obj) {
            return (node != obj.node);
        }
    };

    void push(Tp &x, int prt = 0) {
        if (!_size) {
            first = new Node<Tp>;
            first->info = x;
            last = first;
            first->priority = std::max(++pri, prt);
        } else {
            Node<Tp> *cur = first;
            auto *new_node = new Node<Tp>;
            new_node->info = x;
            if (!prt)
                prt = pri++;
            new_node->priority = prt;
            for (; cur != NULL; cur = cur->next) {
                if (cur->priority > prt) {
                    break;
                }
            }
            if (cur != NULL) {
                new_node->next = cur;
                new_node->prev = cur->prev;
                cur->prev->next = new_node;
                cur->prev = new_node;
            } else {
                last->next = new_node;
                new_node->prev = last;
                last = last->next;
            }
        }
        _size++;
    }

    void push(Tp &&x, int prt = 0) {
        if (!_size) {
            first = new Node<Tp>;
            first->info = x;
            last = first;
            first->priority = std::max(++pri, prt);
        } else {
            Node<Tp> *cur = first;
            auto *new_node = new Node<Tp>;
            new_node->info = x;
            if (!prt)
                prt = ++pri;
            new_node->priority = prt;
            for (; cur != NULL; cur = cur->next) {
                if (cur->priority > prt) {
                    break;
                }
            }
            if (cur != NULL) {
                if (cur->prev != NULL) {
                    new_node->next = cur;
                    new_node->prev = cur->prev;
                    cur->prev->next = new_node;
                    cur->prev = new_node;
                } else {
                    new_node->next = cur;
                    cur->prev = new_node;
                    first = first->prev;
                }
            } else {
                last->next = new_node;
                new_node->prev = last;
                last = last->next;
            }
        }

        _size++;
    }

    void pop() {
        first = first->next;
        delete first->prev;
        first->prev = NULL;
        _size--;
    }

    Tp &front() { return first->info; }

    Tp &back() { return last->info; }

    int size() const { return _size; }

    iterator begin() {
        iterator tm;
        tm = iterator(first);
        return tm;
    }

    iterator end() {
        iterator tm;
        tm = iterator(last->next);
        return tm;
    }

    ~priority_queue() {
        auto cur = first;
        while (cur != NULL) {
            first = first->next;
            delete cur;
            cur = first;
        }
    }

private:
    Node<Tp> *first;
    Node<Tp> *last;
    int _size;
    int pri;
};

#endif //QUEUE_PRIORITYQUEUE_H
