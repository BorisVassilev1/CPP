#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long delitel = 2;
    int exor = 0;
    for(;delitel  * delitel < n; delitel += delitel%2==0? 1 : 2) {
        int stepen = 0;
        while(n % delitel == 0){
            n/=delitel;
            stepen ++;
        }
        exor ^= stepen;
    }
    if(n != 1) {exor ^= 1;}
    if(exor == 0)
        cout << "vtoriq";
    else
        cout << "purviq";

}
