#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <fstream>
#define MAX 32

using namespace std;

//Structs que definem os campos de cada tipo difente de instrucao
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

//Prototipos dos metodos
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
void transformaBin(rformat instructions);
void transformaBinI(iformat instructions);
void transformaBinJ(jformat instructions);
void jump(int target);
void jr(int rd, int rs, int rt);
void execute(int i,int j,int k,int l);

//Vetor que contem o valor real dos registradores
int registers[MAX];

//Vetor da memoria do programa
string memory[4096];

//String inicial do comando
string inst;

//Sub strings que vao conter o comando a ser realizado e os registradores
string inst2,inst3,inst4, inst5;

//Program counter
int pc=0;

//Vetor que contem os nomes dos registradores
string registersName[MAX]={"$0","$at","$v0","$v1","$a0","$a1","$a2","$a3",
 						   "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
 						   "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8",
 						   "$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

//Vetor que contem o nome das instrucoes
string instructionsName[MAX]={"add","sub","addu","mult","multu","subu","div","divu","jr","slt", //só do tipo R
                              "addi","subi","beq","bnq","slti","sltiu","lw","sw",               //só do tipo I
                              "j","jal"};                                                       //só do tipo J

//Vetor que contem as instrucoes que podem ser realizadas
rformat instructionsR[10];
iformat instructionsI[10];
jformat instructionsJ[10];

//Metodo para quebrar a string utilizando um delimitador
string quebra(string *s,string delimiter){
	int pos = s->find(delimiter);
	string token = s->substr(0, pos);
	s->erase(0, pos+ delimiter.length());
	return token;
}

//Metodo para aumentar o pc counter
void advance_pc(int n){
	pc+=n;
}

//Metodo para retornar a posicao do registrador a ser utiizado
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

//Metodo para retornar a posicao da instrucao a ser realizada
int posicaoInstrucao(string s){
	int i=0;
	while(s!=instructionsName[i]){
		i++;
	}
	return i;
}
//Metodo da funcao addi
void addi(int rs,int rt,int immediate){
	registers[rs] = registers[rt] + immediate;
	advance_pc(4);
}

//Metodo da funcao add
void add(int rd,int rs,int rt){
	registers[rd] = registers[rs] + registers[rt];
	advance_pc(4);
}

//Metodo da funcao sub
void sub(int rd,int rs, int rt){
	registers[rd] = registers[rs] - registers[rt];
	advance_pc(4);
}

//Metodo da funcao j
void jump(int target){
	pc = target*4;
}

void lw(int rs, int rt, int immediate){
    int PMEM = registers[rt]+(immediate/4);
    istringstream (memory[PMEM]) >> registers[rs];
    advance_pc(4);
}

//Metodo da funcao slt
void slt(int rd,int rs,int rt){
	if (registers[rs] < registers[rt])
		registers[rd] = 1;
	else
		registers[rd] = 0;
	advance_pc (4);
}

//Metodo da funcao slti
void slti(int rd,int rs,int immediate){
	if (registers[rs] < immediate)
		registers[rd] = 1;
	else
		registers[rd] = 0;
	advance_pc (4);
}

//Metodo da funcao sw
void sw(int rs, int rt, int immediate){
    int PMEM = registers[rt]+(immediate/4);
	std::stringstream Resultado;
	Resultado << registers[rs];
    memory[PMEM] = Resultado.str();
	advance_pc (4);
}

//Metodo da funcao beq
void beq(int rs,int rt,int immediate){
	if (registers[rt]==registers[rs]){
		pc = immediate * 4;
	}
	else{
		advance_pc(4);
	}
}

//Metodo da funcao beq
void bne(int rs,int rt,int immediate){
	if (registers[rt]!=registers[rs]){
		pc = immediate * 4;
	}
	else
		advance_pc(4);
}

//Metodo da função jr
void jr(int rd, int rs, int rt){
    pc = registers[rd] * 4;
}

//Metodo que transforma a instrucao em binario usando a biblioteca bitset
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

//Metodo que transforma a instrucao I em binario usando a biblioteca bitset
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

//Metodo que transforma a instrucao J em binario usando a biblioteca bitset
void transformaBinJ(jformat instructions){
    cout << "Instrucao em binario:" << endl;
	bitset<6>bin_opcode(instructions.opcode);
	cout << bin_opcode << " ";
	bitset<26>bin_address(instructions.address);
	cout << bin_address << endl;
}

//Metodo para executar a instrucao desejada
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
  		cout << "\n\nInstrucao: ";	     	 // Impressao
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