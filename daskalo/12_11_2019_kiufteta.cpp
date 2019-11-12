#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    if(n > 10000) cout << 1 << endl;
    else{
        int k = (10000 - n) / 2 + 2;
        cout << k << endl;
        cout << (2 * n + (k-2)*2) * (k-1) / 2 + 10001 << endl;
    }
}
