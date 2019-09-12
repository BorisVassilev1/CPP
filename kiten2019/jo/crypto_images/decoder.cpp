#include <cmath>
#include <iostream>
#include <bitset>
#include "pnglib.h"
#include <fstream>
using namespace std;

unsigned char msg[2000000];

int used_bits = 1;

int main() {

    string inName, outName;
    cout << "read from this image: " << endl;
    cin >> inName;
    cout << "and write in this file: " << endl;
    cin >> outName;
    cout << "bit depth: " << endl;
    cin >> used_bits;
    if(used_bits > 8) used_bits = 8;
    if(used_bits < 1) used_bits = 1;

	// read
	vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	lodepng::decode(image, width, height, inName + ".png");

    int header_length = 32;
    int header = 0;

    for(int i = 0, bits_written = 0; i < width * height * 4 && (bits_written >= header_length ? bits_written < header * 8 + header_length : true); ++ i) {
        if(i % 4 == 3) continue;
        unsigned char pixel = image[i];
        for(int j = used_bits - 1; j >= 0; j --) {
            bool bit = pixel & (1 << j);
            if(bits_written < header_length) {
                short header_bit = bits_written;
                //cout << bit;
                if(bit) {
                    int a = 1 << (header_length - 1 - header_bit);
                    header |= a;
                }
                else {
                    int a = ~(1 << (header_length - 1 - header_bit));
                    header &= a;
                }
            }
            else {
                int msg_char = (bits_written - header_length) / 8;
                short char_bit = (bits_written - header_length) % 8;

                if(bit) {
                    short a = 1 << (7 - char_bit);
                    msg[msg_char] |= a;
                }
                else {
                    short a = ~(1 << (7 - char_bit));
                    msg[msg_char] &= a;
                }
            }
            bits_written ++;
        }
    }

    ofstream out;
    out.open(outName, ios::binary);
    //cout << endl << header;
    for(int i = 0; i < header; ++ i) out << msg[i];
}
