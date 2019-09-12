#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int exor = 0;
    for(int i = 0; i < m; i ++) {
        int black, white;
        cin >> black >> white;
        int dist = abs(black - white) - 1;
        exor ^= dist;
    }
    if(exor == 0) {cout << "vtoriq";}
    else {cout << "purviq";}
}
