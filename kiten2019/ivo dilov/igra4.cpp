#include <iostream>
using namespace std;

long long n;

int main() {
    cin >> n;
    long long delitel = 2;
    int broi_deliteli = 0;
    for(;delitel  * delitel < n; delitel += delitel%2==0? 1 : 2) {
        while(n % delitel == 0){
            n/=delitel;
            broi_deliteli ++;
        }
    }
    if(n != 1) {broi_deliteli ++;}
    if(broi_deliteli % 2 == 1) {
        cout << "1 pecheli";
    }
    else cout << "2 pecheli";
}
