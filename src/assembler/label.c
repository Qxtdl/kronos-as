#include "../global.h"
#include "label.h"
#include "../util.h"

#include <stddef.h>
#include <string.h>

static label_t *rom_labels = NULL, *ram_labels = NULL;
static size_t rom_labels_size = 0, ram_labels_size = 0;

void push_rom_label(label_t label) {
    rom_labels = srealloc(rom_labels, sizeof(label_t) * ++rom_labels_size);
    memcpy(&rom_labels[rom_labels_size - 1], &label, sizeof(label_t));
}

label_t *search_rom_label(const char *name) {
    for (size_t i = 0; i < rom_labels_size; i++) {
        if (!strcmp(rom_labels[i].name, name)) {
            return &rom_labels[i];   
        }
    }
    return NULL;
}

void push_ram_label(label_t label) {
    ram_labels = srealloc(ram_labels, sizeof(label_t) * ++ram_labels_size);
    memcpy(&ram_labels[ram_labels_size - 1], &label, sizeof(label_t));
}

label_t *search_ram_label(const char *name) {
    for (size_t i = 0; i < ram_labels_size; i++) {
        if (!strcmp(ram_labels[i].name, name)) {
            return &ram_labels[i];   
        }
    }
    return NULL;
}

label_t *search_label(const char *name) {
    label_t *label;
    label = search_rom_label(name);
    if (!label)
        label = search_ram_label(name);
    if (label) return label;
    return NULL;
}