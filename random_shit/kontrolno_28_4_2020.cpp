#include <iostream>
using namespace std;

const int MAX_N = 10000;

int a[N];
int N;
int M;

int main() {
    cin >> N;
    long sum = 0;
    for(int i = 0; i < N; i ++) {
        cin >> a[i];
        sum += a[i];
    }
    cin >> M;

    double mean = (double)sum / N;

    for(int i = 0; i < N; i ++) {
        if(a[i] < mean) a[i] -= M;
        else if(a[i] > mean) a[i] += M;
        cout << a[i] << " ";
    }
    cout << endl;

}
