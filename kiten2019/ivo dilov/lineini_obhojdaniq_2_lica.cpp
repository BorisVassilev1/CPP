#include <iostream>
#include <stack>
using namespace std;

stack<pair<int, int> > s;/// first -> value, second -> index
int n, m;
int a[1000];
int result[1000]; /// first -> nazad; second -> napred;

int main() {
    cin >> n;
    cin >> m;
    for(int i = 0; i < n; ++ i) {
        cin >> a[i];
    }
    s.push({100000000,-1});
    for(int i = 0; i < n; ++ i) {
        pair<int, int> curr = {a[i],i};
        while(!s.empty() && s.top().first <= curr.first) {s.pop();}
        int res = curr.second - s.top().second - 1;
        result[i] = res;
        s.push(curr);
    }
    s = *(new stack<pair<int, int> >());
    s.push({100000000,n});
    for(int i = n - 1 ; i >= 0; -- i) {
        pair<int, int> curr = {a[i],i};
        while(!s.empty() && s.top().first <= curr.first) {s.pop();}
        int res = - curr.second + s.top().second - 1;
        result[i] += res;
        s.push(curr);
    }
    int best = 0;
    for(int i = 0; i < n; ++ i) {
        int face = (result[i] + 1) * (m - a[i]);
        if(face > best) {best = face;}
    }
    cout << best;
}
/*
11 8
2 3 6 1 0 2 0 5 3 2 1


7 4
1 0 2 3 1 1 0
*/
