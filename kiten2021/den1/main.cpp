#include <iostream>

using namespace std;

int main() {
	
	const int size = 20;

	for(int y = -size; y <= size; y ++) {
		for(int x = -size; x <= size; x ++) {
			if(x * x + y * y <= size * size) {
				cout << "##";
			}
			else {
				cout << "  ";
			}
		}
		cout << endl;
	}

	return 0;
}
