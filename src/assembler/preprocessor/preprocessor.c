#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../util.h"
#include "macro.h"

char *preprocess(char *s) {
    char *text = sstrdup(s);
    char *line = strtok(text, "\n");
    char *directive;
    while (line != NULL) {
        if ((directive = strstr(line, "#"))) {
            char *save;
            if (!strncmp(directive+1, "define", 6)) {
                strtok_r(directive, " ", &save);
                char *needle = strtok_r(NULL, " ", &save);
                char *replacement = strtok_r(NULL, " ", &save);
                s = strreplace(s, needle, replacement);
            }
            else if (!strncmp(directive+1, "include", 7)) {
                char *needle = strdup(directive);
                char *includepath = strtok_r(directive, "\"", &save);
                includepath = strtok_r(NULL, "\"", &save);
                char *replacement = open_file(includepath);
                s = preprocess(strreplace(s, needle, replacement));
            }
            else if (!strncmp(directive+1, "macro", 5)) {
                // strtok_r(directive, " ", &save);

                // macro_t macro = {0};
                
                // macro.name = strdup(strtok_r(NULL, " ", &save));
                // char *arg = strtok_r(NULL, " ", &save), *last_arg;
                // while (arg) {
                //     macro.arguments = realloc(macro.arguments, ++macro.argument_count * sizeof(const char *));
                //     macro.arguments[macro.argument_count - 1] = strdup(arg);

                //     last_arg = arg;
                //     arg = strtok_r(NULL, " ", &save);
                // }
                // // Get macro body
                // char *macro_line = strtok(NULL, "\n");
                // while (1) {
                //     if (!strncmp(macro_line, "#endmacro", 9)) break;
                //     macro.body = strappend((char *)macro.body, macro_line);
                //     macro.body = strappend((char *)macro.body, "\n");
                //     macro_line = strtok(NULL, "\n");
                // }

                // s = expand_macro(s, macro, strstr(s, "#expansion allowed\n"));
            }
        }

        line = strtok(NULL, "\n");
    }
    return s;
}