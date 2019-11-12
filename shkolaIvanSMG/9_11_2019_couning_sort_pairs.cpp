#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

const int MAX_N = 1000000;
const int MAX_LOG_N = 20;

int sortedIndex[MAX_LOG_N][MAX_N + 1];
string str;
int n;
int k, twoPowK;



bool cmpInit(int start1, int start2) {
    return str[start1] < str[start2];
}

bool cmpByTwoPowK(int start1, int start2) {
    if(sortedIndex[k - 1][start1] != sortedIndex[k - 1][start2]) {
        return sortedIndex[k - 1][start1] < sortedIndex[k - 1][start2];
    }

    int start1Shift = min(start1 + twoPowK / 2, n);
    int start2Shift = min(start2 + twoPowK / 2, n);

    return sortedIndex[k - 1][start1Shift]
            <= sortedIndex[k - 1][start2Shift];
}

int main() {
    cin >> str;
    n = str.size();

    vector<int> initArr;

    for(int i = 0; i < n; ++i) {
        initArr.push_back(i);
    }

    sort(initArr.begin(), initArr.end(), cmpInit);

    int currInd = 0;
    sortedIndex[0][initArr[0]] = 0;
    cout << 0 << endl;

    for(int i = 1; i < n; ++i) {
        if(str[initArr[i]] != str[initArr[i - 1]]) {
            ++currInd;
        }

        sortedIndex[0][initArr[i]] = currInd;
        ///cout << initArr[i] << endl;
        cout << sortedIndex[0][initArr[i]] << endl;
    }

    sortedIndex[0][n] = -1;

    for(k = 1, twoPowK = 2; twoPowK <= n; ++k, twoPowK *= 2) {
        /// compute sortedIndex[k][...]
        for(int i = 0; i < n; ++i) {
            initArr[i] = i;
        }

        sort(initArr.begin(), initArr.end(), cmpByTwoPowK);

        sortedIndex[k][initArr[0]] = 0;
        int currInd = 0;
        for(int i = 1; i < n; ++i) {
            if(!(cmpByTwoPowK(initArr[i], initArr[i - 1]) &&
                    cmpByTwoPowK(initArr[i - 1], initArr[i]))) {
                ++currInd;
            }

            sortedIndex[k][initArr[i]] = currInd;
        }

        sortedIndex[k][n] = -1;

        cout << "-----------\n";
        cout << "K = " << k << endl;
        for(int i = 0; i < n; ++i) {
            cout << initArr[i] << " ";
        }
        cout << endl;

        for(int i = 0; i < n; ++i) {
            cout << sortedIndex[k][initArr[i]] << " ";
        }
        cout << endl;

    }

    for(int i = 0; i < n; ++i) {
        cout << sortedIndex[k][initArr[i]] << " ";
    }

    return 0;
}
