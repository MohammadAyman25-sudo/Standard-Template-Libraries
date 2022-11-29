#include <iostream>
#include "PriorityQueue.h"

using namespace std;

int main() {
    priority_queue<int> q;
    q.push(10, 3);
    q.push(5, 2);
    cout << q.front() << endl;
    q.pop();
    q.push(15, 1);
    q.push(7, 3);
    cout << q.front() << endl;
    q.pop();
    q.push(13);
    cout << q.front() << endl;
    return 0;
}
