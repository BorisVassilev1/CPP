#include <iostream>
#include <string>

const int MAN_N = 1000000, MAX_M = 1000;

int kmpTable[MAX_M];

int main() {
    std::string big;
    std::string small;
    std::cin >> big >> small;

    int n = big.size();
    int m = small.size();

    ///Precompute kmpTable
    kmpTable[0] = 0;

    for(int i = 1; i < m; i ++) {
        int current = i;
        while(current > 0 && small[kmpTable[current - 1]] != small[i]) {
                current = kmpTable[current - 1];
        }
        if(current == 0) {
            if(small[i] == small[0]) {
                kmpTable[i] = 1;
            }
            else {
                kmpTable[i] = 0;
            }
        }
        else {
            kmpTable[i] = kmpTable[current - 1] + 1;
        }
    }

    /*
    for(int i = 0; i <m; i ++) {
        std::cout << kmpTable[i];
    }
    std::cout << std::endl;
    */

    ///Match
    int bigIndex = 0;
    int smallIndex = 0;
    int matchCount = 0;

    while(bigIndex < n) {
        if(small[smallIndex] == big[bigIndex]) {
            if(smallIndex < m - 1) {
                ++smallIndex;
                ++bigIndex;
            }
            else {
                std::cout << "Match at: " << bigIndex - m + 1 << std::endl;
                ++matchCount;

                if(smallIndex > 0) {
                    smallIndex = kmpTable[smallIndex];
                }
                ++bigIndex;
            }
        }
        else {
            if(smallIndex > 0) {
                smallIndex = kmpTable[smallIndex];
            }
            else {
                ++bigIndex;
            }
        }
    }
}
