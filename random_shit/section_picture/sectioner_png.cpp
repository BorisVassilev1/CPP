#include "pnglib.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string input_name = "adv_time.png";

    //read
    vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	lodepng::decode(image, width, height, input_name);

    unsigned grid_size = 100;

	for(int i = 0; i < image.size(); i += 4) {
        unsigned pixel_id = i / 4;
        unsigned x = pixel_id % width;
        unsigned y = pixel_id / width;
        if(x % grid_size == 0 || y % grid_size == 0) {
            image[i + 0] = 255 - image[i + 0];
            image[i + 1] = 255 - image[i + 1];
            image[i + 2] = 255 - image[i + 2];
            //image[i + 3] = 255 - image[i + 3];
        }
	}

    lodepng::encode("sectioned.png", image, width, height);
}
