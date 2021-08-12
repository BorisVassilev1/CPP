#include <iostream>
using namespace std;

int *expand(int *old, int &n) {
    int *new_blok = new int[n*2];
    for (int i=0 ;i<n; i++ ) new_blok[i] = old[i];
    delete [] old;
    n*=2;
    return new_blok;
}
int main() {
    int i=0, n;
    cin>>n;
    int n_copy = n;
    int *A = new int[n];
    while (true){
        cin >> A[i];
        if(A[i] == 0) break;

        i ++;
        if (i==n) {
            A = expand(A,n);
        }
    }
    int counter = 0;
    for(int j = i - n_copy; j < i; j ++) {
        if(A[j] % 5 == 0) {
            counter ++;
        }
    }
    cout << counter;
    delete [] A;
    return 0;
}
