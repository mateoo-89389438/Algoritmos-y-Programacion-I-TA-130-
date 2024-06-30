#include <stdint.h>
#include <stdio.h>

#define MASKB 0xFF // 1111 1111 
#define SHIFTB 8

//EJ1
uint32_t bextr(uint32_t a, uint16_t b) {
	// Extraer la parte baja de b
	uint8_t inicio = b & MASKB;
	// Extraer la parte alta de b
	uint8_t longitud = (b >> SHIFTB) & MASKB;

	// Muevo a la derecha para dejar todos los bits deseados al inicio
	// Muevo a la izquierda para obtener el resultado
	return (a >> inicio) & ((1 << longitud) - 1);
}

//EJ2
terminal_t *terminal_clonar(const terminal_t *t) {
	terminal_t *c = malloc(sizeof(terminal_t));
	if(c == NULL) return NULL;

	c->historial = malloc((t->nhistorial * MAX_STRING) * sizeof(char));
	if(c->historial == NULL) {
		free(c);
		return NULL;
	}

	memcpy(c->historial, t->historial, t->nhistorial * MAX_STRING);
	c->nhistorial = t->nhistorial;
	return c;
}


//EJ3
char *centrar(const char *cadena, size_t largo) {
	char *s = malloc(largo + 1);
	if(s == NULL) return NULL;

	size_t nc = strlen(cadena);
	size_t espacios = (largo - nc) / 2;

	for(size_t i = 0; i < espacios; i++)
		s[i] = ' ';
	strcat(s, cadena);
	for(size_t j = espacios + nc; j < largo; j++)
		s[j] = ' ';
	s[largo] = '\0';

	return s;

}


int main() {
	//EJ1
	uint32_t a = 0b1001001110111101;
	uint16_t b = 0x0804; // inicio = 4, longitud = 8
	uint32_t resultado = bextr(a, b);
	printf("Resultado: %u\n", resultado); // Debería imprimir 59 (00111011 en binario)
	return 0;

	//EJ2
	terminal_t *c = terminal_clonar(&t);

	for(size_t i = 0; i < c->nhistorial; i++)
		printf("%zd: %s\n", i, c->historial[i]);

	free(c->historial);
	free(c);



	//EJ3
	char *s = centrar("hola", 10);
	printf("#%s#\n", s);
	free(s);
	return 0;
}











