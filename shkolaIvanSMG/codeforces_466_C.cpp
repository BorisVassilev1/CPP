#include <iostream>
using namespace std;

const int MAX_N = 5 * 1e5 + 1;
long long numbers[MAX_N];

int main() {
    int n;
    cin >> n;
    long long sum = 0;
    long long sub_sum;
    for(int i = 0; i < n; ++ i) {
        long long num;
        cin >> num;
        numbers[i] = num;
        sum += num;
    }
    if(sum % 3 != 0) {cout << 0; return 0;}
    sub_sum = sum / 3;
    //cout << sub_sum << endl;
    long long curr_sum = 0;
    int _1 = 0;
    int _2 = 0;
    long long ans = 1;
    for(int i = n - 1; i > 0; i --) {
        curr_sum += numbers[i];
        if(curr_sum == sub_sum * 2) {
            ++ _2;
        }
        else if(curr_sum == sub_sum) {
            ++ _1;
            ans += _2;
        }
    }
}
