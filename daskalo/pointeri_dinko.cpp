#include <iostream>

using namespace std;

int a[] {0,1,2,3,4,5,6,7,8,9};

int sum(int* arr, int len) {
    int sum = 0;
    for(int i = 0; i < len; ++ i) {
        sum += arr[i];
    }
    return sum;
}

struct hamburger {
    int mass;
    bool ima_li_zele;

    hamburger(int _mass, bool _ima_li_zele) {
        mass = _mass;
        ima_li_zele = _ima_li_zele;
    }
};

hamburger b(10, true);

void print(hamburger* h) {
    cout << "burger: " << h->mass << " ; " << h->ima_li_zele << endl;3
}


int main() {
    cout << *(a + 10) << endl;
    cout << sum(a, 10)<< endl;
    print(&b);

    hamburger* c = new hamburger(20, 0);

    print(c);

    delete c;

    print(c);
}
