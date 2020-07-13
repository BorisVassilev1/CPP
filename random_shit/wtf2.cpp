#include <iostream>

using namespace std;

int main() {
    int a[3] = {1, 2, 3}, *b, *c;
    for(b = a, c = a + 3; c > b; c --) cout << *--c;

}
