#include <iostream>
using namespace std;

long long m, n;

int main() {
    cin >> n >> m;
    if((n-m)%3 == 0)
        cout << "gubeshta";
    else
        cout << "pechelifsha";
}
