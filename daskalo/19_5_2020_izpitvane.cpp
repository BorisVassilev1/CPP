#include <iostream>
using namespace std;

int f(unsigned int a) {
    int k = 1;
    while(k < a) {
        k *= 10;
    }
    if(k == 1) return 1;
    k/= 10;
    return a / k;
}

int main() {
    int n = -1;
    int _count = 0;
    while(n != 0) {
        cin >> n;
        int k = f(n);
        if(k == 6) ++ _count;
    }
    cout << _count;
}
