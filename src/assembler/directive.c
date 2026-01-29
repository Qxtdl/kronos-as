#include <string.h>
#include <stdbool.h>

#include "../util.h"
#include "assembler.h"
#include "instruction.h"

static inline char *filter_line(char *line) {
    if (strstr(line, "#")) return NULL;
    if (strstr(line, "//")) return NULL;
    return line;
}

void process_directive(char *line, bool second_pass) {
    if (!(line = filter_line(line))) return;

    char *directive;
    if (!(directive = strstr(line, "."))) return;

    char *save;
    if (!strncmp(directive+1, "romorg", 6)) {
        strtok_r(directive, " ", &save);
        char *address = strtok_r(NULL, " ", &save);
        last_instruction_address = str_literal_to_ul(address);
    }
    if (!strncmp(directive+1, "ramorg", 6)) {
        strtok_r(directive, " ", &save);
        char *address = strtok_r(NULL, " ", &save);
        last_ram_address = str_literal_to_ul(address);
    }
    else if (second_pass && !strncmp(directive+1, "word", 4)) {
        strtok_r(directive, " ", &save);
        while (1) {
            const char *value = strtok_r(NULL, " ", &save);
            if (!value) break;
            uint16_t word = str_literal_to_ul(value);
            ram[last_ram_address++] = word;
        }
    }
}