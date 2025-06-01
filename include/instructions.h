#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <iostream>
#include <string>

#include "constants.h"

using namespace std;

string quebra(string *s,string delimiter);
void advance_pc(int n);
int posicaoRegistrador(string s);
int posicaoInstrucao(string s);
void add(int rd,int rs,int rt);
void sub(int rd,int rs, int rt);
void jump(int target);
void lw(int rs, int rt, int immediate);
void slt(int rd,int rs,int rt);
void slti(int rd,int rs,int immediate);
void sw(int rs, int rt, int immediate);
void beq(int rs,int rt,int immediate);
void bne(int rs,int rt,int immediate);
void addi(int rs,int rt,int immediate);

void transformaBin(rformat instructions);
void transformaBinI(iformat instructions);
void transformaBinJ(jformat instructions);
void jump(int target);
void jr(int rd, int rs, int rt);

#endif //INSTRUCTIONS_H
