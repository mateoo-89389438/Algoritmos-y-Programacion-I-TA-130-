#include <stdio.h>

int main() {
    FILE *fo = fopen("archivo.txt", "w");
    if(fo == NULL) return 1;

    fprintf(fo, "Hola mundo\n");
    fputc('x', fo);
    fprintf(fo, "%f\n", 5.6);

    if(fclose(fo) == EOF) {
        fprintf(stderr, "Ojo, debes haber perdido datos...\n");
    }

    return 0;
}