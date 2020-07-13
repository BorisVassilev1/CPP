#include <iostream>
#include <time.h>
#include <string>
#include <array>
using namespace std;

struct player {
    string name;
    int id;
    player(string _name, int _id) : name(_name), id(_id) {}
    player(){};
    void set(string _name, int _id){
        name = _name;
        id = _id;
    }
    string tostring() {
        return string("player{name: ").append(name ).append(", id: ").append(to_string(id) ).append("}");
    }
};

struct game {
    const int BOARD_LENGTH = 16;
    const int PLAYER_COUNT = 4;
    player** players;
    int alive_count;
    int* board;
    game() {
        board = new int[BOARD_LENGTH];
        fill(board, board + BOARD_LENGTH, -1);
        players = new player*[PLAYER_COUNT];
        alive_count = PLAYER_COUNT;
    }
    ~game() {
        for(int i = 0; i < PLAYER_COUNT; i ++) {
            if(players[i] != nullptr)
                delete players[i];
        }
        delete this->players;
        delete [] board;
    }
    string tostringPlayers() {
        string out("game{");
        for(int i = 0; i < PLAYER_COUNT; i ++) {
            if(players[i] != nullptr)
                out.append(players[i]->tostring());
            else
                out.append("nullptr");
            if(i != PLAYER_COUNT - 1)
                out.append(", ");
        }
        out.append("}");
        return out;
    }
    string tostringBoard() {
        string out;
        for(int i = 0; i < BOARD_LENGTH; i ++) {
            out.append(to_string(i)).append(":");
            if(i < 10) out.append(" ");
            out.append(to_string(board[i])).append("\n");
        }
        return out;
    }
    void set_player(player* p) {
        players[p->id] = p;
    }
};

int roll_dice();
void move_player(game* g, player* p, int amt);
void remove_player(game*g, player* p);
void play_turn(game* g);
void play_game(game* g);

int main() {

    srand(time(0));

    game* myGame = new game();
    myGame->set_player(new player("a", 0));
    myGame->set_player(new player("b", 1));
    myGame->set_player(new player("c", 2));
    myGame->set_player(new player("d", 3));

    //cout << myGame->tostringPlayers() << endl;
    //cout << myGame->tostringBoard() << endl;

    play_game(myGame);

    //cout << myGame->tostringPlayers() << endl;

    delete myGame;
}

int roll_dice() {
    return rand() % 6 + 1;
}

void remove_player(game* g, player* p) {
    if(!p) return;

    int id = p->id;
    delete g->players[id];
    g->players[id] = nullptr;
    g->alive_count--;
}

void move_player(game* g, player* p, int amt) {
    int id = p->id;
    int* board = g->board;

    int pos = -1;
    for(int i = 0; i < g->BOARD_LENGTH;i ++) {
        if(board[i] == id) pos = i;
    }
    int dest = (pos + amt)%16;
    if(board[dest] != -1) {
        //cout << g->players[board[dest]]->name << " died" << endl;
        remove_player(g, g->players[board[dest]]);
    }
    board[id] = -1;
    board[dest] = id;
}

void play_turn(game* g) {
    for(int i = 0; i < g->PLAYER_COUNT; i ++) {
        if(g->players[i]) {
            //cout << g->players[i]->name << " plays!" << endl;
            move_player(g, g->players[i], roll_dice());
        }
    }
}

void play_game(game* g) {
    int turn = 0;
    while(g->alive_count != 1) {
        turn ++;
        play_turn(g);
    }
    player* winner;
    for(int i = 0; i < g->PLAYER_COUNT; i ++) {
        if(g->players[i]) {
            winner = g->players[i];
        }
    }
    cout << winner->name << " Won on turn " << turn << endl;
}
