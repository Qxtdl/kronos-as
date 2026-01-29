#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "global.h"

void *smalloc(size_t size) {
    void *alloc = malloc(size);
    if (!alloc)
        app_abort("smalloc()", "Failed to allocate memory")
    return alloc;
}

void *srealloc(void *ptr, size_t size) {
    void *alloc = realloc(ptr, size);
    if (!alloc)
        app_abort("srealloc()", "Failed to allocate memory")
    return alloc;    
}

char *sstrdup(const char *s) {
    char *alloc = strdup(s);
    if (!alloc)
        app_abort("ssstrdup()", "Failed to allocate memory");
    return alloc;
}

unsigned long str_literal_to_ul(const char *s) {
    if (!strncmp(s, "0x", 2)) return strtoul(s, NULL, 16);
    if (!strncmp(s, "0b", 2)) return strtoul(s, NULL, 2);
    return strtoul(s, NULL, 10);
}