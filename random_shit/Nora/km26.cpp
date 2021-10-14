#include <iostream>
using namespace std;
int main () {
    int N,X;
    cin >> X >>N;
    bool sus = false;
    int n[100];
    for (int i=0; i<N; i++) {
        cin >> n[i];
    }
    for (int i=0; i<N; i++) {
        if (n[i] == X && n[i+1] == X ) {
            sus=true;
        }
    }
    if(sus==true) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}
