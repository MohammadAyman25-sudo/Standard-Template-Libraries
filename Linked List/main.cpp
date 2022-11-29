#include <iostream>
#include <conio.h>
#include "Linked_List.h"

using namespace std;

int main() {
    List<int> l;
    int x = 5;
    l.insert_tail(x);
    x = 10;
    l.insert_tail(x);
    x = 6;
    l.insert_sorted(x);
    cout << l.size() << endl;
    cout << l << endl;
    x = 4;
    l.insert_sorted(x);
    cout << l << endl;
    l.clear();
    cout<<l<<endl;
    _getch();
    return 0;
}
