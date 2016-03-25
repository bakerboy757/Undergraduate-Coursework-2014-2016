#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMMEMORY 16 /* Maximum number of data words in memory */
#define NUMREGS 8    /* Number of registers */

/* Opcode values for instructions */
#define R 0
#define LW 35
#define SW 43
#define BNE 4
#define HALT 63

/* Funct values for R-type instructions */
#define ADD 32
#define SUB 34

/* Branch Prediction Buffer Values */
#define STRONGLYTAKEN 3
#define WEAKLYTAKEN 2
#define WEAKLYNOTTAKEN 1
#define STRONGLYNOTTAKEN 0
#define BUFFERSIZE 128

typedef struct IFIDStruct {
  unsigned int instr;              /* Integer representation of instruction */
  int PCPlus4;                     /* PC + 4 */
} IFIDType;

typedef struct IDEXStruct {
  unsigned int instr;              /* Integer representation of instruction */
  int PCPlus4;                     /* PC + 4 */
  int readData1;                   /* Contents of rs register */
  int readData2;                   /* Contents of rt register */
  int immed;                       /* Immediate field */
  int rsReg;                       /* Number of rs register */
  int rtReg;                       /* Number of rt register */
  int rdReg;                       /* Number of rd register */
  int branchTarget;                /* Branch target, obtained from immediate field */
} IDEXType;

typedef struct EXMEMStruct {
  unsigned int instr;              /* Integer representation of instruction */
  int aluResult;                   /* Result of ALU operation */
  int writeDataReg;                /* Contents of the rt register, used for store word */
  int writeReg;                    /* The destination register */
} EXMEMType;

typedef struct MEMWBStruct {
  unsigned int instr;              /* Integer representation of instruction */
  int writeDataMem;                /* Data read from memory */
  int writeDataALU;                /* Result from ALU operation */
  int writeReg;                    /* The destination register */
} MEMWBType;

typedef struct stateStruct {
  int PC;                                 /* Program Counter */
  unsigned int instrMem[NUMMEMORY];       /* Instruction memory */
  int dataMem[NUMMEMORY];                 /* Data memory */
  int regFile[NUMREGS];                   /* Register file */
  IFIDType IFID;                          /* Current IFID pipeline register */
  IDEXType IDEX;                          /* Current IDEX pipeline register */
  EXMEMType EXMEM;                        /* Current EXMEM pipeline register */
  MEMWBType MEMWB;                        /* Current MEMWB pipeline register */
  int cycles;                             /* Number of cycles executed so far */
} stateType;


void run();
void printState(stateType*);
void initState(stateType*);
unsigned int instrToInt(char*, char*);
int get_opcode(unsigned int);
void printInstruction(unsigned int);
void fetch(stateType *, const stateType);
void decode(stateType *, const stateType);
void execute(stateType *, const stateType);
void memory(stateType *, const stateType);
void write(stateType *, const stateType);

int main(){
    run();
    
    return(0); 
}

void run(){

  stateType state;           /* Contains the state of the entire pipeline before the cycle executes */ 
  stateType newState;        /* Contains the state of the entire pipeline after the cycle executes */
  initState(&state);         /* Initialize the state of the pipeline */
     while (1) {

        printState(&state);

	/* If a halt instruction is entering its WB stage, then all of the legitimate */
	/* instruction have completed. Print the statistics and exit the program. */
        if (get_opcode(state.MEMWB.instr) == HALT) {
            printf("Total number of cycles executed: %d\n", state.cycles);
            /* Remember to print the number of stalls, branches, and mispredictions! */
            exit(0);
        }

        newState = state;     /* Start by making newState a copy of the state before the cycle */
        newState.cycles++;

	/* Modify newState stage-by-stage below to reflect the state of the pipeline after the cycle has executed */
	
	/*• IF stage: fetches the instruction from the instruction cache and increments the PC.
	  • ID stage: decodes the instruction, reads source registers from register file, signextends
	    the immediate value, calculates the branch target address and checks if the
	    branch should be taken.
	  • EX stage: calculates addresses for accessing memory, performs arithmetic/logical
	    operations on either two register values or a register and an immediate.
	  • MEM stage: load a value from or store a value into the data cache.
	  • WB stage: update the register file with the result of an operation or a load. */
        
	/* --------------------- IF stage --------------------- */
	fetch(&newState, state);
        /* --------------------- ID stage --------------------- */       
	decode(&newState, state);

        /* --------------------- EX stage --------------------- */
	//take contents of rs register and the sign extended immed field as inputs to the ALU which performs the add operation
	//sum is placed in EXEM register(for lw)
        execute(&newState, state);

        /* --------------------- MEM stage --------------------- */
	//take address stored in EXMEM register and use it to access dataMem
	//data read from memory is stored in the MEMWB register(for lw)
	memory(&newState, state);
        /* --------------------- WB stage --------------------- */
	//read the data from the MEMWB register and write it back to the register file in the middle of the datapath
	write(&newState, state);
        state = newState;    /* The newState now becomes the old state before we execute the next cycle */
    }
}
void fetch(stateType *newStatePtr, const stateType state){
  
  newStatePtr->IFID.instr = state.instrMem[state.PC/4];
  newStatePtr->IFID.PCPlus4 = state.PC + 4;
  newStatePtr->PC += 4;

}
void decode(stateType *newStatePtr, const stateType state){

  int instr = state.IFID.instr;
  int rs = get_rs(instr), 
      rt = get_rt(instr),
      rd = get_rd(instr), 
      immed = get_immed(instr),
      branchTar = immed;
  //store which registers hold data into newSatte IDEX field
  newStatePtr->IDEX.rsReg = rs;
  newStatePtr->IDEX.rtReg = rt;
  newStatePtr->IDEX.rdReg = rd;
  newStatePtr->IDEX.immed = immed;//sign extend
  newStatePtr->IDEX.instr = instr;
  newStatePtr->IDEX.branchTarget = branchTar;
  //move contents of rs and rt respectively into newStateIDEX
  newStatePtr->IDEX.readData1 = state.regFile[rs];
  newStatePtr->IDEX.readData2 = state.regFile[rt];
  newStatePtr->IDEX.PCPlus4 = state.IFID.PCPlus4;
  //sign extend 16 bit imm field to 32 bit and store in IDEX type
  //PCPlus 4 value from IFID is copied into IDEX register

}
void execute(stateType *newStatePtr, const stateType state){
/*  • EX stage: calculates addresses for accessing memory, performs arithmetic/logical
      operations on either two register values or a register and an immediate.
      
      take contents of rs register and the sign extended immed field as inputs to the ALU which performs the add operation
      sum is placed in EXEM register(for lw)
*/
  int instr = newStatePtr->EXMEM.instr = state.IDEX.instr;

  switch(get_opcode(instr)){
    case LW:
      newStatePtr->EXMEM.aluResult = state.IDEX.readData1 + state.IDEX.immed;//where to put memory
      newStatePtr->EXMEM.writeDataReg = state.IDEX.readData2;
      newStatePtr->EXMEM.writeReg = state.IDEX.rtReg;
      break;
    case SW:
      newStatePtr->EXMEM.aluResult = state.IDEX.readData1 + state.IDEX.immed;
      newStatePtr->EXMEM.writeDataReg = state.IDEX.readData2;//copy contents of rt to EXMEM register
      newStatePtr->EXMEM.writeReg = state.IDEX.rtReg;
      break;
    case BNE:
      if(state.IDEX.readData1!= state.IDEX.readData2)
	instr = state.IDEX.immed;
      break;
    case HALT:
       newStatePtr->EXMEM.writeReg = 0;
       newStatePtr->EXMEM.writeDataReg = 0;
       newStatePtr->EXMEM.aluResult = 0;
      //do nothing
      break;
    case R:
      if(get_funct(instr) == ADD)
          newStatePtr->EXMEM.aluResult = state.IDEX.readData1 + state.IDEX.readData2; 
      else
          newStatePtr->EXMEM.aluResult = state.IDEX.readData1 - state.IDEX.readData2; 
      newStatePtr->EXMEM.writeReg = state.IDEX.rdReg;
      break;
    default:
//      exit(EXIT_FAILURE);
      break;
  }
}
void memory(stateType *newStatePtr, const stateType state){
/*typedef struct MEMWBStruct {
  unsigned int instr;               Integer representation of instruction 
  int writeDataMem;                 Data read from memory 
  int writeDataALU;                 Result from ALU operation 
  int writeReg;                     The destination register 
} MEMWBType;*/
   int instr = newStatePtr->MEMWB.instr = state.EXMEM.instr;
   newStatePtr->MEMWB.writeDataALU = state.EXMEM.aluResult;
   switch(get_opcode(instr)){
     case LW:
	newStatePtr->MEMWB.writeDataMem = newStatePtr->dataMem[state.EXMEM.aluResult/4];//go to address
	newStatePtr->MEMWB.writeReg = state.EXMEM.writeReg;
	break;
     case SW:
	newStatePtr->dataMem[newStatePtr->MEMWB.writeDataALU/4] = state.EXMEM.writeDataReg;
	newStatePtr->MEMWB.writeReg = state.EXMEM.writeReg;
	break;
     case BNE:
	break;
     case HALT:
	newStatePtr->MEMWB.writeDataALU = 0;
	newStatePtr->MEMWB.writeReg = 0;
	break;
     case R:
	newStatePtr->MEMWB.writeReg = state.EXMEM.writeReg;
	break;
     default:
//	exit(EXIT_FAILURE);
	break;
   }



}
void write(stateType *newStatePtr, const stateType state){
/*typedef struct MEMWBStruct {
  unsigned int instr;               Integer representation of instruction 
  int writeDataMem;                 Data read from memory 
  int writeDataALU;                 Result from ALU operation 
  int writeReg;                     The destination register 
} MEMWBType;*/
   switch(get_opcode(state.MEMWB.instr)){
     case LW:
	newStatePtr->regFile[state.MEMWB.writeReg] = state.MEMWB.writeDataMem;
//	newStatePtr->MEMWB.writeDataMem = state.MEMWB.writeDataMem;
        break;
     case SW:
        break;
     case BNE:
        break;
     case HALT:
        break;
     case ADD:
     case SUB:
	newStatePtr->regFile[state.MEMWB.writeReg] = state.MEMWB.writeDataALU;
        break;
     default:
//	exit(EXIT_FAILURE);
        break;
   }



}
/******************************************************************/
/* The initState function accepts a pointer to the current        */ 
/* state as an argument, initializing the state to pre-execution  */
/* state. In particular, all registers are zero'd out. All        */
/* instructions in the pipeline are NOOPS. Data and instruction   */
/* memory are initialized with the contents of the assembly       */
/* input file.                                                    */
/*****************************************************************/
void initState(stateType *statePtr)
{
    unsigned int dec_inst;
    int data_index = 0;
    int inst_index = 0;
    char line[130];
    char instr[6];
    char args[130];
    char* arg; 

    statePtr->PC = 0;
    statePtr->cycles = 0;

    /* Zero out data, instructions, and registers */
    memset(statePtr->dataMem, 0, 4*NUMMEMORY);
    memset(statePtr->instrMem, 0, 4*NUMMEMORY);
    memset(statePtr->regFile, 0, 4*NUMREGS);

    /* Parse assembly file and initialize data/instruction memory */
    while(fgets(line, 130, stdin)){
        if(sscanf(line, "\t.%s %s", instr, args) == 2){
            arg = strtok(args, ",");
            while(arg != NULL){
                statePtr->dataMem[data_index] = atoi(arg);
                data_index += 1;
                arg = strtok(NULL, ","); 
            }  
        }
        else if(sscanf(line, "\t%s %s", instr, args) == 2){
            dec_inst = instrToInt(instr, args);
            statePtr->instrMem[inst_index] = dec_inst;
            inst_index += 1;
        }
    } 

    /* Zero-out all registers in pipeline to start */
    statePtr->IFID.instr = 0;
    statePtr->IFID.PCPlus4 = 0;
    statePtr->IDEX.instr = 0;
    statePtr->IDEX.PCPlus4 = 0;
    statePtr->IDEX.branchTarget = 0;
    statePtr->IDEX.readData1 = 0;
    statePtr->IDEX.readData2 = 0;
    statePtr->IDEX.immed = 0;
    statePtr->IDEX.rsReg = 0;
    statePtr->IDEX.rtReg = 0;
    statePtr->IDEX.rdReg = 0;
 
    statePtr->EXMEM.instr = 0;
    statePtr->EXMEM.aluResult = 0;
    statePtr->EXMEM.writeDataReg = 0;
    statePtr->EXMEM.writeReg = 0;

    statePtr->MEMWB.instr = 0;
    statePtr->MEMWB.writeDataMem = 0;
    statePtr->MEMWB.writeDataALU = 0;
    statePtr->MEMWB.writeReg = 0;
 }


 /***************************************************************************************/
 /*              You do not need to modify the functions below.                         */
 /*                They are provided for your convenience.                              */
 /***************************************************************************************/


/*************************************************************/
/* The printState function accepts a pointer to a state as   */
/* an argument and prints the formatted contents of          */
/* pipeline register.                                        */
/* You should not modify this function.                      */
/*************************************************************/
void printState(stateType *statePtr)
{
    int i;
    printf("\n********************\nState at the beginning of cycle %d:\n", statePtr->cycles+1);
    printf("\tPC = %d\n", statePtr->PC);
    printf("\tData Memory:\n");
    for (i=0; i<(NUMMEMORY/2); i++) {
        printf("\t\tdataMem[%d] = %d\t\tdataMem[%d] = %d\n", 
            i, statePtr->dataMem[i], i+(NUMMEMORY/2), statePtr->dataMem[i+(NUMMEMORY/2)]);
    }
    printf("\tRegisters:\n");
    for (i=0; i<(NUMREGS/2); i++) {
        printf("\t\tregFile[%d] = %d\t\tregFile[%d] = %d\n", 
            i, statePtr->regFile[i], i+(NUMREGS/2), statePtr->regFile[i+(NUMREGS/2)]);
    }
    printf("\tIF/ID:\n");
    printf("\t\tInstruction: ");
    printInstruction(statePtr->IFID.instr);
    printf("\t\tPCPlus4: %d\n", statePtr->IFID.PCPlus4);
    printf("\tID/EX:\n");
    printf("\t\tInstruction: ");
    printInstruction(statePtr->IDEX.instr);
    printf("\t\tPCPlus4: %d\n", statePtr->IDEX.PCPlus4);
    printf("\t\tbranchTarget: %d\n", statePtr->IDEX.branchTarget);
    printf("\t\treadData1: %d\n", statePtr->IDEX.readData1);
    printf("\t\treadData2: %d\n", statePtr->IDEX.readData2);
    printf("\t\timmed: %d\n", statePtr->IDEX.immed);
    printf("\t\trs: %d\n", statePtr->IDEX.rsReg);
    printf("\t\trt: %d\n", statePtr->IDEX.rtReg);
    printf("\t\trd: %d\n", statePtr->IDEX.rdReg);
    printf("\tEX/MEM:\n");
    printf("\t\tInstruction: ");
    printInstruction(statePtr->EXMEM.instr);
    printf("\t\taluResult: %d\n", statePtr->EXMEM.aluResult);
    printf("\t\twriteDataReg: %d\n", statePtr->EXMEM.writeDataReg);
    printf("\t\twriteReg:%d\n", statePtr->EXMEM.writeReg);
    printf("\tMEM/WB:\n");
    printf("\t\tInstruction: ");
    printInstruction(statePtr->MEMWB.instr);
    printf("\t\twriteDataMem: %d\n", statePtr->MEMWB.writeDataMem);
    printf("\t\twriteDataALU: %d\n", statePtr->MEMWB.writeDataALU);
    printf("\t\twriteReg: %d\n", statePtr->MEMWB.writeReg);
}

/*************************************************************/
/*  The instrToInt function converts an instruction from the */
/*  assembly file into an unsigned integer representation.   */
/*  For example, consider the add $0,$1,$2 instruction.      */
/*  In binary, this instruction is:                          */
/*   000000 00001 00010 00000 00000 100000                   */
/*  The unsigned representation in decimal is therefore:     */
/*   2228256                                                 */
/*************************************************************/
unsigned int instrToInt(char* inst, char* args){

    int opcode, rs, rt, rd, shamt, funct, immed;
    unsigned int dec_inst;
    
    if((strcmp(inst, "add") == 0) || (strcmp(inst, "sub") == 0)){
        opcode = 0;
        if(strcmp(inst, "add") == 0)
            funct = ADD;
        else
            funct = SUB; 
        shamt = 0; 
        rd = atoi(strtok(args, ",$"));
        rs = atoi(strtok(NULL, ",$"));
        rt = atoi(strtok(NULL, ",$"));
        dec_inst = (opcode << 26) + (rs << 21) + (rt << 16) + (rd << 11) + (shamt << 6) + funct;
    } else if((strcmp(inst, "lw") == 0) || (strcmp(inst, "sw") == 0)){
        if(strcmp(inst, "lw") == 0)
            opcode = LW;
        else
            opcode = SW;
        rt = atoi(strtok(args, ",$"));
        immed = atoi(strtok(NULL, ",("));
        rs = atoi(strtok(NULL, "($)"));
        dec_inst = (opcode << 26) + (rs << 21) + (rt << 16) + immed;
    } else if(strcmp(inst, "bne") == 0){
        opcode = 4;
        rs = atoi(strtok(args, ",$"));
        rt = atoi(strtok(NULL, ",$"));
        immed = atoi(strtok(NULL, ","));
        dec_inst = (opcode << 26) + (rs << 21) + (rt << 16) + immed;   
    } else if(strcmp(inst, "halt") == 0){
        opcode = 63; 
        dec_inst = (opcode << 26);
    } else if(strcmp(inst, "noop") == 0){
        dec_inst = 0;
    }
    return dec_inst;
}
int get_rs(unsigned int instruction){
    return( (instruction>>21) & 0x1F);
}

int get_rt(unsigned int instruction){
    return( (instruction>>16) & 0x1F);
}

int get_rd(unsigned int instruction){
    return( (instruction>>11) & 0x1F);
}

int get_funct(unsigned int instruction){
    return(instruction & 0x3F);
}

int get_immed(unsigned int instruction){
    return(instruction & 0xFFFF);
}

int get_opcode(unsigned int instruction){
    return(instruction>>26);
}

/*************************************************/
/*  The printInstruction decodes an unsigned     */
/*  integer representation of an instruction     */
/*  into its string representation and prints    */
/*  the result to stdout.                        */
/*************************************************/
void printInstruction(unsigned int instr)
{
    char opcodeString[10];
    if (instr == 0){
      printf("NOOP\n");
    } else if (get_opcode(instr) == R) {
        if(get_funct(instr)!=0){
            if(get_funct(instr) == ADD)
                strcpy(opcodeString, "add");
            else
                strcpy(opcodeString, "sub");
            printf("%s $%d,$%d,$%d\n", opcodeString, get_rd(instr), get_rs(instr), get_rt(instr));
        }
        else{
            printf("NOOP\n");
        }
    } else if (get_opcode(instr) == LW) {
        printf("%s $%d,%d($%d)\n", "lw", get_rt(instr), get_immed(instr), get_rs(instr));
    } else if (get_opcode(instr) == SW) {
        printf("%s $%d,%d($%d)\n", "sw", get_rt(instr), get_immed(instr), get_rs(instr));
    } else if (get_opcode(instr) == BNE) {
        printf("%s $%d,$%d,%d\n", "bne", get_rs(instr), get_rt(instr), get_immed(instr));
    } else if (get_opcode(instr) == HALT) {
        printf("%s\n", "halt");
    }
}

