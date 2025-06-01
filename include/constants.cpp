#include "constants.h"

int registers[MAX];
string memory[4096];

string inst;
string inst2, inst3, inst4, inst5;

int pc = 0;

string registersName[MAX] = {
    "$0","$at","$v0","$v1","$a0","$a1","$a2","$a3",
    "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
    "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
    "$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"
};

string instructionsName[MAX] = {
    "add","sub","addu","mult","multu","subu","div","divu","jr","slt",
    "addi","subi","beq","bnq","slti","sltiu","lw","sw",
    "j","jal"
};

rformat instructionsR[10];
iformat instructionsI[10];
jformat instructionsJ[10];
