#include <iostream>
using namespace std;


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
        int from, to;
        cin >> from >> to;
        union1(from, to);
    }
}
