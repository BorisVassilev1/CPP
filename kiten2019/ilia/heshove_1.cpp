#include <iostream>
using namespace std;

long long MOD = 1e9 + 7;

unsigned long long pow(int n, int k) {
    unsigned long long result = 1;
    for(int i = 0; i < k ; i ++) {
        result *= n;
    }
    return result;
}

unsigned long long prec[5100][5100];

int main() {
    int n = 4, k = 2;
    cin >> n >> k;
    char a[n][n];
    char b[k][k];
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j < k; ++j) {
            cin >> b[i][j];
        }
    }
    unsigned long long hashA = 0;
    unsigned long long hashB = 0;
    ///table hash for A
    for(int i = 0; i < k; i ++) {
        for(int j = 0; j < k; j ++) {
            int power = (k - i - 1) * k + (k - j - 1);
            hashA += pow(59,power) * (a[i][j] - 64);
        }
    }
    ///table hash for B
    for(int i = 0; i < k; i ++) {
        for(int j = 0; j < k; j ++) {
            int power = (k - i - 1) * k + (k - j - 1);
            hashB += pow(59,power) * (b[i][j] - 64);
        }
    }
    ///preocompute
    {
        for(int j = 0; j < n ; j ++) {
            for(int i = 0; i < k; ++i) {
                prec[j][0] += pow(59, k-i - 1) * (a[j][i] - 64);
            }

        }

        for(int i = 0; i < n ; ++ i) {
            for(int j = 1; j < n - k + 1; ++j) {
                prec[i][j] = prec[i][j - 1] - pow(59,k-1) * (a[i][j-1] - 64);
                prec[i][j] *= 59;
                prec[i][j] += a[i][j + k - 1] - 64;
            }
        }
    }
    ///wtf
    unsigned long long powK = pow(59,k);
    unsigned long long powK1K = pow(59,(k-1) * k);

    for(int i = 0; i < n - k + 1; ++i) {
        ///purvoto
        unsigned long long currTableHash = 0;
        int power = 1;
        for(int h = k - 1; h >= 0; --h) {
            currTableHash += prec[h][i] * power;
            power *= powK;
        }
        if(currTableHash == hashB) {cout << 0 << " " << i << endl;}
        ///vsqko sledvashto
        for(int j = 1; j < n - k + 1; ++j) {
            currTableHash -= prec[j-1][i] * powK1K;
            currTableHash *= powK;
            currTableHash += prec[j + k - 1][i];
            if(currTableHash == hashB) {cout << j << " " << i << endl;}
        }
    }
}

/*
4 2
a b c d
e f g h
i j k l
m n o p
j k
n o
*/
