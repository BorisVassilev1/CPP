#include <iostream>
#include <vector>
using namespace std;

vector<int> vec;

int main() {
    int N;
    cin >> N;
    int a;
    cin >> a;
    vec.push_back(a);
    while(a != 0) {
        cin >> a;
        if(a == 0) break;
        vec.push_back(a);
    }
    int counter = 0;
    for(int i = vec.size() - N; i < vec.size(); i++) {
        //cout << vec[i];
        if(vec[i] % 5 == 0) {
            counter ++;
        }
    }
    cout << counter;
}
