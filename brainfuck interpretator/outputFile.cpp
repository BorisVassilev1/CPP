#include <iostream>
using namespace std;
char array[65536] = {0};
char* ptr = array;
int main() {
++*ptr;
--*ptr;
cout << *ptr;
}
