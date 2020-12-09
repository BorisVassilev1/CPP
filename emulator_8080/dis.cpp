#include <iostream>
#include <fstream>
using namespace std;

/*
 *  * OP
 *   * OP D1
 *    * OP D1 D2
 *     */

const unsigned int ROM_SIZE = 8192;
unsigned char memory[ROM_SIZE];

struct CPU {
    unsigned char A, B, C, D, E, H, L;
    bool flagZero, flagSign, flagCarry, flagParity;
    unsigned short PC, SP;
};

CPU cpu;

unsigned short concat(unsigned char high, unsigned char low) {
    return ((unsigned short)high << 8) | low;
}

unsigned char h(unsigned short a) {
    return a >> 8;
}

unsigned char l(unsigned short a) {
    return a & 0x00FF;
}

void set(unsigned char & high, unsigned char & low, unsigned short value) {
    high = h(value);
    low = l(value);
}

void run() {
#define A cpu.A
#define B cpu.B
#define C cpu.C
#define D cpu.D
#define E cpu.E
#define H cpu.H
#define L cpu.L
#define BC concat(B, C)
#define DE concat(D, E)
#define HL concat(H, L)
#define PC cpu.PC
#define SP cpu.SP 
    cout << "==============================" << endl;
    cout << "About to execute: " << std::hex << (int)memory[PC] << endl;
    unsigned char tmp8;
    unsigned short tmp16;
    switch(memory[PC]) {
        case 0x00:
            PC++;
            break;
        case 0x05:
            B = B - 1;
            PC ++;
            break;
        case 0x06: 
            B = memory[PC+1];
            PC += 2;
            break;
        case 0x11:
            D = memory[PC + 2];
            E = memory[PC + 1];
            PC += 3;
            break;
        case 0x13:
            set(D, E, DE + 1);
            PC ++;
            break;
        case 0x1A:
            A = memory[DE];
            PC ++;
            break;
        case 0x21:
            H = memory[PC+2];
            L = memory[PC+1];
            PC += 3;
            break;
        case 0x23:
            set(H, L, HL + 1);
            PC ++;
            break;
        case 0x31:
            SP = concat(memory[PC+2], memory[PC+1]);
            PC += 3;
            break;
        case 0x77:
            memory[HL] = A;
            PC ++;
            break;
        case 0xC2:
            tmp16 = concat(memory[PC+2], memory[PC+1]);
            PC = (tmp16!= 0 ? tmp16: PC + 3);
            break;
        case 0xC3:
            PC = concat(memory[PC+2], memory[PC+1]);
            break;
        case 0xCD:
            memory[SP-1] = h(PC);
            memory[SP-2] = l(PC);
            SP-= 2;
            PC = concat(memory[PC+2], memory[PC+1]);
            break;
        default:
            cout << "Unimplemented instruction " << std::hex << (int)memory[PC] << endl;
            exit(0);
            break;
    }

#undef A
#undef B
#undef C
#undef D
#undef E
#undef H
#undef L
#undef BC
#undef DE
#undef HL
#undef PC
#undef SP
}

void logCPU() {
    cout << std::hex
            << "PC=" << cpu.PC
            << " SP=" << cpu.SP
            << " A=" << (int)cpu.A
            << " B=" << (int)cpu.B
            << " C=" << (int)cpu.C
            << " D=" << (int)cpu.D
            << " E=" << (int)cpu.E
            << " H=" << (int)cpu.H
            << " L=" << (int)cpu.L
            << " flagZero:" << cpu.flagZero
            << " flagSign:" << cpu.flagSign
            << " flagCarry:" << cpu.flagCarry
            << " flagParit:" << cpu.flagParity << endl;
}

int main() {
    ifstream inFile("invaders.bin", ios::binary);

    for (unsigned int i = 0; i < ROM_SIZE; i++) {
        char b;
        inFile.read(&b, 1);
        memory[i] = b;
    }

    inFile.close();

    cout.setf(ios::hex, ios::basefield);
    
    logCPU();
    for(int i = 0; i < 20; i ++) {
        run();
        logCPU();
        cout << "Operations finished: " << std::dec << i + 1 << endl;
    }

    return 0;
}

