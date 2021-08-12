#include <iostream>
#include <fstream>
#include <cmath>
int N, A0, g_seed;

unsigned int fastrand() {
    g_seed = 214013 * g_seed + 2531011;
    return (g_seed >> 16) & 0x7FFF;
}

int next(int prev) {
    return 1 + prev + (fastrand() & 0b111)
}

int B(int A) {
    return A - (A % 3) * (A % 5);
}

int main() {
    int B0 =
}
