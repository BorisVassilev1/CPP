#include <iostream>

using namespace std;

int print_number(int);

int main () {
    cout << print_number(2) * print_number(3);
}

int print_number (int number) {
    cout << number;
    number *= 2;
    return number;
}
