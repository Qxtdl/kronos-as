#pragma once

#include <stdlib.h>

typedef struct {
    const char *name;
    size_t argument_count;
    const char **arguments;
    const char *body;
} macro_t;

char *expand_macro(char *s, macro_t macro, char *after);
