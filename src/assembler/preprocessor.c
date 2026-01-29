#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "../util.h"

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


char *strreplace(char *orig, char *rep, char *with) {
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

// static inline char *filter_line(char *line) {
//     if (strstr(line, ".")) return NULL;
//     //if (strstr(line, "//")) return NULL;
//     return line;
// }

char *preprocess(char *s) {
    char *text = sstrdup(s);
    char *line = strtok(text, "\n");
    char *directive;
    while (line != NULL) {
        //if (!(line = filter_line(line))) goto nextline;
        
        if ((directive = strstr(line, "#"))) {
            char *save;
            if (!strncmp(directive+1, "define", 6)) {
                strtok_r(directive, " ", &save);
                char *needle = strtok_r(NULL, " ", &save);
                char *replacement = strtok_r(NULL, " ", &save);
                s = strreplace(s, needle, replacement);
            }
        }

        nextline: line = strtok(NULL, "\n");
    }
    free(text);
    return s;
}