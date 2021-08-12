#include <iostream>
using namespace std;

int MOD = 1e9 + 7;

long long fact(int a) {
    long long result = 1;
    while(a > 0) {
        result *= a;
        result %= MOD;
        --a;
    }
    //cout << result << " ";
    return result;
}

long long comb(int n, int k) {
    long long result = 1;
    int a = n - k;
    while(n > a) {
        result *= n;
        result %= MOD;
        --n;
    }
    result /= fact(k);
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << comb(n  + k -1,k - 1 );

}
