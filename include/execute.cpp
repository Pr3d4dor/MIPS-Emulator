#include <iostream>
#include <string>
#include <bitset>

#include "execute.h"
#include "constants.h"
#include "instructions.h"
void execute(int i,int j,int k,int l){

    	//Instrução JR
    	rformat ijr;
    	ijr.opcode = 0;
	ijr.rs = j;
	ijr.rd = 0;
	ijr.rt = 0;
	ijr.funct = 8;
	ijr.shamt = 0;
	ijr.f = &jr;
	instructionsR[8]=ijr;

    	// Instrucao bne
	iformat ibne;
	ibne.opcode = 5;
	ibne.rt = k;
	ibne.rs = j;
	ibne.immediate = l;
	ibne.f = &bne;
	instructionsI[3]=ibne;

	// Instrucao beq
	iformat ibeq;
	ibeq.opcode = 4;
	ibeq.rt = k;
	ibeq.rs = j;
	ibeq.immediate = l;
	ibeq.f = &beq;
	instructionsI[2]=ibeq;

	//Instrução addi
	iformat iaddi;
	iaddi.opcode = 16;
	iaddi.rs = j;
	iaddi.rt = k;
	iaddi.immediate = l;
	iaddi.f = &addi;
	instructionsI[0]=iaddi;

	//Instrucao add
	rformat iadd;
	iadd.opcode = 0;
	iadd.rs = k;
	iadd.rd = l;
	iadd.rt = j;
	iadd.funct = 32;
	iadd.shamt = 0;
	iadd.f = &add;
	instructionsR[0]=iadd;

	//Instrucao sub
	rformat isub;
	isub.opcode = 0;
	isub.rs = k;
	isub.rd = l;
	isub.rt = j;
	isub.funct = 34;
	isub.shamt = 0;
	isub.f = &sub;
	instructionsR[1]=isub;

    	//Instrução LW
	iformat ilw;
	ilw.opcode = 35;
	ilw.rs = j;
	ilw.rt = k;
	ilw.immediate = l;
	ilw.f = &lw;
	instructionsI[6]=ilw;

	//Instrução SW
	iformat isw;
	isw.opcode = 43;
	isw.rs = j;
	isw.rt = k;
	isw.immediate = l;
	isw.f = &sw;
	instructionsI[7]=isw;

	//Instrucao j
	jformat ij;
	ij.opcode = 2;
	ij.address = j;
	ij.f = &jump;
	instructionsJ[0]=ij;

	//Instrucao slt
	rformat islt;
	islt.opcode = 0;
	islt.rs = k;
	islt.rd = l;
	islt.rt = j;
	islt.funct = 42;
	islt.shamt = 0;
	islt.f = &slt;
	instructionsR[9]=islt;

	// Instrucao slti
	iformat islti;
	islti.opcode = 10;
	islti.rt = k;
	islti.rs = j;
	islti.immediate = l;
	islti.f = &slti;
	instructionsI[4]=islti;

	//Verifica qual o tipo de a instrucao pela posicao do vetor de instrucoes que foi chamado
		if(i < 10){
        	cout << "FORMATO R" << endl;
			instructionsR[i].f(j,k,l);
			transformaBin(instructionsR[i]);
			cout << registersName[j] << endl;
            cout << registers[j] << endl;

            cout << registersName[l] << endl;
            cout << registers[l] << endl;

            cout << registersName[k] << endl;
            cout << registers[k] << endl;
		}else{
        		if(i > 17){
            		cout << "FORMATO J" << endl;
					instructionsJ[i-18].f(j);
					transformaBinJ(instructionsJ[i-18]);
        		}
        		else{
            		cout << "FORMATO I" << endl;
					instructionsI[i-10].f(j,k,l);
					transformaBinI(instructionsI[i-10]);
					cout << registersName[j] << endl;
                    cout << registers[j] << endl;

                    cout << registersName[k] << endl;
                    cout << registers[k] << endl;

                    cout << "Immediate" << endl;
                    cout << instructionsI[i-10].immediate << endl;
        		}
        }
}
