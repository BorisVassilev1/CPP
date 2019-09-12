#include <cmath>
#include <iostream>
#include <bitset>
#include "pnglib.h"
#include <fstream>
#include <bitset>
#include <time.h>
using namespace std;

const int colors_count = 512;

struct Color {
    int r, g, b;
    Color() {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
    }
    Color(int r, int g, int b) : r(r), g(g), b(b){}
};

int dist(Color &a, Color &b) {
    return (a.r - b.r) * (a.r - b.r) + (a.g - b.g) * (a.g - b.g) + (a.b - b.b) * (a.b - b.b);
    //return abs(a.r - b.r) + abs(a.g - b.g) + abs(a.b - b.b);
}

Color pivots[colors_count];
int sumR[colors_count];
int sumG[colors_count];
int sumB[colors_count];
int sumC[colors_count];

int main() {
    srand(time(0));
    vector<unsigned char> image; //the raw pixels
    unsigned width, height;
    lodepng::decode(image, width, height, "src_2.png");

    for(int k = 0; k < 10; ++ k) {
        //_time = time(0);
        for(int i = 0; i < width * height * 4; i += 4) {
            Color col(image[i], image[i + 1], image[i + 2]);
            int closestIndex = -1;
            int minDist = 2e9;
            for(int j = 0; j < colors_count; ++ j) {
                int curr_dist = dist(pivots[j], col);
                if(curr_dist < minDist) {
                    minDist = curr_dist;
                    closestIndex = j;
                }
            }
            sumR[closestIndex] += col.r;
            sumG[closestIndex] += col.g;
            sumB[closestIndex] += col.b;
            sumC[closestIndex] ++;
        }

        for(int i = 0; i < colors_count; ++ i) {
            if(sumC[i] != 0) {
                sumR[i] /= sumC[i];
                sumG[i] /= sumC[i];
                sumB[i] /= sumC[i];
                pivots[i] = {sumR[i], sumG[i], sumB[i]};
                sumC[i] = sumR[i] = sumG[i] = sumB[i] = 0;
            }
            else pivots[i] = Color();
        }
    }
    for(int i = 0; i < width * height * 4 ; i += 4) {
        Color col(image[i], image[i + 1], image[i + 2]);
        int closestIndex = -1;
        int minDist = 2e9;
        for(int j = 0; j < colors_count; ++ j) {
            int curr_dist = dist(pivots[j], col);
            if(curr_dist < minDist) {
                minDist = curr_dist;
                closestIndex = j;
            }
        }
        image[i + 0] = pivots[closestIndex].r;
        image[i + 1] = pivots[closestIndex].g;
        image[i + 2] = pivots[closestIndex].b;
    }
    //draw the color palette on the image:
    /*for(int i = 0; i < colors_count; ++ i) {
        for(int x = 0; x < 10; ++ x) {
            for(int y = 0; y < 10; ++ y) {
	        image[(y * width + x + i * 10) * 4 + 0] = pivots[i].r;
	        image[(y * width + x + i * 10) * 4 + 1] = pivots[i].g;
	        image[(y * width + x + i * 10) * 4 + 2] = pivots[i].b;
	    }
        }
    }*/
    lodepng::encode("finished.png", image, width, height);
}
