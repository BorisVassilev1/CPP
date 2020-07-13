#include <iostream>
#include <stack>
using namespace std;

const int MAX_N = 1e4;

int n;
stack<int> s;

int main() {
    cin >> n;
    for(int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        if(s.empty()) {
            s.push(x);
            //cout << "pushing " << x << endl;
        }
        else {
            while(!s.empty() && s.top() < x) {
                //cout << "popping " << s.top() << endl;
                s.pop();
            }
            s.push(x);
            //cout << "pushing " << x << endl;
        }
    }
    cout << s.size();
}

