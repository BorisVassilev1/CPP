#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int l, n;
    cin >> l >> n;
    int max_h = 0;
    int min_h = 2e9;
    int max_ind, min_ind;
    for(int i = 0; i < n; i ++) {
        int h;
        cin >> h;
        if(h > max_h) {max_h = h; max_ind = i;}
        if(h < min_h) {min_h = h; min_ind = i;}
    }
    float dist = (float)l / (n - 1);
    cout << abs(float(dist * max_ind - dist * min_ind));
}
