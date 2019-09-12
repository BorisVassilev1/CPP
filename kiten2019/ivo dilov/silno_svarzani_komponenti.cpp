#include <iostream>
#include <vector>
using namespace std;

vector<int> v[1000];
int n;
int m;

int counter = 0;
int sorted[1000];
bool seen[1000];

void dfsA(int i) {
    seen[i] = true;
    for(int j = 0; j < v[i].size(); ++ j){if(!seen[v[i][j]])dfsA(v[i][j]);}
    sorted[counter] = i;
    counter ++;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i ++) {
        int from, to;
        cin >> from >> to;
        v[from].push_back(to);
    }
    while(counter < n - 1)dfsA(counter);


    for(int i = 0; i < n; i ++) {
        cout << sorted[i] << " ";
    }
}
/*
13 18
0 2
1 0
1 3
3 4
4 1
2 3
2 7
6 7
7 9
9 6
11 9
11 12
12 11
5 2
5 8
10 5
8 10
4 11
*/
