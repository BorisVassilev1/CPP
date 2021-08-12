#include <iostream>
using namespace std;
            ///BOT ZA NIMB

void print(int *data, int len) {
    for(int i = 0; i < len; i ++) {
        cout << data[i] << " ";
    }
    return;
}

int exor(int *data, int len) {
    int _exor = 0;
    for(int i = 0; i < len; i ++) {
        _exor ^= data[i];
    }
    return _exor;
}

void turn(int *data, int len) {
    int _exor = exor(data, len);

    for(int i = 0; i < len; i ++) {
        int curr_exor = _exor ^ data[i];
        //cout << curr_exor;
        if(curr_exor <= data[i]) {
            data[i] = curr_exor;
            break;
        }
    }
    cout << "az igrah! " << endl;;
    print(data,len);
    cout << endl;
}

bool ended(int *data, int len) {
    bool hasEnded = true;
    for(int i = 0; i < len; i ++) {
        if(data[i] != 0) hasEnded = false;
    }
    return hasEnded;
}

void humanTurn(int* data, int len) {
    cout << "ti si na hod!";
    for(int i = 0; i < len; i ++) {
        cin >> data[i];
    }
    return;
}

int main() {
    int koi_e_purvi;
    int broi_kupchinki;
    cout << "broi kupchinki: ";
    cin >> broi_kupchinki;
    cout << endl << "kupchinki: ";
    int data[broi_kupchinki];
    for(int i = 0; i < broi_kupchinki; i ++) {
        cin >> data[i];
    }
    ///ok

    bool moqta_poziciq;
    int _exor = exor(data, broi_kupchinki);
    moqta_poziciq = _exor == 0;

    if(moqta_poziciq) {
        cout << "ti si purvi";
    }
    else {
        cout << "az sum purvi";
        turn(data,broi_kupchinki);
    }

    while(true) {
        humanTurn(data,broi_kupchinki);
        //print(data, broi_kupchinki);
        if(ended(data, broi_kupchinki)) {cout << "ti biesh!!"; return 0;}
        turn(data,broi_kupchinki);
        if(ended(data, broi_kupchinki)) {cout << "az biq!!"; return 0;}
    }

    //cout << exor;
}
