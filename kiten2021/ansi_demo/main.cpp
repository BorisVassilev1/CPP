#include <iostream>
#include <math.h>
#include <unistd.h>
using namespace std;

// color codes: 30-37; 90-97
// color prefix: \x1B
// reset: /033[0m

// unicode (linux)
string square = "██";
// ascii (windows)
//string square = string() + (char) 219 + (char) 219;

void draw_pixel_at(int y, int x, const char* pixel) {
	cout << "\033[" << y + 1 << ";" << x * 2 + 1 << "H" << pixel << flush;
}

void move_cursor_to(int y, int x) {
	cout << "\033[" << y + 1 << ";" << x * 2 + 1 << "H" << flush;
}

void clear_screen() {
	cout << "\033[2J" << flush; // does not move the cursor to (0,0) althouth it should...
	move_cursor_to(0, 0);
}

double PI = 3.14159;

int main() {
	clear_screen();
	
	system("stty raw");

	int i = 0;
	int x = 0;
	int y = 0;
	double angle = 0;
	int max = 20;
	
	char ch;
	while((ch = getchar()) != 'q') {
		
		if(ch == 27) ch = getchar();
		if(ch == 91) ch = getchar();

		i++;
		i %= max;
		
		draw_pixel_at(x, y, "  ");
		angle = (double)i / max * 2  * PI;
		x = round(cos(angle) * 10 + 20);
		y = round(sin(angle) * 10 + 20);
		draw_pixel_at(x, y, square.c_str());
		cout << (int) ch << endl;
		move_cursor_to(0, 0);
		//usleep(1000000 / 20);
	}

	move_cursor_to(40, 0);

	cout << endl;
	
	system("stty cooked");

	return 0;
}
