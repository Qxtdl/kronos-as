#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../global.h"
#include "instruction.h"
#include "../util.h"
#include "assembler.h"
#include "label.h"

static inline unsigned long branch_target_to_ul(const char *s) {
    label_t *label = search_rom_label(s);
    if (!label) {
        return str_literal_to_ul(s);
    }
    else {
        return label->address;
    }
}

static inline unsigned long memory_operand_to_ul(const char *s) {
    label_t *label = search_ram_label(s);
    if (!label) {
        app_abort("memory_operand_to_ul()", "Label could not be found.")
    }
    else {
        return label->address;
    }
}

#define x(y) (strtoul(y + 1, NULL, 10))

instruction_t get_instruction(char *line) {
    instruction_t instruction = {0};

    char *save;
    char *opcode = strtok_r(line, ", ", &save);
    char *dest = strtok_r(NULL, ", ", &save);
    char *rs1 = strtok_r(NULL, ", ", &save);
    char *rs2 = strtok_r(NULL, ", ", &save);

    if (!opcode) return instruction;

    for (size_t i = 0; i < sizeof(opcode_table)/sizeof(opcode_table[0]); i++) {
        if (!strcmp(opcode, opcode_table[i].name)) {
            instruction.type = INST_REAL;
            instruction.opcode = opcode_table[i].opcode;
            break;
        }
    }
    if (instruction.type == INST_NULL) {
        for (size_t i = 0; i < sizeof(pseudo_opcode_table)/sizeof(pseudo_opcode_table[0]); i++) {
            if (!strcmp(opcode, pseudo_opcode_table[i].name)) {
                instruction.type = INST_PSEUDO;
                instruction.pseudo_opcode = pseudo_opcode_table[i].pseudo_opcode;
                break;
            }
        }        
    }

    if (instruction.type == INST_REAL)
    switch (instruction.opcode) {
        case OPCODE_ADD:
        case OPCODE_SUB:
        case OPCODE_MUL:
        case OPCODE_DIV:
        case OPCODE_AND:
        case OPCODE_OR:
        case OPCODE_XOR:
        case OPCODE_NAND:
        // 3 operand
            instruction.dest = x(dest);
            instruction.rs1 = x(rs1);
            instruction.rs2 = strtoul(rs2 + 1, NULL, 10);
            break;
        case OPCODE_ADDI:
        case OPCODE_ADDI_HS:
        // rd rs1 immediate
            instruction.dest = x(dest);
            instruction.rs1 = x(rs1);
            instruction.imm = str_literal_to_ul(rs2);
        break;
        case OPCODE_LW:
        // load word
            instruction.dest = x(dest);
            instruction.rs2 = x(rs1);
            break;
        case OPCODE_SW:
        // rs1 rs2
            instruction.rs1 = x(dest);
            instruction.rs2 = x(rs1);
            break;
        case OPCODE_BEQ:
            instruction.dest = x(dest);
            instruction.rs1 = x(rs1);
            instruction.imm = branch_target_to_ul(rs2);
            break;
        case OPCODE_JAL:
            instruction.dest = x(dest);
            instruction.imm = branch_target_to_ul(rs1);
            break;
        case OPCODE_JALR:
            instruction.dest = x(dest);
            instruction.rs1 = x(rs1);
            break;            
    }
    else if (instruction.type == INST_PSEUDO)
    switch (instruction.pseudo_opcode) {
        case PSEUDO_OPCODE_NOP:
            instruction.opcode = OPCODE_ADDI;
            break;
        case PSEUDO_OPCODE_LI:
            instruction.opcode = OPCODE_ADDI;
            instruction.dest = x(dest);
            instruction.imm = str_literal_to_ul(rs1);
            break;
        case PSEUDO_OPCODE_LIL:
            instruction.opcode = OPCODE_ADDI;
            instruction.dest = x(dest);
            instruction.imm = memory_operand_to_ul(rs1);
            break;
        case PSEUDO_OPCODE_LI_HS:
            instruction.opcode = OPCODE_ADDI_HS;
            instruction.dest = x(dest);
            instruction.imm = str_literal_to_ul(rs1);
            break;            
        case PSEUDO_OPCODE_J:
            instruction.opcode = OPCODE_JAL;
            instruction.imm = branch_target_to_ul(dest);
    }

    return instruction;
}

uint16_t last_instruction_address = 1;

void put_instruction(instruction_t instruction) {
    static instruction_t last_instruction = {INST_NULL};
    // if (last_instruction_address > (uint16_t)sizeof(rom)/sizeof(rom[0])) {
    //     quick_abort("ROM overflow");
    // }
    if (instruction.type == INST_NULL) return;

    uint32_t encoded_instruction = 0;
    encoded_instruction |= instruction.opcode << 21;
    encoded_instruction |= instruction.dest << 18;
    encoded_instruction |= instruction.rs1 << 15;
    encoded_instruction |= instruction.rs2 << 12;
    encoded_instruction |= (instruction.imm & 0x7FFF);

    printf("%x\n", encoded_instruction);
    rom[last_instruction_address++] = encoded_instruction;
}