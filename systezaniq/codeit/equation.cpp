#include <iostream>
#include <math.h>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_N = 500;
const int MAX_K = MAX_N * 500;
int N;

int a[MAX_N + 10];

int p[MAX_K / 2 + 10][MAX_N + 10];


/*
    p(i, j) be True if a subset of { x0, ..., xj } sums to i and False otherwise.
Then p(K/2 , N - 1) is True if and only if there is a subset of S that sums to K/2.
 The goal of our algorithm will be to compute p(K/2, N - 1). In aid of this, we have the following recurrence relation:

    p(i, j) is True if either p(i, j − 1) is True or if p(i − xj, j − 1) is True
    p(i, j) is False otherwise
*/

int main() {
    ifstream in;
    in.open("equation.in");
    ofstream out;
    out.open("equation.out");


    in >> N;
    int sum = 0;
    for(int i = 0; i < N; i ++) {
        in >> a[i];
        sum += a[i];
    }

    if(sum % 2 != 0) {
        out << "NO";
        return 0;
    }

    int K = sum / 2;
    //cout << K << endl;

    for(int i = 0; i <= K; ++ i) {
        p[i][0] = (i == 0);
    }

    for(int j = 1; j <= N; j ++ ) {
        for(int i = 0; i <= K; i ++) {
            //cout << a[j - 1];
            if( p[i][j-1]) {
                p[i][j] = true;
            } else {
                if(a[j - 1] > i) continue;
                if(p[i - a[j - 1]][j-1]) {
                    p[i][j] = true;
                }
            }
        }
    }
    //cout << endl;

    /*for(int i = 0; i <= K; i ++) {
        for(int j = 0; j <= N; j ++) {
            cout << p[i][j] << " ";
        }
        cout << endl;
    }*/

    out << (p[K][N] == 1 ? "YES" : "NO");
}
