#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int Nmax = 100000;

vector<int> graph[Nmax+1];
int d[Nmax+1];

int N, M, C, K;
int count_per = 0;

void input(){
  int u,v;
  scanf("%d %d %d %d",&N, &M, &C, &K);
  for (int i=1; i<=M; i++){
    scanf("%d %d",&u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  for (int i=1;i<=N;i++)
     d[i]=-1;
}

void BFS(int vbeg) {
  int u, v;
  queue<int> q;
  q.push(vbeg);
  d[vbeg] = 0;
  while (!q.empty()){
    u = q.front();
    q.pop();
    for (int i=0;i<graph[u].size();i++){
        v = graph[u][i];
        if (d[v] == -1){
            d[v] = d[u]+1;
            q.push(v);
            if (d[v]>K) count_per++;
        }
    }
  }
}

void output(){

  printf("%d\n", count_per);
  for (int i=1;i<=N;i++)
    if (d[i]>K)
      printf("%d\n", i);
}

int main() {
  input();
  BFS(C);
  output();
  return 0;
}


