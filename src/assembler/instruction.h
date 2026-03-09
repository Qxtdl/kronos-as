#pragma once

#include <stdint.h>

typedef enum {
    INST_NULL,
    INST_REAL,
    INST_PSEUDO
} inst_type_t;

typedef enum {
    OPCODE_ADD     = 0b100,
    OPCODE_SUB     = 0b1000,
    OPCODE_MUL     = 0b10000,
    OPCODE_DIV     = 0b100000,
    OPCODE_AND     = 0b1000000,
    OPCODE_OR      = 0b10000000,
    OPCODE_XOR     = 0b100000000,
    OPCODE_NAND    = 0b1000000000,
    OPCODE_ADDI    = 0b10000000000,
    OPCODE_JALR    = 0b101,
    OPCODE_JAL     = 0b1001,
    OPCODE_BEQ     = 0b10001,
    OPCODE_BEQ_FAR = 0b100001,
    OPCODE_LW      = 0b110,
    OPCODE_SW      = 0b1010,
    OPCODE_ADDI_HS = 0b10000000011,
} opcode_t;

typedef enum {
    PSEUDO_OPCODE_NOP,
    PSEUDO_OPCODE_LI,
    PSEUDO_OPCODE_LI_HS,
    PSEUDO_OPCODE_LIL,
    PSEUDO_OPCODE_J
} pseudo_opcode_t;

// PATCH
// preprocessor breaks dots in the assembler
// so remove dots in opcodes

static struct {
    const char *name;
    opcode_t opcode;
} const opcode_table[] = {
    {"add", OPCODE_ADD},
    {"sub", OPCODE_SUB},
    {"mul", OPCODE_MUL},
    {"div", OPCODE_DIV},
    {"and", OPCODE_AND},
    {"or", OPCODE_OR},
    {"xor", OPCODE_XOR},
    {"nand", OPCODE_NAND},
    {"addi", OPCODE_ADDI},
    {"jalr", OPCODE_JALR},
    {"jal", OPCODE_JAL},
    {"beq", OPCODE_BEQ},
    {"beq.far", OPCODE_BEQ_FAR},
    {"lw", OPCODE_LW},
    {"sw", OPCODE_SW},
    {"addi.hs", OPCODE_ADDI_HS},
};

static struct {
    const char *name;
    pseudo_opcode_t pseudo_opcode;
} const pseudo_opcode_table[] = {
    {"nop", PSEUDO_OPCODE_NOP},
    {"li", PSEUDO_OPCODE_LI},
    {"li.hs", PSEUDO_OPCODE_LI_HS},
    {"lil", PSEUDO_OPCODE_LIL},
    {"j", PSEUDO_OPCODE_J},
};

typedef struct {
    inst_type_t type;
    union {
        opcode_t opcode;
        pseudo_opcode_t pseudo_opcode;
    };
    uint8_t dest;
    uint8_t rs1;
    uint8_t rs2;
    uint16_t imm;
} instruction_t;

static const instruction_t nop = {
    INST_REAL,
    {.opcode = OPCODE_ADDI},
    0,
    0,
    0,
    0
};

static struct {
    opcode_t first;
    opcode_t second;
    instruction_t mitigation;
} const hazards[] = {
    {OPCODE_SW, OPCODE_JAL, nop} // SW followed by a JAL
};

extern uint16_t last_instruction_address;

instruction_t get_instruction(char *line);
void put_instruction(instruction_t instruction);