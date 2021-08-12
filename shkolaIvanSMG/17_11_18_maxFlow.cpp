#include <iostream>
#include <vector>
#include <queue>
using namespace std;
/*
max_flow = min_cut!!

max_flow = matching!!
*/

struct edge{
  int to;
  int prev;
  int cap;
};

const int maxint = 1<<30;

int n, m;
vector<edge> e;
int last[100200];

void addEdge(int from, int to, int cap){
  e.push_back({to, last[from], cap});
  last[from] = e.size()-1;
  e.push_back({from, last[to], cap});
  last[to] = e.size()-1;
}

bool used[100200];
int d[100200];

bool bfs(int from, int to){
  queue<int> q;
  for (int i=0; i<n; ++i) d[i]=0;
  d[from] = 1;
  q.push(from);
  while(!q.empty()){
    int curr = q.front();
    q.pop();
    if (curr == to) return 1;
    for (int i=last[curr]; i>-1; i=e[i].prev){
      if (!d[e[i].to] && e[i^1].cap){
        d[e[i].to] = d[curr]+1;
        q.push(e[i].to);
      }
    }
  }
  return 0;
}

int dfs(int from, int to, int flow){
  used[from] = 1;
  if (from == to) return flow;
  for (int i=last[from]; i>-1; i=e[i].prev){
    if (!used[e[i].to] && e[i].cap > 0 && d[e[i].to] == d[from]-1){
      int curr = dfs(e[i].to, to, min(flow, e[i].cap));
      if (curr > 0){
        e[i].cap -= curr;
        e[i^1].cap += curr;
        return curr;
      }
    }
  }
  return 0;
}

int find_flow(int source, int sink){
  int ans = 0;
  while(bfs(sink, source)){
    //cout<<ans<<"\n";
    for (int i=0; i<n; ++i) used[i]=0;
    int curr;
    do{
      curr = dfs(source, sink, maxint);
      ans += curr;
    }while(curr);
  }
  return ans;
}

int main(){
  cin>>n>>m;
  for (int i=0; i<n; ++i) last[i]=-1;
  for (int i=0; i<m; ++i){
    int a, b, c;
    cin>>a>>b>>c;
    addEdge(a, b, c);
  }
  cout<<find_flow(0, n-1)<<"\n";
  return 0;
}
