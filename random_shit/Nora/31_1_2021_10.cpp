#include <iostream>

using namespace std;

int main() {
    int c = 0, curr, prev;
    do {
        prev = curr;
        cin >> curr;
        c ++;
    } while(curr != prev || c == 1);

    cout << c;
}

