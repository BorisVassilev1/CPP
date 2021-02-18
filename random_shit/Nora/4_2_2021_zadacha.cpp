#include <iostream>
using namespace std;
int main () {
    int N;
    cin >> N;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if((j+i)%2==0) {
                cout << "o";
            } else {
                cout << "x";
            }
        }
        cout << endl;
    }
}
