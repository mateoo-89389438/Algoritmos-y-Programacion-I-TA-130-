#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINEA 100

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




typedef struct {
	// El prompt:
	char prompt[MAX_LINEA];

	// El historial, la cantidad de cadenas y el índice de la línea que se está editando:
	char (*historial)[MAX_LINEA];
	int nhistorial, ihistorial;

	// La línea que se está editando, su longitud y la posición del cursor:
	char *linea;
	int nlinea, ilinea;

	// La copia de la configuración de terminal original:
	struct termios config_original;
} terminal_t;


terminal_t *terminal_crear(const char *prompt) {

	terminal_t * terminal = malloc(sizeof(terminal_t));
	if (terminal == NULL) {
		return NULL;
	}

	strcpy(terminal->prompt, prompt); //Inicializar el prompt con el prompt pasado como parámetro.

	terminal->nhistorial = 1;
	terminal->ihistorial = 0;
	terminal->historial = malloc(terminal->nhistorial * sizeof(char[MAX_LINEA]));
	if (terminal->historial == NULL) {
		free(terminal);
		return NULL;
	}
	terminal->historial[0][0] = '\0'; //Crear un historial de tamaño 1, con una cadena vacía.

	terminal->linea = terminal->historial[0]; //linea apuntará a esta cadena del historial.
	terminal->nlinea = 0;
	terminal->ilinea = 0;

	// Obtención de la configuración original de la terminal
	if (tcgetattr(0, &terminal->config_original) != 0) {
		// No pudo obtenerse la configuración actual de la terminal
		free(terminal->historial);
		free(terminal);
		return NULL;
	}

	// Configuración en modo no echo y sin buffer
	struct termios config_nueva = terminal->config_original;
	config_nueva.c_lflag &= ~ICANON & ~ECHO;
	if (tcsetattr(0, TCSAFLUSH, &config_nueva) != 0) {
		// No pudimos reconfigurar la terminal
		free(terminal->historial);
		free(terminal);
		return NULL;
	}

	return terminal;
}



void terminal_destruir(terminal_t *t){
	free(t->historial);
	// Restauración de la configuración original 
	tcsetattr(0, TCSAFLUSH, &t->config_original); 
	free(t);
}



int terminal_leer(terminal_t *t){

	char c = getchar();   

	//OP1: EOF 
	if(c == 4){
		return EOF;
	}

	
	
	// OP2: ENTER 
	if (c == '\n') {

	  //Verifico que la línea que se estaba editando no fuera la última del historial
	  if (t->ihistorial < t->nhistorial - 1) {
	      //Mando la línea actual al historial
	      strcpy(t->historial[t->nhistorial - 1], t->linea);
	  }

	  //agregar una nueva línea en blanco al historial
	  char (*historial_nuevo)[MAX_LINEA] = realloc(t->historial, (t->nhistorial + 1) * sizeof(char[MAX_LINEA]));
	  if (historial_nuevo == NULL) {
	      return 0; 
	  }
	  t->historial = historial_nuevo;
	  t->nhistorial++;
	  t->ihistorial = t->nhistorial - 1;

	  //Escribir el '\0' en la línea actual.
	  t->historial[t->nhistorial - 1][0] = '\0';
	  // Ajustar todo para que esta sea la nueva línea a editar.
	  t->linea = t->historial[t->nhistorial - 1];
	  t->nlinea = 0;
	  t->ilinea = 0;
	  return c;
	}
	

	//OP3: RETROCESO 
	//*Esta funcion borra el caracter ANTERIOR al cursor
	if (c == 127) {
	    if (t->ilinea > 0) {
	        memmove(&t->linea[t->ilinea - 1], &t->linea[t->ilinea], t->nlinea - t->ilinea);
	        t->nlinea--;
	        t->ilinea--;
	        t->linea[t->nlinea] = '\0';
	    }
	    return c;
	}


	//OP4: ESC
	if (c == 27 && getchar() == '[') {

		char d = getchar();
		
		
		// IZQUIERDA 
		if ( d == 'D') {
			if ( ((t->ilinea)>0 ) && (t->ilinea)<=(t->nlinea) ) {
				t->ilinea--;
			}
			return d; 
		}
		//DERECHA 
		else if( d == 'C'){
			if( (t->ilinea) >= 0 && (t->ilinea)<(t->nlinea)){
				t->ilinea++;
			}
			return d;
		}
		//INICIO 
		else if( d == 'H'){
			t->ilinea = 0;
			return d;
		}
		//FIN
		else if( d == 'F'){
			if(t->ilinea>=0 && (t->ilinea)<=(t->nlinea)){
				t->ilinea = t->nlinea;
			}
			return d;
		}
		// ARRIBA 
		if (d == 'A') {
			if (t->ihistorial > 0) {
				//guardo la cadena actual en el historial
				t->linea = t->historial[t->ihistorial];
				t->ihistorial--;
				//recupero la cadena siguiente del historial
				t->linea = t->historial[t->ihistorial];
				t->nlinea = strlen(t->linea);
				t->ilinea = t->nlinea;
				return d;
			}
		}
		// ABAJO 
		else if (d == 'B') {
			if (t->ihistorial >= 0 && t->ihistorial < (t->nhistorial - 1)) {
				//guardo la cadena actual en el historial
				t->linea = t->historial[t->ihistorial];
				t->ihistorial++;
				//recupero la cadena siguiente del historial
				t->linea = t->historial[t->ihistorial];
				t->nlinea = strlen(t->linea);
				t->ilinea = t->nlinea;
				return d;
			}
		}
		//SUPRIMIR 
		//*Esta funcion borra el caracter EN LA POSICION del cursor
		//*El cursor no se mueve de donde estaba
		else if (d == '3' && isprint(getchar())) { 
		    if (t->ilinea < t->nlinea) {
		        memmove(&t->linea[t->ilinea], &t->linea[t->ilinea + 1], t->nlinea - t->ilinea);
		        t->nlinea--;
		        t->linea[t->nlinea] = '\0';
		    }
		    return d;
		}

	}

	//OP5: OTRA LETRA IMPRIMIBLE 
	if (isprint(c)) {
	    memmove(&t->linea[t->ilinea + 1], &t->linea[t->ilinea], t->nlinea - t->ilinea);
	    // Insertar el nuevo carácter
	    t->linea[t->ilinea] = c;
	    t->ilinea++;
	    t->nlinea++;
	    t->linea[t->nlinea] = '\0'; //por las dudas meto el \0 al final
	    return c;
	}

	return c;
}


void terminal_imprimir(const terminal_t *t) {
	//llevo el cursor al principio de la linea
	printf("\033[1G");
	//limpiar la línea
	printf("\033[2K");
	// imprimir el prompt y la línea actual
	printf("%s%s", t->prompt, t->linea);
	// posicionar el cursor donde corresponda
	printf("\033[%luG", (strlen(t->prompt) + t->ilinea + 1));
}


char *terminal_historial(const terminal_t *t, int i) {
	if (t->historial != NULL && t->nhistorial > 0 && i <= 0 && i > -(t->nhistorial)) {
		return t->historial[(t->nhistorial)+i-1];
	}
	return NULL;
}



int main(void) {
	terminal_t *t = terminal_crear("$ ");
	if(t == NULL)
		return 1;

	terminal_imprimir(t);

	int c;
	while((c = terminal_leer(t)) != EOF) {
		if(! (rand() % 50))
			printf("\033[2K\033[1G%s<<< Hola, soy texto interrumpiendo!\n%s", color_escape(COLOR_ROJO), color_escape(COLOR_RESET));

		if(c == '\n') {
			printf("\033[2K\033[1G%s>>> %s\n%s", color_escape(COLOR_VERDE), terminal_historial(t, -1), color_escape(COLOR_RESET));
		}
		terminal_imprimir(t);
	}

	terminal_destruir(t);
	return 0;
}

