#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;


int MSG_SIZE;
const int KEY_LENGTH = 23;

unsigned char msg[32520];

int symbols_count[KEY_LENGTH][256];

unsigned char most_used_char[KEY_LENGTH];

unsigned char key[KEY_LENGTH];

int main() {
    ifstream file;
    file.open("enc_task5_keylen23.txt", ios::in | ios::binary);

    for(int i = 0; !file.eof();  ++ i) {
        msg[i] = file.get();
        MSG_SIZE = i;
    }

    for(int i = 0; i < KEY_LENGTH; ++ i) {
        int best_score = 0;
        unsigned char best_key;
        for(int j = 0; j < 256; ++ j) {
            unsigned char curr_key = j;
            int score = 0;
            for(int k = i; k < MSG_SIZE; k += KEY_LENGTH) {
                unsigned char curr_char = (curr_key ^ msg[k]);
                if(curr_char == ' ') score += 5;
                else if((curr_char >= 97 && curr_char <= 122)) score += 15;
                //else if((curr_char >= 65 && curr_char <= 90)) score += 10;
                //else if(curr_char == '.' || curr_char == ',') score += 5;
                //else if(curr_char == '%' || curr_char == '$' || curr_char == '#' || curr_char == '@' || curr_char == '^' || curr_char == '|' || curr_char == '  `') score -= 100;
                //else if((curr_char >= '0' && curr_char <= '9')) score += 10;
                else score -= 10;
            }
            if(best_score < score) {
                best_score = score;
                best_key = curr_key;
            }
        }
        //cout << best_score << " ";
        key[i] = best_key;
    }
    //cout << endl;

    for(int i = 0; i < MSG_SIZE; ++ i) {
        cout << (unsigned char)(key[i % KEY_LENGTH] ^ msg[i]);
    }
    //cout << endl;
    //for(int i = 0; i < KEY_LENGTH; ++ i) cout << key[i];
}
