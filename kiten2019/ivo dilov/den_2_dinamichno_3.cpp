#include <iostream>
using namespace std;

int result[5000][5000];
int nums[5000];
///ne raboti. koda na ivo e na emaila mi
int main() {
    int n, m, k;
    cin >> n >> m >> k;

    for(int i = 0; i < n; i ++) {
        cin >> nums[i];
    }
    cout << endl;
    int curr_sum1 = 0;
    for(int i = 0; i <= n; i ++) {
        curr_sum1 += nums[i];
        result[0][i] = curr_sum1 <= k ? 1 : 0;
    }
    delete &curr_sum1;

    for(int i = 1; i <= m; i ++) {
        int pointer = 0;
        int curr_sum = 0;
        for(int j = 0; j <= n; j ++) {
            result[i][j] = result[i - 1][j] + (j > 0 ? result[i][j - 1] : 1);
            curr_sum += nums[j];
            while(curr_sum > k) {
                result[i][j] -= result[i-1][pointer];
                curr_sum -= nums[pointer];
                pointer ++;
            }
        }
    }

    for(int i = 0; i <= m; i ++) {
        for(int j = 0; j <= n; j ++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

}
/*

8 4 12
8 3 1 5 4 9 1 6
*/
/*
9 3 17
1 5 9 2 7 6 8 3 2
*/
