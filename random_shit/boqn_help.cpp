#include <stdlib.h>
#include <iostream>
#include <fstream>
#include<windows.h>
#include<psapi.h>
#include<tchar.h>
using namespace std;

#define DIV 1048576

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
        return ("{name: " + name + ", id: " + to_string(id) + "}");
    }
};

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof( memCounter ));
    SIZE_T physMemUsedByMe = memCounter.WorkingSetSize;
    return physMemUsedByMe;
}


void printMemoryStatus()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);

    cout << ((statex.ullTotalVirtual - statex.ullAvailVirtual) / (float)DIV) << endl;
}


int main() {
    player* players;

    //players = (player*) calloc(4, sizeof(player));
    players = new player[4]();

    //if(!players) cout << "failed malloc!" << endl;

    cout << "asd" << endl;

    players[0].set("a", 1);
    players[1].set("b", 2);
    players[2].set("c", 3);
    players[3].set("d", 4);

    cout << endl << "asda" << endl;
    //cout << players[1].name;

    for(int i = 0; i < 4; i ++) {
        cout << players[i].tostring() << endl;
    }

    cout << "memory usage before delete: " << getMemoryUsage() / (float) DIV << endl;
    printMemoryStatus();
    //cout << "wtf";

    //free(players);
    delete [] players;
    //cout << (players + 1 != nullptr) << endl;


    //cout << "aas";
    cout << "memory usage after delete: " << getMemoryUsage() / (float) DIV << endl;
    printMemoryStatus();
    //for(int i = 0; i < 4; i ++) {
        //cout << players[i].tostring() << endl;
    //}

    return 0;
}
