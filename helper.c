
/*
static inline Um_instruction sloadInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(SLOAD, a, b, c);
}


static inline Um_instruction sstoreInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(SSTORE, a, b, c);
}

static inline Um_instruction addInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(ADD, a, b, c);
}

static inline Um_instruction mulInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(MUL, a, b, c);
}

static inline Um_instruction divInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(DIV, a, b, c);
}

static inline Um_instruction nandInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(NAND, a, b, c);
}

static inline Um_instruction haltInstruction(void) 
{
        return three_register(HALT, 0, 0, 0);
}

static inline Um_instruction activateInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(ACTIVATE, 0, b, c);
}

static inline Um_instruction inactivateInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(INACTIVATE, 0, 0, c);
}

static inline Um_instruction outputInstruction(Um_register c)
{
        assert((0 <= c) && (c <= 255));
        return three_register(OUT, 0,0,c);
}

static inline Um_instruction inInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(IN, a, b, c);
}

static inline Um_instruction nandInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(NAND, a, b, c);
}

static inline Um_instruction loadpInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(LOADP, a, b, c);
}


static inline Um_instruction loadvalInstruction(unsigned ra, unsigned val)
{
        return (13 << 28) | (ra << 25) | val;
}


//-------------------------------------------------------------------

static inline void append(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}*/

//-------------------------------------------------------

#include <stdlib.h> 
#include <stdio.h>
#include <stdint.h>
#include <assert.h>


typedef uint32_t Um_register;
typedef uint32_t Um_instruction;

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

int getOP(uint32_t instruction)
{
    return instruction >> 28;
}

int getRegA(uint32_t instruction)
{
    return instruction << 23 >> 29;
}

int getRegB(uint32_t instruction)
{
    return instruction << 26 >> 29;
}

int getRegC(uint32_t instruction)
{
    return instruction << 29 >> 29;
}

int getValueLoad(uint32_t instruction)
{
    return instruction << 7 >> 7;
}

int getRegLoad(uint32_t instruction)
{
    return instruction << 4 >> 29;
}


Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
        return (op << 28) | (ra << 6) | (rb << 3) | rc;

}

static inline Um_instruction cmovInstruction(Um_register a, Um_register b, Um_register c) 
{
        return three_register(CMOV, a, b, c);
}
uint32_t memory[8];

void setReg(uint32_t value, int reg)
{
    assert(reg >= 0 && reg < 8);
    memory[reg] = value;
}

int getRegValue(int reg)
{
    assert(reg >= 0 && reg < 8);
    return memory[reg];
}

//-------------------Start of instructions------------------------


void cmov(Machine_T um, Um_word instruction)
{
    if (getRegC(instruction) != 0) {
        setReg(um, getRegValue(um, getRegB(instruction)), getRegA(instruction));
    }
}

void add(Machine_T um, Um_word instruction)
{
    Um_word digit1 = getRegValue(um, getRegB(instruction));
    Um_word digit2 = getRegValue(um, getRegC(instruction));
    Um_word sumReg = getRegA(instruction);
    setReg(um, (digit1 + digit2), sumReg);
}


void mul(Machine_T um, Um_word instruction)
{
    Um_word digit1 = getRegValue(um, getRegB(instruction));
    Um_word digit2 = getRegValue(um, getRegC(instruction));
    Um_word sumReg = getRegA(instruction);
    setReg(um, (digit1 * digit2), sumReg);
}
void divide(Machine_T um, Um_word instruction)
{
    Um_word digit1 = getRegValue(um, getRegB(instruction));
    Um_word digit2 = getRegValue(um, getRegC(instruction));
    Um_word sumReg = getRegA(instruction);
    setReg(um, (digit1 / digit2), sumReg);
}
void nand(Machine_T um, Um_word instruction)
{
    Um_word digit1 = getRegValue(um, getRegB(instruction));
    Um_word digit2 = getRegValue(um, getRegC(instruction));
    Um_word sumReg = getRegA(instruction);
    setReg(um, (~(digit1 & digit2)), sumReg);
}




//---------------------------NOT YET IMPLEMENTED DUE TO NEED FOR SEQUENCE---------------------------


void sload(Machine_T um,Um_word instruction)
{
    printf("sload\n");
}

void sstore(Machine_T um, Um_word instruction)
{
    printf("sstore\n");
}
void activate(Machine_T um, Um_word instruction)
{
    printf("activate\n");
}
void inactivate(Machine_T um, Um_word instruction)
{
    printf("inactivate\n");
}
void out(Machine_T um, Um_word instruction)
{
    Um_word rc = getRegValue(getRegC(instruction));
    assert(rc < 256 && rc > 0);
    printf("%d", rc);
}
void in(Machine_T um, Um_word instruction)
{
    printf("in\n");
}
void loadp(Machine_T um, Um_word instruction)
{
    printf("loadp\n");
}
void loadval(Machine_T um, Um_word instruction)
{
    printf("loadval\n");
}





int main()
{
/*    uint32_t instruction = 0x4fffff5f;
    printf("%d\n", getOP(instruction));
    printf("%d\n", getRegA(instruction));
    printf("%d\n", getRegB(instruction));
    printf("%d\n", getRegC(instruction));
    uint32_t loadInstruction = 0x5ffda354;
    printf("%d\n", getValueLoad(loadInstruction));
    printf("%d\n", getRegLoad(loadInstruction));*/

    int ra = 0;
    int rb = 1;
    int rc = 3;

    memory[0] = 1;
    memory[1] = 10;
    memory[2] = 3;
    memory[3] = 10;

//    for(int i = 0; i < 14; i++)

    uint32_t instruction = cmovInstruction(ra,rb,rc);
    printf("%d\n", getRegC(instruction));
    switch (10) 
    { 
        case CMOV:       cmov(instruction);//works
                         break; 
        case SLOAD:      sload( instruction);
                         break; 
        case SSTORE:     sstore( instruction);
                         break; 
        case ADD:        add( instruction);
                         break;
        case MUL:        mul( instruction);
                         break;
        case DIV:        divide( instruction);
                         break;
        case NAND:       nand( instruction); 
                         printf("divide %d\n", getRegValue(ra));
                         break;
        case HALT:       halt( instruction); 
                         break;
        case ACTIVATE:   activate( instruction); 
                         break;
        case INACTIVATE: inactivate( instruction); 
                         break;
        case OUT:        out( instruction); 
                         break;
        case IN:         in( instruction);
                         break;
        case LOADP:      loadp( instruction);
                         break;
        default:         loadval( instruction);
                         break;   
    } 

    return 0;
}
