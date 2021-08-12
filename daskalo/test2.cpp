#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;

int main() {
    int a = time(0);
    cout << endl;
    for(int i = 0; i < 11; i ++) {
        cout << "\r" << "progress: ";
        for(int j = 0; j < 11; j ++) {
            cout << char(j <= i - 1 ? 219 : 32);
        }
        cout << i;
        Sleep(500);
    }

}
