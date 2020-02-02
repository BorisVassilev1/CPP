/**
 *  Igra. mestim pionka v graf samo v sasedni poleta.
 *  Guubi tozi, koito ne moje da napravi hod (nabutan e v listo)
 *  pravim oilerovo obhojdane. pri vsqka promqna se zasqga samo 2 vurha. Tqh gi preizchislqvame.
 *  O(N + 4M) dfs1 + obhojdane na vurhove
*/

/**
5 4
1 2
1 3
2 4
2 5
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 2e5;
vector<int> neigh[MAX_N];
int n, m;

bool isWin[MAX_N];
bool ansWin[MAX_N];

bool visited1[MAX_N];
bool dfs1(int index) {
    visited1[index] = true;
    bool isThisWin = false;
    for(int i = 0; i < neigh[index].size(); ++i) {
        if(!visited1[neigh[index][i]]) {
            bool a = dfs1(neigh[index][i]);
            if(a == false) isThisWin = true;
        }
    }
    isWin[index] = isThisWin;
    return isThisWin;
}

void recalculate(int v1, int v2) {
    bool isWin1 = false;
    for(int i = 0; i < neigh[v1].size(); ++ i) {
        if(neigh[v1][i] != v2) {
            if(!isWin[neigh[v1][i]]) isWin1 = true;
        }
    }
    bool isWin2 = false;
    for(int i = 0; i < neigh[v2].size(); ++ i) {
        if(!isWin[neigh[v2][i]]) isWin2 = true;
    }
    isWin[v1] = isWin1;
    isWin[v2] = isWin2;
}

bool visited2[MAX_N];
void dfs2(int prev, int curr) {
    ///recalculate from prev to curr
    if(curr != 0) {
        recalculate(prev, curr);
    }
    //cout << curr;
    ansWin[curr] = isWin[curr];

    visited2[curr] = true;
    for(int i = 0; i < neigh[curr].size(); ++ i) {
        if(!visited2[neigh[curr][i]]) {
            dfs2(curr, neigh[curr][i]);
            //cout << curr;
        }
    }
    ///recalculate from curr to prev
    if(curr != 0) {
        recalculate(curr, prev);
    }

}

int main() {
    ///     in
    cin >> n;
    cin >> m;
    for(int i = 0; i < m; ++ i) {
        int from, to;
        cin >> from >> to;
        from --;
        to --;
        neigh[from].push_back(to);
        neigh[to].push_back(from);
    }

    dfs1(0);
    dfs2(0,0);

    /*cout << 0;
    visited2[0] = true;
    for(int i = 0; i < neigh[0].size(); ++ i) {
        dfs2(0, i);
    }*/
    cout << endl;
    for(int i = 0; i < n; i ++) {
        cout << !ansWin[i] << " ";
    }
}
