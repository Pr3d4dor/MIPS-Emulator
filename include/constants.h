#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
using namespace std;

#define MAX 32

typedef struct {
    int opcode, rs, rd, rt, shamt, funct;
    void (*f)(int, int, int);
} rformat;

typedef struct {
    int opcode, rs, rt, immediate;
    void (*f)(int, int, int);
} iformat;

typedef struct {
    int opcode, address;
    void (*f)(int);
} jformat;

// Deklaracje (extern)
extern int registers[MAX];
extern string memory[4096];

extern string inst;
extern string inst2, inst3, inst4, inst5;

extern int pc;

extern string registersName[MAX];
extern string instructionsName[MAX];

extern rformat instructionsR[10];
extern iformat instructionsI[10];
extern jformat instructionsJ[10];

#endif
