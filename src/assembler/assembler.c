#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../global.h"
#include "../util.h"
#include "directive.h"
#include "instruction.h"
#include "label.h"
#include "directive.h"
#include "preprocessor.h"

uint32_t rom[65536];
uint16_t ram[65536];

uint16_t last_ram_address = 0;

static inline char *filter_line(char *line) {
    if (strstr(line, "#")) return NULL;
    if (strstr(line, ".")) return NULL;
    if (strstr(line, "//")) return NULL;
    return line;
}

static void parse_labels(char *text) {
    char *line = strtok(text, "\n");
    while (line != NULL) {
        process_directive(line, false);
        if (!(line = filter_line(line))) goto nextline;

        char *save;
        if (strstr(line, "::")) {
            push_ram_label((label_t){strtok_r(strdup(line), ":", &save), last_ram_address});
        }
        else if (strstr(line, ":")) {
            push_rom_label((label_t){strtok_r(strdup(line), ":", &save), last_instruction_address});
        }        
        else if (get_instruction(line).type != INST_NULL) last_instruction_address++;
        
        nextline: line = strtok(NULL, "\n");
    }
    last_instruction_address = 1;
}

void assemble_asm(char *text) {
    text = preprocess(text);
    char *new_text = sstrdup(text);
    parse_labels(new_text);
    free(new_text);

    char *line = strtok(text, "\n");
    while (line != NULL) {
        process_directive(line, true);
        if (!(line = filter_line(line))) goto nextline;

        instruction_t instruction = get_instruction(line);
        put_instruction(instruction);

        nextline: line = strtok(NULL, "\n");
    }
}