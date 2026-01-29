#pragma once

#include <stdint.h>

typedef struct {
    const char *name;
    uint16_t address;
} label_t;

void push_rom_label(label_t label);
label_t *search_rom_label(const char *name);
void push_ram_label(label_t label);
label_t *search_ram_label(const char *name);