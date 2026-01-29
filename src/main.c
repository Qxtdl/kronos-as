#include <stdio.h>
#include <string.h>

#include "global.h"
#include "util.h"
#include "assembler/assembler.h"

static const char *open_file(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char *text = smalloc(file_size + 1);
    size_t read_size = fread(text, 1, file_size, file);
    if ((long)read_size != file_size)
        app_abort("open_file()", "Error reading file")
    text[file_size] = '\0';
    return text;
}

static void write_file(const char *filepath, void *data, int unit_size, size_t amount) {
    FILE *fptr = fopen(filepath, "wb");
    fwrite(data, unit_size, amount, fptr);
}

int main(int argc, const char **argv) {
    if (argc <= 1)
        app_abort("main()", "You did not provide enough arguments. Use --help")
    if (!strcmp(argv[1], "--help")) {
        printf("kronos-as <asm file> <bin output> <ram output>\n");
        exit(0);
    }
    else if (argc <= 2)
        app_abort("main()", "You need to provide a output bin file")
    assemble_asm((char *)open_file(argv[1]));
    write_file(argv[2], rom, 4, 65536);
    write_file(argv[3], ram, 2, 65536);
}