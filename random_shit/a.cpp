#include <iostream>
#include <algorithm>
using namespace std;

const int N = 15;

int a[N];

int main() {

    for(int i = 0; i < N; i ++) {
        cin >> a[i];
    }
    sort(a, a + N);
    for(int i = 0; i < N; i ++) {
        cout << a[i] << " ";
    }
    cout << endl;
    int last = -1;
    int uniquesum = 0;
    int uniquecount = 0;
    for(int i = 0; i < N; i ++) {
        if(a[i] != last) {
            last = a[i];
            uniquesum += last;
            uniquecount ++;
            cout << last << " " << uniquesum << endl;
        }
    }
    float mean = uniquesum / (float)uniquecount;
    cout << uniquesum << " " << uniquecount << " " << mean;
}
