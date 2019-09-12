#include <iostream>
using namespace std;


int main() {
    int n;
    cin >> n;
    int k = n - 1;
    int ans = (k * (k + 1) / 2 + k * (k + 1) * (2 * k + 1) / 6) / 2 + k;
    cout << ans + 2;

}
