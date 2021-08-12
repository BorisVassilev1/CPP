#include <iostream>

using namespace std;

int main() {
    bool are_there_any = false;
    for(int i = 0; i < 3; i ++) {
        int n;
        cin >> n;
        if(n % 2 == 0 && n % 4 != 0) {
            cout << n << " ";
            are_there_any = true;
        }
    }
    if(!are_there_any)
        cout << "N/A";
    cout << endl;
}
