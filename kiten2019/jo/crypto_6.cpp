#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;


int MSG_SIZE;
const int MAX_KEY_LENGTH = 400;


unsigned char msg[32520];

int symbols_count[MAX_KEY_LENGTH][256];

int main() {
    ifstream file;
    file.open("enc_task6_3_nokeylen.txt", ios::in | ios::binary);

    for(int i = 0; !file.eof();  ++ i) {
        msg[i] = file.get();
        MSG_SIZE = i;
    }

    unsigned char best_keys[MAX_KEY_LENGTH];
    int best_keys_score = 0;
    int best_key_length = 0;
    for(int KEY_LENGTH = 1; KEY_LENGTH < MAX_KEY_LENGTH; ++ KEY_LENGTH) {
        unsigned char curr_keys[KEY_LENGTH];
        int curr_keys_score = 0;
        for(int i = 0; i < KEY_LENGTH; ++ i) {
            int best_score = 0;
            unsigned char best_key;
            for(int j = 0; j < 256; ++ j) {
                unsigned char curr_key = j;
                int score = 0;
                for(int k = i; k < MSG_SIZE; k += KEY_LENGTH) {
                    unsigned char curr_char = (curr_key ^ msg[k]);
                    if(curr_char == ' ') score += 10;
                    else if((curr_char >= 'a' && curr_char <= 'z')) score += 5;
                    else if((curr_char >= 'A' && curr_char <= 'Z')) score += 5;
                    //else if(curr_char == '.' || curr_char == ',') score += 1;
                    //else if(curr_char == '%' || curr_char == '$' || curr_char == '#' || curr_char == '@' || curr_char == '^' || curr_char == '|' || curr_char == '  `') score -= 7;
                    //else if((curr_char >= '0' && curr_char <= '9')) score += 5;
                    //else score -= 10;
                }
                if(best_score < score) {
                    best_score = score;
                    best_key = curr_key;
                }
            }
            curr_keys_score += best_score;
            curr_keys[i] = best_key;
        }
        if(curr_keys_score > best_keys_score) {
            best_keys_score = curr_keys_score;
            best_key_length = KEY_LENGTH;
            //cout << "found tmp better: " << KEY_LENGTH << ' '  << curr_keys_score << endl;
            for(int i = 0; i < KEY_LENGTH; ++ i) {
                best_keys[i] = curr_keys[i];
            }
        }
    }

    for(int i = 0; i < MSG_SIZE; ++ i) {
        cout << (unsigned char)(best_keys[i % best_key_length] ^ msg[i]);
    }
    cout << endl;
    cout << best_key_length << endl;
    for(int i = 0; i < best_key_length; ++ i) cout << best_keys[i];
}
