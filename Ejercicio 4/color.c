#include "color.h"

#include <stddef.h>

char * codigos_escape[] = {
    [COLOR_RESET] = "\033[0;0m",
    [COLOR_ROJO] = "\033[1;31m",
    [COLOR_VERDE] = "\033[1;32m",
    [COLOR_AMARILLO] = "\033[1:33m",
    [COLOR_AZUL] = "\033[1;34m",
    [COLOR_MAGENTA] = "\033[1;35m",
    [COLOR_CYAN] = "\033[1;36m",
    [COLOR_BLANCO] = "\033[1;37m",
};


char *color_escape(color_t c) {
    if (c < COLOR_RESET || c > COLOR_BLANCO) {
        return NULL; 
    }

    char * codigo = codigos_escape[c];
    return codigo;
}


