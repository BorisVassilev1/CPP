#include <iostream>

using namespace std;

const int MAX_N = 1e4;

int n, m;
bool a[MAX_N];

int main() {
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int begin, count;
        cin >> begin >> count;
        for(int j = 0; j < count; j ++) {
            a[begin + j - 1] = !a[begin + j - 1];
        }
    }
    for(int i = 0; i < n; ++ i) {
        cout << a[i] << " ";
    }
}
