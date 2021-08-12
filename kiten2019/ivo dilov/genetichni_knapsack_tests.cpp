#include <iostream>
#include <fstream>
using namespace std;

int main() {
    srand(69);
    ofstream out("genetichni_knapsack_tests.txt");
    int n = 10000;
    out << n << endl;
    int sum = 0;
    for(int i = 0; i < n; i ++) {
        int price = rand();
        int vol = rand();
        sum += vol;
        out << price << " " << vol << endl;
    }
    out << sum / 3;
}
