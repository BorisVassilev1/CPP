#include <iostream>
#include <queue>
using namespace std;

struct baba {
    string ime;
    int mrunkaemost;
    int index;
    baba (string ime, int mrunkaemost, int index) : ime(ime), mrunkaemost(mrunkaemost), index(index){}

    bool operator < (const baba a) const {
        if(mrunkaemost != a.mrunkaemost){return mrunkaemost < a.mrunkaemost;}
        else { return index > a.index;}
    }

};

priority_queue<baba > a;

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) {
        char c;
        cin >> c;
        if(c == 'd') {
            string ime;
            int mrunkaemost;
            cin >> ime >> mrunkaemost;
            baba b(ime, mrunkaemost,i);
            a.push(b);
        } else if(c == 'p') {
            cout << a.top().ime << endl;
            a.pop();
        }
    }

}
