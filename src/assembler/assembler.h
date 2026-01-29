#pragma once

#include <stdint.h>

extern uint32_t rom[65536];
extern uint16_t ram[65536];

extern uint16_t last_ram_address;

void assemble_asm(char *text);