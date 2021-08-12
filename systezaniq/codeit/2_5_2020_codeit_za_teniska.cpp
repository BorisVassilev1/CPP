#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int main() {

    ifstream in;
    in.open("exercise.in");

    ofstream out;
    out.open("exercise.out");

    int n;
    cin >> n;

    int _sqrt = sqrt(n * 2);
    cout << _sqrt  << " " << _sqrt - 1 << endl;
    int most = _sqrt * (_sqrt + 1) / 2;
    if(n > most) cout << _sqrt + 1;
    else cout << _sqrt;

}
