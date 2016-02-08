/*
    Tyler Kelly : tck13
*/
#include <stdio.h>
#include <string.h>
/************
*    BUFFERSIZE for mac length of single line
*    MAXSIZE for how many lines in a file
*
*    inst[] holds names of instructions with key meaning
*
*    Instruction struct will tokenize instructions in meaningful way
*    instructionSet will hold all the tokenized instructions in its own array
*
*    Label struct will hold the addr and name of a label used 
*    labelSet will hold all label struct values
*
*    Format struct will hold the important values we will print to the screen
*    fArray actually holds these values
*
*    lCurSize holds current size of labelSet
*    curSize holds current size for instructionSet
*    fCurSize holds current size for fArray
*************/
#define BUFFERSIZE 512
#define MAXSIZE 100

char *inst[] = {"add", "addi", "nor", "ori", "sll",
                "lui", "sw", "lw", "bne", "j", "la"};
int curSize = 0,
    lCurSize = 0,
    fCurSize = 0,
    dataLabels= 0;
typedef struct Instruction{
    int addr;
    char opcode[5],
         argv1[4],
         argv2[4],
         argv3[4];

}Instruction;

typedef struct Label{
    int addr, 
        value;
    char name[128],
         directive[7];

}Label;

typedef struct Format{
    int addr,
        hexa;
    Instruction instr;
}Format;


Instruction instructionSet[MAXSIZE];
Label labelSet[MAXSIZE];
Format fArray[MAXSIZE];
/*
*
*/
int isInstr(const char*,  int);
void convert_la(Instruction cur, int line);
int parseInstruction(const char*, const int);
void itrInstr();
void r_format(const int);
void i_format(const int);
void j_format(const int);
void ori_inst(const int);
void lui_inst(const int);
int getReg(const char*);
void printArr();
void insertF(const int, const int);
int getLabelAddr(const char *);

int parseData(const char *, int);
int parseText(const char *, int); 

int main(int argc, char *argv[]){
    char buffer[BUFFERSIZE];
    int line = 0;
    int flag = 0;//flag to tell if what section we are in

    //first pass, grab labels and identifiers
    while(fgets(buffer, BUFFERSIZE, stdin) != NULL){
        //remove trailing new line characters(risky and not thread safe but whatevs
        strtok(buffer, "\n");
        //if we see .data the are about to enter the data zone so 
        //set flag to 1 and be prepared for directives
        if(strstr(buffer, ".data"))
            flag = 1;
        //line is incremented if a valid directive(which in our case should be everything 
        //past .data
        if(flag)
             line = parseData(buffer, line);
        //this part is actually done first, we increase line if a valid instruction
        //basically saying skip .text since all lines are valid
        else
             line = parseText(buffer, line);
    }
    //this will iterate over all instructions in instructionSet and calls functions that machine code-inize our assembly
    itrInstr();
    //all the hardwork is done, lets celebrate by printing out our data in a nice formatted structure
    printArr();
    return 0;

}
/*
*    This function will parse all lines in the .data section(from .data to EOF)
*/
int parseData(const char* buf, int line){
    //create temp struct to hold values
    Label l1; 
    //value will hold a user number ie. in _a: .space 400, value would be 400
    char value[20000];
    //this statement basically tells us to piss off if we are sending in the .data buffer
    //otherwise we enter in the if
    if(strstr(buf, ":")){
        //matches _a: .word 400
        sscanf(buf, "%[^':']: %s %s", l1.name, l1.directive, value);
        //convert "400" to an int, value is our offset
        l1.value = atoi(value);
        /*  if this is the first directive than our offset will just be whatever
            line we are on * 4
            otherwise: we need to check the last directive to see how big of an 
            offset to account for 
            if .space was last directive, then we need to alocate space based on the value(AKA a varaiable amount)
            otherwise, this means we passed in a .word which has a set limit of 4 bytes so we just say the address 
            of that word is the last lines address + 4 for our current spot
        */
        if(dataLabels > 0){
            if(!strcmp(labelSet[lCurSize - 1].directive, ".space"))
                l1.addr = line * 4 + labelSet[lCurSize - 1].value - 4;
            else //it's .word
                l1.addr =  labelSet[lCurSize - 1].addr + 4;
        }
        else //it's the first directive
            l1.addr = line * 4;
        //again dataTables is a hacky fix so I know where I am with my directives
        dataLabels++;
        //this throws l1 into an array of label structs so that we can later parse
        //and check for appropriate use of la and other instructions that depend on .data directives
        labelSet[lCurSize] = l1;
        lCurSize++;
        line++;
    }
    return line;
}
//this function is point less now but saved for posterity
int parseText(const char* buf, int line){
    //calls isInstr which passes an instruction via buf
    line = isInstr(buf, line);
    return line;
}
//prints FArray in hex format
void printArr(){
    int i = 0;
    for(i =0;i < fCurSize; i++){
        printf("0x%08X: 0x%08X\n", fArray[i].addr, fArray[i].hexa);

    }

}
//this function will verify that buf is indeed an instruction and
//call dtrInst to parse that instruction and place into our instruction array
int isInstr(const char* buf, int line){
    int i = 0, runs = 0;
    for(i = 0; runs == 0 && i < 11; i++){
        if(strstr(buf, inst[i]) != NULL){
            //inserts instruction into our array 
            line = parseInstruction(buf, line);
            runs++;
        }
    }
    return line;

}
//this function parse our instruction(differentiating between an instruction with a label 
//and one without)
int parseInstruction(const char* buf, int line){
    Label l1;
    Instruction cur;
    //if instruction is with preceding label...
    if(strstr(buf, ":")){
        sscanf(buf, "%[^':']: %s %[^','], %[^','], %s", l1.name, cur.opcode, cur.argv1, cur.argv2, cur.argv3);
        if(!strcmp(cur.opcode, "la")){
            convert_la(cur,line);
            line++;
        }
        else{
            //store label addr to be whatever line we passed in
            l1.addr = line * 4;
            //set this value to 0; only used for directives
            l1.value = 0;
            labelSet[lCurSize] = l1;
            lCurSize++;
            cur.addr = line * 4;
            //return instruction
            instructionSet[curSize] = cur;
            curSize++;
        }
        return ++line;
    }
    
    //obviously not a label so treat as normal instruction
    sscanf(buf, "%s %[^','], %[^','], %s", cur.opcode, cur.argv1, cur.argv2, cur.argv3);
    if(!strcmp(cur.opcode, "la")){
        convert_la(cur,line);
        //need to increase line twice to account for converting one instruction to two
        line++;
        return ++line;
    }
    else{
        cur.addr = line*4;
        instructionSet[curSize] = cur;
        curSize++;
        return ++line;
    }
   
}
//this will just split la into an lui and ori instruction
//note we never add la to the instructionSet array
void convert_la(Instruction cur, int line){
    Instruction lui, ori;
    strcpy(lui.opcode,"lui");
    strcpy(lui.argv1, cur.argv1);
    strcpy(lui.argv2, cur.argv2);
    lui.addr = line * 4;
    instructionSet[curSize] = lui;
    curSize++;
   
    strcpy(ori.opcode, "ori");
    strcpy(ori.argv1, cur.argv1);
    strcpy(ori.argv2, cur.argv1);
    strcpy(ori.argv3, cur.argv2);
    //fancy part here to account for adding an instruction
    ori.addr = (line+1) * 4;
    instructionSet[curSize] = ori;
    curSize++;
   

}


//this is where we filter our instructions sliding them into certain functions so that those
//functions can take care of them
void itrInstr(){
    int i;
    //lets iterate over instructionSet (our array of instructions)
    //i relates to which instruction it is
    for(i = 0;i < curSize; i++){
        //so if our instructions opcode matches a ceratin element in our inst dictionary hand it off 
        //to the appropriate function 
        if(!strcmp(instructionSet[i].opcode, inst[1])||!strcmp(instructionSet[i].opcode, inst[6])||!strcmp(instructionSet[i].opcode, inst[7])||!strcmp(instructionSet[i].opcode, inst[8]))
            i_format(i);
        else if(!strcmp(instructionSet[i].opcode, inst[0])||!strcmp(instructionSet[i].opcode, inst[2])||!strcmp(instructionSet[i].opcode, inst[4]))
            r_format(i);
        else if(!strcmp(instructionSet[i].opcode, inst[9]))
            j_format(i);
        else if(!strcmp(instructionSet[i].opcode, "ori"))
            ori_inst(i);
        else if(!strcmp(instructionSet[i].opcode, "lui"))
            lui_inst(i);
        else
            printf("Invalid token: %s", instructionSet[i].opcode);
    }

}
void r_format(const int loc){
    //r format consists of three instructions: ADD NOR and SLL
    int hex = 0, funct = 0, rd = 0, rs = 0, rt = 0, shamt = 0;
    Format f1;
    rt = getReg(instructionSet[loc].argv3);
    rs = getReg(instructionSet[loc].argv2);
    //assign opcodes
    if(!strcmp(instructionSet[loc].opcode, inst[0]))
        funct = 32;
    else if(!strcmp(instructionSet[loc].opcode, inst[2])) 
        funct = 39;
    else if(!strcmp(instructionSet[loc].opcode, inst[4])) 
        funct = 0;
    if(funct == 0){
        rt = getReg(instructionSet[loc].argv2);
        shamt = atoi(instructionSet[loc].argv3);
        rs = 0;
    }
    //determine register numbers based off args (ie $t0 is converted to 8)
    rd = getReg(instructionSet[loc].argv1);
    //this is a formula for getting the machine code
    //we are basically just inserting numbers into their appropriate spot
    hex = (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    //we call insertF to store hex value and address print later
    insertF(hex, loc);
}
void i_format(const int loc){
    //i types are pretty similar except for bne, lw, and sw which we need to handle specially
    //bne has opcode 5 and location inst[8]
    int hex = 0, op = 0, rt = 0, rs = 0, imm;
    char tmpreg[4];
    if(!strcmp(instructionSet[loc].opcode, inst[1]))
        op = 8;
    else if(!strcmp(instructionSet[loc].opcode, inst[3])) 
        op = 13;
    else if(!strcmp(instructionSet[loc].opcode, inst[5])) 
        op = 15;
    else if(!strcmp(instructionSet[loc].opcode, inst[6]))
        op = 43;
    else if(!strcmp(instructionSet[loc].opcode, inst[7])) 
        op = 35;
    else if(!strcmp(instructionSet[loc].opcode, inst[8]))
        op = 5;
    //again lets convert $t0 to 8, etc.
    rt = getReg(instructionSet[loc].argv1);
    rs = getReg(instructionSet[loc].argv2);
    imm = atoi(instructionSet[loc].argv3);
    //sw and lw have a special second argument that needs to be reparsed
    if(op == 43 || op == 35)
    {
        sscanf(instructionSet[loc].argv2, "%d (%[^')'])", &imm, tmpreg);
        rs = getReg(tmpreg);
    }
    //bne is weird, it flips rs and rt and its imm field is pc relative so some extra work is done
    if(op == 5)
    { 
        rs = getReg(instructionSet[loc].argv1);
        rt = getReg(instructionSet[loc].argv2);
        imm = getLabelAddr(instructionSet[loc].argv3);
        //imm now equal to how many instructions away from PC we are
        //this is based off pc relative form
        imm = (imm - loc * 4) / 4;
        imm = imm & 0xFFFF;
    }
    hex = (op << 26) | (rs << 21) | (rt << 16) | imm;
    insertF(hex, loc);

}
//for jumps we need to use pseudo direct addressing to determine we are jumping to 
void j_format(const int loc){
    int targaddr, op = 2;
    int curAddrMSB = 0, hex = 0, tmpLoc;
    tmpLoc = loc * 4;
    //targaddr will hold the label address we are going to 
    targaddr = getLabelAddr(instructionSet[loc].argv1);
    //grab 4 MSB of our current addr
    curAddrMSB = (unsigned int)(tmpLoc & 0xF0000000) >> 28;
    hex = (op << 26) | (curAddrMSB << 22) | (targaddr >> 2);
    insertF(hex, loc);
}
void insertF(const int hex, const int loc){
    Format f1;
    f1.hexa = hex;
    f1.addr = loc * 4;
    //store instr for funsies and maybe for debugging
    f1.instr = instructionSet[loc];
    fArray[fCurSize] = f1;
    fCurSize++;
}
//search through my array of labels and grab the addr when we have a match
int getLabelAddr(const char * label){
    int i = 0;
    for(i = 0; i <= lCurSize; i++)
        if(!strcmp(labelSet[i].name, label))
            return labelSet[i].addr;
       
}
void lui_inst(const int loc){
    int op = 15, rt, imm, hex, labelAddr;
    rt = getReg(instructionSet[loc].argv1);
    labelAddr = getLabelAddr(instructionSet[loc].argv2);
    //grab top 16 bits
    imm = (unsigned int)(labelAddr & 0xFFFF0000) >> 16;
    hex = (op << 26) | (0 << 21) | (rt << 16) | imm;
    insertF(hex, loc);
}
void ori_inst(const int loc){
    int op = 13, rt, imm, hex, labelAddr;
    rt = getReg(instructionSet[loc].argv1);
    labelAddr = getLabelAddr(instructionSet[loc].argv3);
    //grab bottom 16 bits
    imm = labelAddr & 0xFFFF;
    hex = (op << 26) | (rt << 21) | (rt << 16) | imm;
    insertF(hex, loc);

}
//returns decimal value of register
int getReg(const char *reg){
    if(!strcmp(reg, "$t0"))
        return 8;
    if(!strcmp(reg, "$t1"))
        return 9;
    if(!strcmp(reg, "$t2"))
        return 10;
    if(!strcmp(reg, "$t3"))
        return 11;
    if(!strcmp(reg, "$t4"))
        return 12;
    if(!strcmp(reg, "$t5"))
        return 13;
    if(!strcmp(reg, "$t6"))
        return 14;
    if(!strcmp(reg, "$t7"))
        return 15;
    if(!strcmp(reg, "$s0"))
        return 16;
    if(!strcmp(reg, "$s1"))
        return 17;
    if(!strcmp(reg, "$s2"))
        return 18;
    if(!strcmp(reg, "$s3"))
        return 19;
    if(!strcmp(reg, "$s4"))
        return 20;
    if(!strcmp(reg, "$s5"))
        return 21;
    if(!strcmp(reg, "$s6"))
        return 22;
    if(!strcmp(reg, "$s7"))
        return 23;
    if(!strcmp(reg, "$0"))
        return 0;

    return -1;

}

