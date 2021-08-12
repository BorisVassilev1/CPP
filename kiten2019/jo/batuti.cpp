#include <iostream>

using namespace std;

int batuti[1000000];
int n;
int m;
int ans[1000000]

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i ++) {
        cin >> batuti[i];
    }

    ///precompute

    for(int i = 0; i < m; i ++) {
        int a;
        cin >> a;
        if(a == 0) {

        }
        else{
            int b;
            cin >> b;
            cin >> batuti[b];
        }
    }
}
