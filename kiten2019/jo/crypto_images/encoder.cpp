#include <cmath>
#include <iostream>
#include <bitset>
#include "pnglib.h"
#include <fstream>
#include <bitset>
#include <vector>
using namespace std;

vector<unsigned char> msg;

int MSG_SIZE;

int used_bits = 1;


int main(int argc, char** argv) {

    string inName1, inName2, outName;

    //cout << "argument count: " << argc << endl;
    //for(int i = 0; i < argc; i ++) {
    //    cout << argv[i] << endl;
    //}

    if(argc - 1 != 4) {
        if(argc == 2 && argv[1][0] == '?') {
            cout << endl
                 << "   Use: \"imgenc <data> <image> <output file> <bit depth>\"." << endl
                 << "       data - any type of file to be hidden in the image." << endl
                 << "       image - png image to use." << endl
                 << "       output file - output file." << endl
                 << "       bit depth - count of pixels to use from the image [0-8]" << endl;
                 return 0;
        }
        cout << endl << "   Incorrect number of arguments! Use: \"<data> <image> <output file> <bit depth>\". Use \"?\" for help." << endl;
        return 0;
    }

    inName1 = argv[1];
    inName2 = argv[2];
    outName = argv[3];

    used_bits = stoi(argv[4]);;

    //cout << "write this: " << endl;
    //cin >> inName1;
    //cout << "in this image: " << endl;
    //cin >> inName2;
    //cout << "and save in this image: " << endl;
    //cin >> outName;
    //cout << "bit depth: " << endl;
    //cin >> used_bits;

    if(used_bits > 8) used_bits = 8;
    if(used_bits < 1) used_bits = 1;

	// read
	vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	lodepng::decode(image, width, height, inName2);

    ifstream file;
    file.open(inName1, ios::in | ios::binary);

    for(int i = 0; !file.eof();  ++ i) {
        unsigned char a = file.get();
        if (!file)
            break;
        msg.push_back(a);
    }
    //cout << MSG_SIZE << endl;


    MSG_SIZE = msg.size();
    int header = MSG_SIZE;
    int header_length = sizeof(header) * 8;
    //cout << header_length << endl;
    cout << "Attempting to write " << MSG_SIZE * 8 << " bits of data in an image with " << width * height * 4 * used_bits << " bits of storage." << endl;
    //cout << endl << width * height * 4 * used_bits / header;
    int bits_written = 0;
    for(int i = 0; i < width * height * 4  && bits_written < MSG_SIZE * 8 + header_length ; i += 1) {
        if(i % 4 == 3) continue;
        unsigned char pixel = image[i];
        for(int j = used_bits - 1; j >= 0; j --) {

            bool bit = false;
            if(bits_written < header_length) {
                int header_bit = bits_written;
                bit = header & (1 << (header_length - 1 - header_bit));
            }
            else {
                int msg_char = (bits_written - header_length) / 8;
                int char_bit = (bits_written - header_length) % 8;
                bit = msg[msg_char] & (1 << (7 - char_bit));
            }
            if(bit) {
                short a = 1 << j;
                pixel |= a;
            }
            else {
                int a = ~(1 << j);
                pixel &= a;
            }

            bits_written ++;
        }
        image[i] = pixel;
    }

    if(bits_written == MSG_SIZE * 8 + header_length) {
        cout << "Success!" << endl;
        lodepng::encode(outName, image, width, height);
    }
    else cout << "The message is too large to be hidden in this image!";

    return 0;
}
