#include<iostream>
using namespace std;

const int MAX_N = 300;

int a[MAX_N][MAX_N];
int res[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];
int n, k;

void mul(int* a, int* b, int* res) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            res[i * n + j] = 0;
            /// *(res + i * n + j) = 0;
            /// z[i][j] = 0;

            for(int k = 0; k < n; ++k) {
                res[i * MAX_N + j] += a[i * MAX_N + k] * b[k * MAX_N + j];
            }
        }
    }
}

/// slaga a^k vuv res i izpolzva tmp, kudeto mu trqbva
void pow(int* a, int* res, int* tmp, int k) {

    if(k == 1) {
        res = a;
    }
    else if(k % 2 == 0) {
        pow(a,tmp,tmp,  k / 2);
        mul(tmp,tmp, res);
    }
    else {
        pow(a, tmp, tmp, k - 1);
        mul(tmp, a, res);
    }
}



int main() {
    cin >> n;
    cin >> k;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    pow((int*)a, (int*) res, (int*) temp, k);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << res[i][j] << " ";
        }

        cout << endl;
    }
}
