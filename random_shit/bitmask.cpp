#include <iostream>
#include <bitset>

using namespace std;

unsigned int check_mask(unsigned int mask, unsigned int n) {
    return (mask & n) == mask;
}

int restore_data(unsigned int data1, unsigned int _xor) {
    return _xor ^ data1;
}

int is_power_of_two(unsigned int n) {
    return (n & (n-1)) == 0;
}
int main() {
    unsigned int n = 8;
    cout << is_power_of_two(n);
}
