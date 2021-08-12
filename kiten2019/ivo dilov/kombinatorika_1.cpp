#include <iostream>
using namespace std;
int MOD = 1e9+7;

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

int main() {
    int a, b,c;
    cin >> a >> b >> c;
    long long ans =  fact(a + b + c);
    ans /= fact(a);
    ans /= fact(b);
    ans /= fact(c);
    cout << ans;
}
