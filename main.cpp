#include <iostream>
#include <string>
#include <bitset>
#include <fstream>

#include "include/constants.h"
#include "include/instructions.h"
#include "include/execute.h"


int main(int argc, char const *argv[])
{
	//Contador que guarda o numero de linhas que foram copiadas para a memoria
	int cont=0;
	int controle=0;

	//Variaveis de indice
	int i,j,k,l;

	//Inicia registradores com zero
	for (int w=0;w<MAX;w++){
		registers[w]=0;
	}

	//Inicia memória com x
	for (int w=0;w<4096;w++){
		memory[w]="x";
	}

    //Mudando valor da memória e de alguns registrador para testar utilizando o teste.txt
    memory[58]="12";
    registers[21]=50;
	registers[10]=8;
	registers[8]=8;
	registers[9]=27;
	registers[18]=10;
	registers[17]=10;
	registers[22]=10;
	registers[20]=1;
	registers[19]=0;	

	//Variavel do tipo ifstream para receber o arquivo txt
  	ifstream myfile ("teste.txt");

  	//Copia todas as linhas do arquivo para a memoria
  	while (getline (myfile,memory[cont])){
  		cont++;
  	}
  	myfile.close();

  	while (memory[pc/4]!="x"){
  		cout << "\n\nInstrucao: ";   // Impressao
    	cout << memory[pc/4] << endl;        // Impressao
    	inst = memory[pc/4];
		inst2 = quebra(&inst," ");
            if((posicaoInstrucao(inst2) == 16)||(posicaoInstrucao(inst2) == 17)){
                inst3 = quebra(&inst,",");
                inst5 = quebra(&inst,"(");
                inst4 = quebra(&inst,")");
                inst = inst5;
            }
            else{
                inst3 = quebra(&inst,",");
                inst4 = quebra(&inst,",");
            }

		i=posicaoInstrucao(inst2);
		j=posicaoRegistrador(inst3);
		k=posicaoRegistrador(inst4);
		l=posicaoRegistrador(inst);

		execute(i,j,k,l);

	}
	return 0;
}
