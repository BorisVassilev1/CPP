#include <iostream>

using namespace std;

const int MAX_N = 300000;

int num[MAX_N];

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin.tie();
    cout.tie();

    int n, r;
    cin >> n >> r;
    for(int i = 0; i < n; ++i) {
        cin >> num[i];
    }
    int p1 = 0;
    int p2 = 1;
    long long count = 0;
    while(true) {
        if(num[p2] - num[p1] <= r) {
            ++p2;
            if(p2 == n) break;
        }
        else {
            count += n - p2;
            ++p1;
            if(num[n-1] - num[p1] <= r) break;
        }
    }
    cout << count;
}
