#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

unsigned char msg[32520];

int symbols_count[256];

int MSG_SIZE;

int main() {
    ifstream file;
    file.open("enc_task4.txt", ios::in | ios::binary);

    for(int i = 0; !file.eof();  ++ i) {
        msg[i] = file.get();
        MSG_SIZE = i;
    }

    for(int i = 0; i < MSG_SIZE; ++ i) {
        symbols_count[msg[i]] ++;
    }

    int most_used_char_count = 0;
    unsigned char most_used_char;


    for(int i = 0; i < 256; i ++) {
        if(most_used_char_count < symbols_count[i]) {
            most_used_char = i;
            most_used_char_count = symbols_count[i];
        }
    }

    unsigned char key = most_used_char ^ ' ';

    for(int i = 0; i < MSG_SIZE; ++ i) {
        cout << (unsigned char)(key ^ msg[i]);
    }
}
