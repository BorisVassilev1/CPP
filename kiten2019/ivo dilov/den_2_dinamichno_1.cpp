#include <iostream>
using namespace std;

int result[5000][5000];

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i < n + 1; i ++) {
        result[i][1] = i <= k ? 1 : 0;
    }
    //result[0][2] = 1;
    for(int vazi = 2; vazi < m + 1; vazi ++) {
        for(int kamuni = 0; kamuni < n + 1; kamuni ++) {
            result[kamuni][vazi] = (kamuni > 0 ? result[kamuni - 1][vazi] + result[kamuni][vazi-1] : 1);
            if(kamuni > k) {
                result[kamuni][vazi] -= result[kamuni - k - 1][vazi - 1];
            }
        }
    }
    cout << result[n][m] << endl;
    /*for(int i = 0; i < m + 1; i ++) {
        for(int j = 0; j < n + 1; j ++) {
            cout << result[j][i] << " ";
        }
        cout << endl;
    }*/
}
