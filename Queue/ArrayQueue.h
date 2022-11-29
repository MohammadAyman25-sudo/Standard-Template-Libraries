//
// Created by Mohammad Ayman on 4/22/2022.
//

#ifndef QUEUE_ARRAYQUEUE_H
#define QUEUE_ARRAYQUEUE_H

#include <iostream>

template<class Tp>
class ArrayQueue {
public:
    ArrayQueue() {
        first = last = -1;
        _size = 100;
        arr = new Tp[_size];
        cnt = 0;
    }

    ArrayQueue(int &&sz) {
        arr = new Tp[sz];
        _size = sz;
        cnt = 0;
        first = last = -1;
    }

    ArrayQueue(int &sz) {
        arr = new Tp[sz];
        _size = sz;
        cnt = 0;
        first = last = -1;
    }

    void enqueue(Tp &value) {
        if (!isFull()) {
            if (first == -1) {
                arr[++first] = value;
                last = first;
            } else {
                if (first != 0 and last == _size - 1) {
                    last %= _size;
                }
                arr[++last] = value;
            }
            cnt++;
        } else
            std::cerr << "Queue is Full";
    }

    void enqueue(Tp &&value) {
        if (!isFull()) {
            if (first == -1) {
                arr[++first] = value;
                last = first;
            } else {
                if (first != 0 and last == _size - 1) {
                    last %= _size;
                }
                arr[++last] = value;
            }
            cnt++;
        } else
            std::cerr << "Queue is Full";
    }

    Tp &dequeue() {
        int tmp = first;
        if (first == last) {
            first = last = -1;
        } else
            first++;
        cnt--;
        return arr[tmp];
    }

    bool isFull() { return ((first == 0 and last == _size - 1) or (last == first - 1)); }

    bool isEmpty() { return (first == -1); }

    int size() const { return cnt; }

    Tp &front() const { return arr[first]; }

    Tp &back() const { return arr[last]; }

    void initializeArray() {
        first = last = -1;
        cnt = 0;
    }

    ~ArrayQueue() {
        delete[]arr;
    }

private:
    Tp *arr;
    int first, last, _size, cnt;
};

#endif //QUEUE_ARRAYQUEUE_H
