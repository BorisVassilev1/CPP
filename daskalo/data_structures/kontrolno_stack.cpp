#include <iostream>
#include "stack_array.cpp" // implementaciq na stack

using namespace std;

struct ball {
    int number; // nomer na topkata v nachaloto
    bool color; // topkata cherna li e
};

int N, K; // N i K po uslovie

int main() {
    
    stack<ball> s1, s2, s3; // saotvetno truba A, B, C

    cin >> N >> K; 
    
    for(int i = 0; i < N; i ++) {
        ball b = {i + 1, i + 1 == K}; // ako nomera e raven na K, topkata e cherna
        s1.push(b); // v truba A
    } 

    int cmd;
    for(int i = 0; i < 2*N; i ++) {
        cin >> cmd;
        if(cmd == 1) { // komanda 1
            s2.push(s1.top());
            s1.pop();
        } else { // komanda 2
            s3.push(s2.top());
            s2.pop();
        }
    }

    int counter = 0; // broi topki, koito si zapazvat mqstoto.
    while(!s3.is_empty()) { // shte vadim topkite ot steka 
        ball b = s3.top(); 
        int n_number = s3.size(); // topka s nomer 3 shte bude na vurha na steka kogato toi ima razmer 3
        s3.pop();
        if(b.number == n_number) { // ako noviq nomer e kato stariq
            counter ++;
        }
        if(b.color == 1) { // ako topkata e cherna
            cout << n_number << " ";
        }
    }
    cout << counter << endl; 
}
