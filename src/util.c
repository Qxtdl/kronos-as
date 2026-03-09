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

char *strappend(char *s, const char *src) {
    if (!s) return sstrdup(src);
    s = srealloc(s, strlen(s) + strlen(src) + 1);
    return strcat(s, src);
}

// char *strreplace(char *text, const char *needle, const char *replacement) {
//     size_t text_len = strlen(text);
//     size_t replacement_len = strlen(replacement);
//     size_t needle_len = strlen(needle);
//     char *new_text = NULL;
    
//     int i = 0;
//     bool loop = false;
//     while (1) {
//         char *occurence;
//         for (int y = 0; y <= i; y++) {
//             occurence = strstr(loop ? new_text : text, needle);
//         }
//         if (!occurence) return loop ? new_text : text;
        
//         char *after = strdup(occurence + replacement_len);
//         new_text = realloc(loop ? new_text : strdup(text), occurence - (loop ? new_text : text) + replacement_len + needle_len + 1 + 9999);
//         new_text[occurence - (loop ? new_text : text)] = '\0';
//         strcat(new_text, replacement);
//         strcat(new_text, after);
        
//         free(after);
//         loop = true;
//         printf("%s\n", new_text);
//     }
//     return NULL;
// }


char *strreplace(char *orig, const char *rep, const char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

char *open_file(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file)
        app_abort("open_file()", "The file could not be found")
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