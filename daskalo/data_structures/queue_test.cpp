#include <iostream>
#include "queue.cpp"

using namespace std;

int main() {
    queue<int> q;

    cout << q.empty() << endl;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    cout << q.size() << endl << endl;
    q.push(5);
    q.push(6);
    q.push(7);
    q.push(8);

    while(!q.empty()) {
        cout << q.front() << " " << flush;
        q.pop();
    }
    cout << endl;
}

