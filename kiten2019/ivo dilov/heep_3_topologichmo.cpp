#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> a[10000];
int counters[10000];
priority_queue<int> q;
int n, m;

int main() {
    cin >> n >> m;

    for(int i = 0; i < m; i ++) {
        int from, to;
        cin >> from >> to;
        a[from].push_back(to);
        counters[to]++;
    }
    for(int i = 0; i < n; i ++) {
        if(counters[i] == 0) {
            //cout << i << " ";
            q.push(-i);
        }
    }
    //cout << endl;
    while(!q.empty()) {
        int v = -q.top();
        cout << v << " " ;///<< q.size() << endl;
        q.pop();

        for(int i = 0; i < a[v].size(); i ++) {
            if((--counters[a[v][i]]) == 0) {
                q.push(-a[v][i]);
            }
        }
    }
}
/*
5 6
0 5
4 0
1 5
2 4
2 1
3 1
*/
