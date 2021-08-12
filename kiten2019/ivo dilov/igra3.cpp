#include <iostream>
#include <set>
using namespace std;
///OOF GRESHNO USLOVIE LOL
bool wl[1000007];
int n;
set<int> deliteli;
int main() {
    cin >> n;
    int temp = n;
    ///razlagane
    long long delitel = 2;
    while(temp != 1) {
        while(temp % delitel == 0){
            temp/=delitel;

        }
        deliteli.insert(delitel);
        delitel += delitel%2==0? 1 : 2;
    }
    wl[0] = false;
    wl[1] = false;
    for(int i = 2;i < n + 1; i ++) {
        //wl[i] = true/false
        bool imaLiGubeshtaPoziciqKatoVariant = false;
        for(auto j = deliteli.begin(); j != deliteli.end(); j ++) {
            if(i - *j >= 0 && !wl[i - *j]) {
                imaLiGubeshtaPoziciqKatoVariant = true;
            }
        }
        wl[i] = imaLiGubeshtaPoziciqKatoVariant;
    }
    cout << wl[n] << endl;

    //for(int i = 0; i < n; i ++) {
    //    cout << wl[i] << " ";
    //}

}
