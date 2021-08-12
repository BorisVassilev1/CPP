#include <iostream>
#include <math.h>
using namespace std;

int n, m;
int i [5120],j[5120];
int dp[2][5120];

int d(int a, int b) {
return abs(a - b);
}

int main() {
    cin >> n >> m;
    for(int k = 0; k < m; ++k) {
        cin >> i[k] >> j[k];
        --i[k];
        --j[k];
    }
    for(int k = 0; k < n; ++k) {
        dp[0][k] = d(i[0],j[0]);
    }
    for(int k = 1; k < m; ++k) {
        for(int l =0; l < n; ++l) {dp[k%2][l] = -1;}
        for(int l = 0; l < n; ++l) {
            ///dp[k-1][l] -> dp[k][l]
            int cans = dp[(k-1)%2][l] + d(j[k-1], i[k]) + d(i[k], j[k]);
            if(dp[k%2][l] == -1 || cans < dp[k%2][l]) dp[k%2][l] = cans;
            ///dp[k-1][l] -> `dp[k][j[k-1]]
            cans = dp[(k-1)%2][l] + d(l, i[k]) + d(i[k], j[k]);
            if(dp[k%2][j[k-1]] == -1 || cans < dp[k%2][j[k-1]]) dp[k%2][j[k-1]] = cans;
        }
    }
    int ans = dp[(m-1)%2][0];
    for(int k = 1; k < n; k ++) {
        ans = min(ans,dp[(m-1)%2][k]);
    }

    cout << ans;

}


