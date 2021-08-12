#include <iostream>

using namespace std;

int main() {
    float sum = 0;
    float in;
    while(cin >> in) {/// ako e vavedeno neshto.
        sum += in;
    }
    cout << sum;
}
