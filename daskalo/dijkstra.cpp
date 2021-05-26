/// raboti, no dava memory limit na test 31.

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int MAX_N = 1e5;

struct edge{
    int to;
    int distance;

    edge(int to, int distance): to(to), distance(distance){}

    bool operator < (const edge& other) const {
        return distance > other.distance;
    }
};

vector<edge> graph[MAX_N];
int d[MAX_N];
int f[MAX_N];

stack<int> route;

int dijkstra(int start, int n) {
    priority_queue<edge> q;
    for(int i = 0; i < n; i ++) d[i] = -1;

    q.push({start,0});
    d[start] = 0;
    while(!q.empty()) {
        auto curr = q.top();
        if(curr.to == n-1) break;
        q.pop();
        for(int i = 0; i < graph[curr.to].size(); i++) {
            edge e = graph[curr.to][i];
            int dist = curr.distance + e.distance;
            if(d[e.to] == -1 || d[e.to] > dist) {
                q.push({e.to, dist});
                d[e.to] = dist;
                f[e.to] = curr.to;
            }
        }
    }
}

int main() {
    int n;
    int m;
    cin >> n >> m;
    for(int i = 0; i < m; i ++) {
        int from, to, w;
        cin >> from >> to >> w;
        from --;
        to --;
        graph[from].push_back(edge(to, w));
        graph[to].push_back(edge(from, w));
    }

    dijkstra(0, n);
    //for(int i = 0; i < n; i ++) {
    //    graph[i].clear();
    //}

    if(d[n-1] == -1)
        cout << -1;
    else {
        int curr = n-1;
        while(curr != 0) {
            route.push(curr);
            curr = f[curr];
        }

        cout << 1 << " ";
        while(!route.empty()) {
            cout << route.top() + 1 << " ";
            route.pop();
        }
    }
}
