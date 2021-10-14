#include <iostream>
using namespace std;
int main () {
    int arr[100];
    int N;

    cin >> N;

    for (int i=0; i<N; i++) {
        cin >> arr[i];
    }

    int long_r = 0;
    int curr_r = 1;

    for (int i=1; i < N; i++) {
        if(arr[i] == arr[i-1]) {
            curr_r ++;
        } else {
            curr_r = 1;
        }
        if(curr_r > long_r) {
            long_r = curr_r;
        }
    }
    cout << long_r;
}
