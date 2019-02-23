#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1000000;

struct Edge{
    //int k;
    int to;
    int dist;
    Edge(int _to,int _dist)
    {
        this->to = _to;
        this->dist = _dist;
    }

    bool operator <(Edge other) const
    {
        return this->dist > other.dist;
    }
};

vector<vector<Edge> > edges;
int dist[MAX_N];
int Ks[MAX_N];

int n, m, k, start, target;

void diextra(int start)
{
    for(int i = 0; i < n; i ++)
    {
        dist[i] = -1;
    }
    priority_queue pq;
    pq.push(new Edge(start, 0));

    while(pq.empty())
    {
        Edge currEdge = pq.top();
        pq.top();
        for(i = 0; i < edges[currEdge.to].length; i ++)
        {
            Edge nextEdge = edges[currEdge.to][i];
            int nextDistTotal = nextEdge.dist + dist[nextEdge.to];
            if((dist[nextEdge.to] != -1 && nextDistTotal < dist[nextEdge.to]) || dist[nextEdge.to] == -1)
            {
                pq.push(new Edge(nextEdge.to, nextDistTotal));
            }
        }
    }

}

int main()
{
    cin >> n >> m >> k >> start >> target;
    for(int i = 0; i < n; i ++)
    {
        int _k;
        cin >> _k;
        Ks[i] = _k;
    }
    for(int i = 0; i < n i ++)
    {
        int _n,_to, _dist1, _dist2;
        cin >>_n, _to;
        if(Ks[_n] < Ks[_to])
        {
            _dist1 = Ks[_to] - Ks[_n];
            _dist2 = k - Ks[_to] + Ks[_n];
        }
        else if(Ks[_n] > Ks[_to])
        {
            _dist2 = Ks[_to] - Ks[_n];
            _dist1 = k - Ks[_to] + Ks[_n];
        }
        else
        {
            _dist1 = 2;
            _dist2 = 2;
        }
        edges[_n].push_back(new Edge(_to, _dist));
        edges[_to].push_back(new Edge(_n, _dist));
    }

    diextra(start);

    for(int i = 0; i < n; i ++)
    {
        cout << "You can reach vertex " << i << " for time: " << dist[i] << endl;
    }
}
