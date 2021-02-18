#include <iostream>

using namespace std;

int main () {
    int b, num, sum = 0, c = 0;
    cin >> b;

    do {
        cin >> num;
        c ++;
        if(num % 4 == 0) {
            sum += num;
        }
    } while(sum <= b);
    cout << c;
}

