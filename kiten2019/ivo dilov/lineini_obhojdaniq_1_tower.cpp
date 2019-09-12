#include <iostream>
#include <vector>
using namespace std;

vector<int> s;

int main() {
    int n;
    int kula;
    cin >> n >> kula;
    int best = 0;
    s.push_back(0);
    for(int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        if(k > kula) {s.clear();s.push_back(0);}
        while(k > s[s.size() - 1]) {s.pop_back();}
        s.push_back(k);
        if(s.size() > best) {best = s.size();}
    }
    cout << best;
}
/*
12 180
200 170 130 90 150 140 40 30 100 160 50 110

*/
