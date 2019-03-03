#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int MAX_N = 100000;

struct Edge
{
    int from, to, dist;
    Edge(int _from, int _to, int _dist)
    {
        from = _from;
        to = _to;
        dist = _dist;
    }

    /*string toString()
    {
        string a = "from: " + from + " to: " + to + " dist: " + dist;
        return a;
    }*/
};

vector<Edge> edges;

bool cmp(Edge first, Edge second)
{
    return first.dist < second.dist;
}

int parent[MAX_N];
int tree_size[MAX_N];

int find1(int a)
{
    if(a == parent[a])
    {
        return a;
    }
    return parent[a] = find1(parent[a]);
}

void union1(int a, int b)
{
    int pa = find1(a);
    int pb = find1(b);
    if(pa == pb)
    {
        return;
    }
    if(tree_size[pa] > tree_size[pb])
    {
        swap(pa, pb);
    }
    parent[pa] = pb;
    tree_size[pb] += tree_size[pa];
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n = 5;
    int m;
    cin >> n;
    cin >> m;
    fill(tree_size, tree_size + n, 1);

    for(int i = 0; i < n; i ++)
    {
        parent[i] = i;
    }
    for(int i = 0; i < m; i ++)
    {
        int from, to, dist;
        cin >> from >> to >> dist;
        edges.push_back({from, to, dist});
    }
    sort(edges.begin(), edges.end(), cmp);
    long long sum = 0;
    for(int i = 0; i < m; i ++)
    {
        if(find1(edges[i].from) != find1(edges[i].to))
        {
            union1(edges[i].from, edges[i].to);
            cout << "from: " << edges[i].from << " to: " << edges[i].to << " dist: " << edges[i].dist << endl;
            sum += edges[i].dist;
        }
    }
    cout << sum;
}
