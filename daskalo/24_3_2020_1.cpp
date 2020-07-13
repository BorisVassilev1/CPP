#include <iostream>
#include <cmath>
using namespace std;

const int MAX_N = 1e4;

int a[MAX_N];
int n;

int main() {
    cin >> n;
    int sum = 0;
    for(int i = 0; i < n; ++ i) {
        cin >> a[i];
        sum += a[i];
    }
    int x = sum / n;
    int ans = 0;
    for(int i = 0; i < n; ++ i) {
        if(a[i] > x) {
            int diff = a[i] - x;
            ans += diff;
        }
    }
    cout << ans << endl;
}
