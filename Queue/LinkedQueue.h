//
// Created by ayman on 4/22/2022.
//

#ifndef QUEUE_LINKEDQUEUE_H
#define QUEUE_LINKEDQUEUE_H

#include <list>
#include <iostream>

template<class t>
class Node {
public:
    Node<t> *prev = NULL;
    t info = NULL;
    Node<t> *next = NULL;
};

template<class Tp>
class queue {
public:
    queue() {
        first = NULL;
        last = NULL;
        _size = 0;
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

    void push(Tp &&x) {
        if (!_size) {
            first = new Node<Tp>;
            first->info = x;
            last = first;

        } else {
            last->next = new Node<Tp>;
            last->next->prev = last;
            last->next->info = x;
            last = last->next;
        }
        _size++;
    }

    void push(Tp &x) {
        if (!_size) {
            first = new Node<Tp>;
            first->info = x;
            last = first;

        } else {
            last->next = new Node<Tp>;
            last->next->prev = last;
            last->next->info = x;
            last = last->next;
        }
        _size++;
    }

    void pop() {
        if (!_size)
            throw "Empty Queue";
        if (_size - 1 == 0) {
            delete first;
            first = NULL;
        } else {
            first = first->next;
            delete first->prev;
            first->prev = NULL;
        }
        _size--;
    }

    std::size_t size() { return _size; }

    bool empty() { return first == NULL; }

    Tp &front() { return first->info; }

    Tp &back() { return last->info; }

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

    ~queue(){
        Node<Tp> *cur = first;
        while(cur != NULL){
            first = first->next;
            delete cur;
            cur = first;
        }
    }
private:
    Node<Tp> *first;
    Node<Tp> *last;
    int _size;
};

#endif //QUEUE_LINKEDQUEUE_H
