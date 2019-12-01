#include <iostream>

using namespace std;

int main() {
    int n;
    cout << "vavedi chislo:";
    cin >> n;
    int c = 0;
    while(n >= 1 || -n >= 1) {
        n /= 10;
        c ++;
    }
    if(n == 0) c = 1;
    cout << "Chisloto ima " << c << " cifri!";
}
