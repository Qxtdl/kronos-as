#pragma once

#include <stddef.h>

void *smalloc(size_t size);
void *srealloc(void *ptr, size_t size);
char *sstrdup(const char *s);
unsigned long str_literal_to_ul(const char *s);