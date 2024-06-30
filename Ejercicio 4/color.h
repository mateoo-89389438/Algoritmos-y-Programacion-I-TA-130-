#ifndef COLOR_H
#define COLOR_H

typedef enum {
    COLOR_RESET,
    COLOR_ROJO,
    COLOR_VERDE,
    COLOR_AMARILLO,
    COLOR_AZUL,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_BLANCO
} color_t;

// recibe un enumerativo de color y devuelve su codigo ANSI
char *color_escape(color_t c);




#endif
