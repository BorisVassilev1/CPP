#include <iostream>
#include <math.h>
#include <ncurses.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>

using namespace std;

const double PI = 3.14159;

const int framerate = 25;

const int width = 300;
const int height = 80;

const int entity_width = 13;
const int entity_height = 5;

const int player_speed = 3;
int frame_counter = 0;

constexpr const char *const spaceship[] = {
	"      ▄      ",
	"     ███     ",
	"▄███████████▄",
	"█████████████",
	"█████████████",
};

constexpr const char *const explosion[] = {
	"▀▄  ▀▄ ▄▀  ▄▀",
	"  ▀       ▀  ",
	"━━━━     ━━━━",
	"  ▄       ▄  ",
	"▄▀  ▄▀ ▀▄  ▀▄",
};

const int char_width = 8;
const int char_height = 5;

constexpr const char *const letters[] = {
"██████      ██  ██████  ██████  ██  ██  ██████  ██████  ██████  ██████  ██████   ████   █████    █████  █████   ██████  ██████   █████  ██  ██    ██    ██████  ██  ██  ██      ██   ██ ██   ██  ████   █████    ████   █████   ██████  ██████  ██  ██  ██  ██  ██   ██ █    █  ██  ██  ██████            ██     ███               ██          ",
"██  ██      ██      ██      ██  ██  ██  ██      ██          ██  ██  ██  ██  ██  ██  ██  ██  ██  ██      ██  ██  ██      ██      ██      ██  ██    ██        ██  ██ ██   ██      ███ ███ ███  ██ ██  ██  ██  ██  ██  ██  ██  ██  ██        ██    ██  ██  ██  ██  ██   ██ ██  ██  ██  ██      ██    ██      ██    █   █             ██           ",
"██  ██      ██  ██████  ██████  ██████  ██████  ██████      ██  ██████  ██████  ██████  ██████  ██      ██  ██  ██████  ██████  ██ ███  ██████    ██        ██  ████    ██      ██ █ ██ ██ █ ██ ██  ██  █████   ██  ██  █████   ██████    ██    ██  ██  ██  ██  ██ █ ██  ████   ██████    ██              ██      ██             ██            ",
"██  ██      ██  ██          ██      ██      ██  ██  ██      ██  ██  ██      ██  ██  ██  ██  ██  ██      ██  ██  ██      ██      ██  ██  ██  ██    ██    ██  ██  ██ ██   ██      ██   ██ ██  ███ ██  ██  ██      ██  █   ██ ██       ██    ██    ██  ██   ████   ███ ███ ██  ██      ██  ██        ██                            ██             ",
"██████      ██  ██████  ██████      ██  ██████  ██████      ██  ██████  ██████  ██  ██  █████    █████  █████   ██████  ██       ████   ██  ██    ██     ████   ██  ██  ██████  ██   ██ ██   ██  ████   ██       █████  ██  ██  ██████    ██     ████     ██    ██   ██ █    █  ██████  ██████            ██      ██     ██    ██              ",
}; 

constexpr const char *const lose_msg	= "you lose!";
constexpr const char *const win_msg		= "you won!";
constexpr const char *const pause_msg	= "paused";
constexpr const char *const info_msg[] = {
	"s : start/menu",
	"p : pause/unpaues",
	"r : restart",
	"q : quit"
};
constexpr const char *const game_name = "space invaders";

int player_pos = width / 2 - entity_width / 2;

struct bullet {
	int y, x;
	static int speed;
	bool direction = 0;

	bullet(int y, int x, int direction) : y(y), x(x), direction(direction) {}

	void update() {
		if(direction)
			y += speed;
		else
			y -= speed;
	}

	void draw() const {
		if(direction) {
			mvaddstr(y + 1, x + 1, "░");
			mvaddstr(y + 2, x + 1, "▒");
			mvaddstr(y + 3, x + 1, "▓");
			mvaddstr(y + 4, x + 1, "█");

		} else {
			mvaddstr(y + 1, x + 1, "█");
			mvaddstr(y + 2, x + 1, "▓");
			mvaddstr(y + 3, x + 1, "▒");
			mvaddstr(y + 4, x + 1, "░");
		}
	}
};

int bullet::speed = 2;

void shoot(int y, int x, int direction);

void draw_sprite(int y, int x, int h, int w, int offset, const char *const *sprite, int size) {
	for(int i = 0; i < h; i ++) {
		const char *const & row = sprite[i];
		for(int j = 0, k = 0; row[j] != '\0' && (k < offset + w || w == -1); k ++) {
			if(row[j] != ' ') {
				for(int py = 0; py < size; py ++) {
					for(int px = 0; px < size; px ++) {
						if(k >= offset)mvaddnstr(y + (i + 1) * size + py, x + (k + 1 - offset) * size + px, row + j , 3);
					}
				}
				j += 3;
			} else {
				j ++;
			}
		}
	}
}

void draw_sprite(int y, int x, int h, int w, int offset, const char *const *sprite) {
	draw_sprite(y, x, h, w, offset, sprite, 1);
}

void draw_sprite(int y, int x, const char *const *sprite) {
	draw_sprite(y, x, entity_height, -1, 0, sprite);
}

void draw_str(int y, int x, const char *str, int size) {
	for(int i = 0; i < strlen(str); i ++) {
		int index = -1;
		char ch = str[i];
		if(ch >= '0' && ch <= '9') {
			index = str[i] - '0';
		}
		else if(ch >= 'a' && ch <= 'z') {
			index = str[i] - 'a' + 10;
		}
		else if(ch == ':') {
			index = 36;
		} 
		else if(ch == '!') {
			index = 37;
		} 
		else if(ch == '?') {
			index = 38;
		} 
		else if(ch == '.') {
			index = 39;
		} 
		else if(ch == '/') {
			index = 30;
		}
		else if(ch == ' ') {
			index = 41;
		}
		
		if(index != -1)
			draw_sprite(y, x + i * char_width * size, char_height, char_width, index * char_width, letters, size);
		else
			draw_sprite(y, x + i * char_width * size, char_height, char_width, 38 * char_width, letters, size);
	}
}

void draw_str(int y, int x, const char *const str) {
	draw_str(y, x, str, 1);
}

struct invader {
	int y, x;
	int state = 0;

	static constexpr const char * const visuals[2][7] = {
		{
			"   ▀▄   ▄▀   ",
			"  ▄█▀███▀█▄  ",
			" █▀███████▀█ ",
			" █ █▀▀▀▀▀█ █ ",
			"    ▀▀ ▀▀    ",
		},
		{
			" ▄ ▀▄   ▄▀ ▄ ",
			" █▄███████▄█ ",
			" ███▄███▄███ ",
			" ▀█████████▀ ",
			"  ▄▀     ▀▄  ",
		}
	};

	int color = 0;

	int move_counter = 0;
	static int move_speed;
	static int move_pattern[][2];
	static int shoot_timeout;

	invader(const int y, const int x) : y(y), x(x) {}

	invader(const int y, const int x, const int color) : y(y), x(x), color(color) {}

	void update() {
		if(!(frame_counter % framerate)) {
			state += 1;
			state %= 2;
		}
		if(!(frame_counter % (framerate * 2))) {
			y += move_pattern[move_counter][0] * move_speed;
			x += move_pattern[move_counter][1] * move_speed;
			move_counter ++;
		}
		if(rand() % (framerate * shoot_timeout) < 1) {
			shoot(y + entity_height / 2 , x + entity_width / 2, 1);
		}
	}

	void draw() const {
		attron(COLOR_PAIR(color));
		for(int i = 0; i < entity_height; i ++) {
			const char *const & row = visuals[state][i];
			for(int j = 0, k = 0; row[j] != '\0'; k ++) {
				if(row[j] != ' ') {
					mvaddnstr(y + i + 1, x + k + 1, row + j , 3);
					j += 3;
				} else {
					j ++;
				}
			}
		}
		attroff(COLOR_PAIR(color));
	}
};

int invader::move_pattern[28][2]; 
int invader::move_speed = 4;
int invader::shoot_timeout = 10;

vector<bullet*> bullets;
vector<invader*> invaders;
int alive_invaders;
int score;
int lives;

bool is_game_running = false;
int game_state = -2;

void init_stats() {
	score = 0;
	lives = 3;
}

void draw_spaceship() {
	attron(COLOR_PAIR(COLOR_GREEN));
	draw_sprite(height - entity_height, player_pos, spaceship);
	attroff(COLOR_PAIR(COLOR_GREEN));
}

void update_bullets() {
	for(auto i = bullets.begin(); i != bullets.end(); i ++) {
		if(*i != nullptr) {
			(*i)->update();
			if((*i)->y < 0 || (*i)->y > height) {
				delete *i;
				*i = nullptr;
				continue;
			}
		}
	}
}

void draw_bullets() {
	for(auto i = bullets.begin(); i != bullets.end(); i ++) {
		if(*i != nullptr) {
			(*i)->draw();
		}
	}
}

void init_invaders() {
	int invaders_count_x = 10;
	int invaders_count_y = 6;
	int invaders_distance_x = 4;
	int invaders_distance_y = 2;
	int invaders_offset_x = width / 2 - invaders_count_x * (entity_width + invaders_distance_x) / 2 - invader::move_speed * 10 / 2;
	int invaders_offset_y = 7;

	for(int i = 0; i < 10; i ++) {
		invader::move_pattern[i][0] = 0;
		invader::move_pattern[i][1] = 1;
	}
	for(int i = 0; i < 4; i ++) {
		invader::move_pattern[i + 10][0] = 1;
		invader::move_pattern[i + 10][1] = 0;
	}
	for(int i = 0; i < 10; i ++) {
		invader::move_pattern[i + 14][0] = 0;
		invader::move_pattern[i + 14][1] = -1;
	}
	for(int i = 0; i < 4; i ++) {
		invader::move_pattern[i + 24][0] = -1;
		invader::move_pattern[i + 24][1] = 0;
	}


	for(int i = 0; i < invaders_count_y; i ++) {
		int color;
		switch(i) {
			case 0:
				color = COLOR_RED;
				break;
			case 1: 
				color = COLOR_YELLOW;
				break;
			case 2: 
				color = COLOR_GREEN;
				break;
			case 3: 
				color = COLOR_CYAN;
				break;
			case 4:
				color = COLOR_BLUE;
				break;
			case 5:
				color = COLOR_MAGENTA;
				break;
		}
		for(int j = 0; j < invaders_count_x; j ++) {
			invaders.push_back(new invader(
						i * (entity_height + invaders_distance_y) + invaders_offset_y,
						j * (entity_width + invaders_distance_x) + invaders_offset_x,
						color));
		}
	}

	alive_invaders = invaders_count_x * invaders_count_y;
}

void delete_invaders() {
	for(auto i = invaders.begin(); i != invaders.end(); i ++ ) {
		delete *i;
	}
	invaders.clear();
}

void delete_bullets() {
	for(auto i = bullets.begin(); i != bullets.end(); i ++ ) {
		delete *i;
	}
	bullets.clear();
}

void update_invaders() {
	for(auto i = invaders.begin(); i != invaders.end(); i ++) {
		if(*i == nullptr) continue;
		(*i)->update();	
	}
}

void draw_invaders() {
	for(auto i = invaders.begin(); i != invaders.end(); i ++) {
		if(*i == nullptr) continue;
		(*i)->draw();
	}
}

bool are_colliding(int y, int x, bullet& b) {
	return b.x >= x && b.x < x + entity_width && 
		b.y >= y && b.y < y + entity_height;
}

void check_collisions() {
	for(auto j = bullets.begin(); j != bullets.end(); j ++) {
		for(auto i = invaders.begin(); i != invaders.end(); i ++) {
			if(*i != nullptr && *j != nullptr && !((*j)->direction) && are_colliding((*i)->y, (*i)->x, **j)) {
				draw_sprite((*j)->y - entity_height / 2, (*j)->x - entity_width / 2, explosion);
				delete *i;
				*i = nullptr;
				delete *j;
				*j = nullptr;
				alive_invaders --;
				score ++;
			}
		}
		if(*j != nullptr && (*j)->direction && are_colliding(height - entity_height, player_pos, **j)) {
			draw_sprite((*j)->y - entity_height / 2, (*j)->x - entity_width / 2, explosion);
			delete *j;
			*j = nullptr;
			lives --;
		}
	}
}

void shoot(int y, int x, int direction) {
	for(auto i = bullets.begin(); i != bullets.end(); i ++) {
		if(*i == nullptr) {
			*i = new bullet(y, x, direction);
			return;
		}
	}
	bullets.push_back(new bullet(y, x, direction));
}

void draw_borders() {
	move(0,0);
	addstr("\u2554");
	for(int i = 1; i < width + 1; i ++)
		addstr("\u2550");
	addstr("\u2557");
	move(height + 1, 0);
	addstr("\u255A");
	for(int i = 1; i < width + 1; i ++)
		addstr("\u2550");
	addstr("\u255D");
	for(int i = 1; i < height + 1; i ++)
		mvaddstr(i, 0, "\u2551");
	for(int i = 1; i < height + 1; i ++)
		mvaddstr(i, width + 1, "\u2551");
}

void draw_gui() {
	string sc = to_string(score);
	string li = to_string(lives);

	const char* score_lbl = "score:";
	const char* lives_lbl = "lives:";

	draw_str(1, 1, score_lbl);
	draw_str(1, 1 + strlen(score_lbl) * char_width, sc.c_str());

	draw_str(1, width - (strlen(lives_lbl) + 1) * char_width, lives_lbl);
	draw_str(1, width - char_width, li.c_str());

	//draw_str(40, 5, "the quick brown fox jumps over the lazy dog");
}

void win_screen() {
	draw_str(height / 2 - char_height / 2, width / 2 - strlen(win_msg) * char_width / 2, win_msg);
}

void lose_screen() {
	draw_str(height / 2 - char_height / 2, width / 2 - strlen(lose_msg) * char_width / 2, lose_msg);
}

void pause_screen() {
	draw_str(height / 2 - char_height / 2, width / 2 - strlen(pause_msg) * char_width / 2, pause_msg);
}

void main_screen() {
	constexpr int rows_count = size(info_msg);
	draw_str(height / 2 - (rows_count + 3) * (char_height + 1) / 2, width / 2 - strlen(game_name) * char_width, game_name, 2);
	for(int i = 0; i < rows_count; i ++) {
		draw_str(height / 2 - (rows_count - 3 - i * 2) * (char_height + 1) / 2, width / 2 - strlen(info_msg[i]) * char_width / 2, info_msg[i]);
	}
}

void cleanup() {
	delete_bullets();
	delete_invaders();
}

void init() {
	init_invaders();
	init_stats();

}

void reset() {
	cleanup();
	init();
}

void redraw(int& ch) {
	clear();
	if(is_game_running) {
		do {
			switch(ch) { 
				case KEY_LEFT:
					player_pos -= player_speed;
					break;
				case KEY_RIGHT:
					player_pos += player_speed;
					break;
				case ' ': 
					shoot(height - 2, player_pos + entity_width / 2, 0);
					break;
				case 'p':
					if(game_state == -1){
						is_game_running = !is_game_running;
					}
					break;
			}
		} while((ch = getch()) != ERR);

		player_pos = min(player_pos, width - entity_width);
		player_pos = max(player_pos, 0);

		update_bullets();
		update_invaders();
		check_collisions();
	}

	if(alive_invaders <= 0)  {
		is_game_running = false;
		game_state = 1;
	}
	if(lives <= 0) {
		is_game_running = false;
		game_state = 0;
	}

	draw_borders();

	if(game_state != -2) {
		draw_bullets();
		draw_spaceship();
		draw_invaders();
		draw_gui();
	}

	if(!is_game_running) {
		switch(game_state) {
			case -2 :
				main_screen();
				if(ch == 's') {
				}
				break;
			case -1 : 
				pause_screen();
				break;
			case 0 : 
				lose_screen();
				break;
			case 1 :
				win_screen();
				break;
		}

		switch(ch) {
			case 'r' : 
				if(game_state >= -1) {
					reset();
					is_game_running = true;
				}
				break;
			case 'p' :
				if(game_state == -1)
					is_game_running = !is_game_running;
				break;
			case 's' :
				if(game_state == -2) {
					game_state = -1;
					is_game_running = true;
				} else {
					reset();
					game_state = -2;
				}
				break;
		}
	}


	move(height + 2, 0);
	refresh();
	frame_counter ++;
}

void* resize_handler(int sig) {
	//int nh, nw;
	//getmaxyx(stdscr, nh, nw);
	int ch = ERR;
	if(!is_game_running)
		redraw(ch);
	return nullptr;
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(0));

	initscr();
	clear();
	noecho();
	cbreak();	
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	nonl();
	intrflush(stdscr, FALSE);
	start_color();

	for(int i = 0; i < 8; i ++) {
		init_pair(i, i, 0);
	}

	signal(SIGWINCH, (__sighandler_t) resize_handler);

	init();

	int ch;
	do {
		redraw(ch);
		usleep(1000000 / framerate);
	} while((ch = getch()) != 'q'); 

	cleanup();
	move(20, 0);
	addch('\n');

	endwin();

	return 0;
}
