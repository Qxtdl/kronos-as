#include <stdlib.h>
#include <string.h>

#include "../../util.h"
#include "macro.h"

char *expand_macro(char *s, macro_t macro, const char *after) {
    while (1) {
        after = strstr(s, "#expansion allowed\n");
        char *save;
        char *found_macro = strstr(after, macro.name);
        if (!found_macro) return s;

        char *buf = NULL;
        buf = strappend(buf, macro.name);

        char *body = sstrdup(macro.body);
        char *macro_line = strtok_r(sstrdup(found_macro), " ", &save);
        char *macro_arg = strtok_r(NULL, " ", &save);
        for (size_t i = 0; i < macro.argument_count; i++) {
            strappend(buf, " ");
            strappend(buf, macro_arg);

            body = strreplace(body, macro.arguments[i], macro_arg);
            macro_arg = strtok_r(NULL, " ", &save);
        }

        s = strreplace(s, buf, body);

        buf = NULL;
    }
}

