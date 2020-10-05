#include <iostream>
#include <cstring>
using namespace std;


/*void memcopy(void* source, void* dest, size_t _size) {
    cout << _size << endl;
    char *p, *q;
    p = (char*)source;
    q = (char*)dest;

    for(int i = 0; i < _size; i ++) {
        q[i] = p [i];
    }
}*/

void memswap1(void* a, void* b, size_t _size) {
    cout << _size << endl;
    char *p, *q, temp;
    p = (char*)a;
    q = (char*)b;

    for(int i = 0; i < _size; i ++) {
        cout << i << " : " << q[i] << " " << p[i] << endl;
        temp = q[i];
        q[i] = p[i];
        p[i] = temp;
    }
}


void memswap2(void* a, void* b, size_t _size) {
    char* c = new char[_size];
    memcpy(c, a, _size);
    memcpy(a, b, _size);
    memcpy(b, c, _size);
    delete [] c;
}


class bruh {
public:
    int kekw;
    float brUhe;
    string kys;

    bruh(int kekw, float brUhe, string kys) : kekw(kekw), brUhe(brUhe), kys(kys) {
    }

    void print() {
        cout << this->kekw << " " << this->brUhe << " " << this->kys << endl;
    }
};


int main() {
    bruh* a = new bruh(1, 2.3, "abcdefg");
    bruh* b = new bruh(69, 4.5, "gfedcba");
    cout << sizeof(bruh) << endl;

    a->print();
    b->print();

    //memcopy(a, b, sizeof(bruh));
    memswap2(a, b, sizeof(bruh));

    a->print();
    b->print();
}
