#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

#include "instructions.h"
#include "constants.h"

using namespace std;

string quebra(string *s,string delimiter){
    int pos = s->find(delimiter);
    string token = s->substr(0, pos);
    s->erase(0, pos+ delimiter.length());
    return token;
}

void advance_pc(int n){
    pc+=n;
}

int posicaoRegistrador(string s){
    int i=0;
    while(s!=registersName[i]){
        i++;
        if(i == 32){
            istringstream (s) >> i;
            break;
        }
    }
    return i;
}

int posicaoInstrucao(string s){
    int i=0;
    while(s!=instructionsName[i]){
        i++;
    }
    return i;
}

void addi(int rs,int rt,int immediate){
	registers[rs] = registers[rt] + immediate;
	advance_pc(4);
}

void add(int rd,int rs,int rt){
	registers[rd] = registers[rs] + registers[rt];
	advance_pc(4);
}

void sub(int rd,int rs, int rt){
	registers[rd] = registers[rs] - registers[rt];
	advance_pc(4);
}

void jump(int target){
	pc = target*4;
}

void lw(int rs, int rt, int immediate){
    int PMEM = registers[rt]+(immediate/4);
    istringstream (memory[PMEM]) >> registers[rs];
    advance_pc(4);
}

void slt(int rd,int rs,int rt){
	if (registers[rs] < registers[rt])
		registers[rd] = 1;
	else
		registers[rd] = 0;
	advance_pc (4);
}

void slti(int rd,int rs,int immediate){
	if (registers[rs] < immediate)
		registers[rd] = 1;
	else
		registers[rd] = 0;
	advance_pc (4);
}

void sw(int rs, int rt, int immediate){
    int PMEM = registers[rt]+(immediate/4);
	std::stringstream Resultado;
	Resultado << registers[rs];
    memory[PMEM] = Resultado.str();
	advance_pc (4);
}

void beq(int rs,int rt,int immediate){
	if (registers[rt]==registers[rs]){
		pc = immediate * 4;
	}
	else{
		advance_pc(4);
	}
}

void bne(int rs,int rt,int immediate){
	if (registers[rt]!=registers[rs]){
		pc = immediate * 4;
	}
	else
		advance_pc(4);
}

void jr(int rd, int rs, int rt){
    pc = registers[rd] * 4;
}

void transformaBin(rformat instructions){
    cout << "Instrucao em binario:" << endl;
	bitset<6>bin_opcode(instructions.opcode);
	cout << bin_opcode << " ";
	bitset<5>bin_rs(instructions.rs);
	cout << bin_rs << " ";
	bitset<5>bin_rt(instructions.rt);
	cout << bin_rt << " ";
	bitset<5>bin_rd(instructions.rd);
	cout << bin_rd << " ";
	bitset<5>bin_shamt(instructions.shamt);
	cout << bin_shamt << " ";
	bitset<6>bin_funct(instructions.funct);
	cout << bin_funct << endl;
}

void transformaBinI(iformat instructions){
    cout << "Instrucao em binario:" << endl;
	bitset<6>bin_opcode(instructions.opcode);
	cout << bin_opcode << " ";
	bitset<5>bin_rs(instructions.rs);
	cout << bin_rs << " ";
	bitset<5>bin_rt(instructions.rt);
	cout << bin_rt << " ";
	bitset<16>bin_immediate(instructions.immediate);
	cout << bin_immediate << endl;
}

void transformaBinJ(jformat instructions){
    cout << "Instrucao em binario:" << endl;
	bitset<6>bin_opcode(instructions.opcode);
	cout << bin_opcode << " ";
	bitset<26>bin_address(instructions.address);
	cout << bin_address << endl;
}
