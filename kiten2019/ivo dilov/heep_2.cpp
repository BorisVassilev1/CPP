#include <iostream>
#include <queue>
using namespace std;

priority_queue<int> q;
priority_queue<int> q2;

int main() {
    int n;
    cin >> n;
    //q.push(-100000);
    //q2.push(100000);
    for(int i = 0; i < n; i ++) {
        char c;
        cin >> c;
        if(c == 'd') {
            int a;
            cin >> a;

            if(q.empty()) {q.push(a);}
            else if(q2.empty()) {q2.push(-a);}
            else {
            if(a > q.top()) {
                q2.push(-a);
            }
            else {
                q.push(a);
            }
            }

            if(q2.size() > q.size()) {
                int b = q2.top();
                q.push(-b);
                q2.pop();
            }
            else if(q.size() > q.size() + 1) {
                int b = q.top();
                q2.push(-b);
                q.pop();
            }
        }
        else {
            //cout << q.size() <<" "<< q2.size() << " " << q.top() << " " << q2.top()<< endl;
            cout << ((q.size() + q2.size()) % 2 == 0) ? (q.top() - q2.top() )/ 2 : q.top();
        }
    }

}
