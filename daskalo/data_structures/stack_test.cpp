#include <iostream>
#include "stack_array.cpp"

using namespace std;

int main() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);    
    s.push(4);
    s.push(4);
    s.push(4);
    s.push(4);
    s.push(4);
    cout << s.size() << endl << endl;
    
    while(!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }
    
    cout << endl << s.size() << endl;
}
