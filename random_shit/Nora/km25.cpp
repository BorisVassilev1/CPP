#include <iostream>
using namespace std;
int main () {
    int N;
    cin >> N;
    int arr[100];
    int sum[100];
    for (int i=0; i<N; i++) {
        cin >> arr[i];
    }
    for (int i=0; i<N; i++) {
        sum[i] = 0;
        do {
           sum[i] += arr[i]%10;
           arr[i] = arr[i]/10;
        }
        while (arr[i] != 0);
        cout << sum [i] << " ";
    }
}
