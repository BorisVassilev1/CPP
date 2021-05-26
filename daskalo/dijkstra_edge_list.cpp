#include <iostream>
#include <queue>

const int MAX_N = 1e5+10;
const int MAX_M = MAX_N;

struct Edge{
    int from;
    int to;
    long long len;
    Edge* next;
};

struct p{
    long long len;
    int to;

    bool operator <(const p &other) const {
        return len > other.len;
    }
};

Edge edges[2*MAX_M];
Edge *first_from[MAX_N];
int edges_count = 0;

long long dist[MAX_N];
int prev[MAX_N];

int route[MAX_N];
int route_length = 0;


int n, m;

void add_edge(int from, int to, int len) {
    edges[edges_count] = {from, to, len, first_from[from]};
    first_from[from] = edges + edges_count;
    ++edges_count;
}

void dijkstra(int start) {
    std::priority_queue<p> q;

    for(int i = 0; i < n; i ++) dist[i] = -1;

    q.push({0, start});
    dist[start] = 0;

    while(!q.empty()) {
        auto curr = q.top();
        q.pop();

        if(curr.to == n-1) return;

        Edge *e = first_from[curr.to];
        while(e != 0) {
            long long d = curr.len + e->len;
            if(dist[e->to] == -1 || dist[e->to] > d) {
                q.push({d, e->to});
                dist[e->to] = d;
                prev[e->to] = curr.to;
            }
            e = e->next;
        }
    }
}

int main() {
    std::cin >> n >> m;
    int from, to, len;
    for(int i = 0; i < m; i ++) {
        std::cin >> from >> to >> len;
        add_edge(from-1, to-1, len);
        add_edge(to-1, from-1, len);
    }

    dijkstra(0);

    if(dist[n-1] == -1) {
        std::cout << -1;
    } else {
        int curr = n-1;
        while(curr != 0) {
            route[route_length++] = curr;
            curr = prev[curr];
        }
        for(int i = route_length; i >= 0; i--) {
            std::cout << route[i]+1 << " ";
        }
    }
}
