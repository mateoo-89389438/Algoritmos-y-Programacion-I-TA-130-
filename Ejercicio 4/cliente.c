#include "comunicador.h"
#include "terminal.h"
#include "cadenas.h"
#include "color.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_STRING 100

typedef enum {
	PRIVMSG,
	NICK,
	JOIN,
	PART,
	NAMES,
	TOPIC,
	LIST,
	USERS,
	QUIT,
	PING,
	PONG,
} comandosIRC_t;


int main(int argc, char *argv[]) {

	if (argc != 4) {
		fprintf(stdout, "Uso: %s servidor puerto nick\n", argv[0]);
		return 1;
	}

	char *servidor = argv[1];
	int puerto = atoi(argv[2]);
	char *nick = argv[3];

	// Creacion del comunicador
	comunicador_t *c = comunicador_crear();
	if (c == NULL) {
		fprintf(stderr, "Error al crear el comunicador\n");
		return 1;
	}

	// Conexion al servidor
	if (!comunicador_conectar(c, servidor, puerto)) {
		fprintf(stderr, "%s\n", comunicador_get_error(c));
		comunicador_destruir(c);
		return 1;
	}

	int sockfd = comunicador_get_sockfd(c);

	//Conexion exitosa -> nick al servidor
	if (comunicador_esta_conectado(c)){
		//handshake
		char *user = malloc(MAX_STRING*sizeof(char));
		if(user == NULL) return 1;
		sprintf(user, "USER %s host server :%s\n", nick, nick);
		write(sockfd, user, strlen(user));

		char *nicks = malloc(MAX_STRING*sizeof(char));
		if(nicks == NULL){
			free(user);
			return 1;
		} 
		sprintf(nicks, "NICK %s\n", nick);
		write(sockfd, nicks, strlen(nicks));
		free(user);
		free(nicks);
	}

	// Creo una estructura terminal
	terminal_t *t = terminal_crear("");
	if (t == NULL) {
		comunicador_destruir(c);
		return 1;
	}

	terminal_imprimir(t);
	fflush(stdout);

	char comandosIRC[][MAX_STRING] = {"PRIVMSG", "NICK", "JOIN", "PART", "NAMES", "TOPIC", "LIST", "USERS", "QUIT", "PING", "PONG"};

	int fd;
	while((fd = comunicador_esperar_datos(c)) != -1 ) {

		// Sé que hay datos en stdin
		if(fd == 0){

			int c;
			if((c = terminal_leer(t)) != EOF) { 

				if(c == '\n') {

					char *s = terminal_historial(t, -1);
					if( s == NULL){
						break;
					}
					//imprimo aca directo lo que se escribio
					printf("\033[2K\033[1G%s<<< %s\n%s", color_escape(COLOR_VERDE), s, color_escape(COLOR_RESET));	

					//Si es un comando
					if(s[0] == '/'){
						// borro el caracter '/'
						for(size_t i = 0; i < strlen(s); i++){
							s[i] = s[i+1];
						}
						//saco los dos primeros campos
						char campo0[MAX_STRING]; 
						char campo1[MAX_STRING];
						extraer_campo(campo0, s, 0);
						extraer_campo(campo1, s, 1);

						size_t comandoIRC = (buscar_cadena(campo0, comandosIRC, 11));
						
						//cambio el prompt					
						if ( comandoIRC == PRIVMSG || comandoIRC == JOIN){
							sprintf(t->prompt, "%s", campo1);
						}
						

						//Agrego el caracter ':' al inicio del 3er campo
						if(cantidad_campos(s) > 2){
							size_t pos = strlen(campo0) + strlen(campo1) + 2; 
							size_t len = strlen(s);

							for(size_t i = len; i >= pos; i--){
								s[i + 1] = s[i]; 
							}
							s[pos] = ':';
						}
						
						s[strlen(s)] = '\n';
						//print al servidor
						write(sockfd, s, strlen(s));
						
						if( comandoIRC == QUIT){
							break;
						}
					}
					else{
						//agrego "privmsg+prompt"
						char *msg = malloc(MAX_STRING*sizeof(char));
						if(msg == NULL) break;
						sprintf(msg, "privmsg %s :%s\n", t->prompt, s);

						//print al servidor
						write(sockfd, msg, strlen(msg));
						free(msg);
					}
				}
			}
			
		}
		else{ 
		// Sé que hay datos en fd para leer con read()

			char l[MAX_STRING];
			
			if(leer_linea_archivos(l, fd)){ 
				char campo0[MAX_STRING];
				extraer_campo(campo0, l, 0);
				size_t comandoIRC0 = buscar_cadena(campo0, comandosIRC, 11);

				char campo1[MAX_STRING];
				extraer_campo(campo1, l, 1);
				size_t comandoIRC1 = buscar_cadena(campo1, comandosIRC, 11);
				
				if( comandoIRC1 == PRIVMSG){
					char campo3[MAX_STRING]; 
					extraer_campo(campo3, l, 3);
					//mensaje de otro usuario
					fprintf(stdout,"\033[2K\033[1G%s>>> %s\n%s", color_escape(COLOR_ROJO), campo3, color_escape(COLOR_RESET));
				}

				if( comandoIRC0 == PING){
					//respuesta al ping
					char *pong = malloc(MAX_STRING*sizeof(char));
					if(pong == NULL) break;
					sprintf(pong, "PONG :%s\n",campo1);
					write(sockfd, pong, strlen(pong));
					free(pong);
					fprintf(stdout,"\033[2K\033[1G%s Respondiendo a PING...\n%s", color_escape(COLOR_MAGENTA), color_escape(COLOR_RESET));
				}

				fprintf(stdout,"\033[2K\033[1G%s*** %s\n%s", color_escape(COLOR_AZUL), l, color_escape(COLOR_RESET));
			}		
		}
		terminal_imprimir(t);
		fflush(stdout);
	}
	comunicador_destruir(c);
	terminal_destruir(t);
	return 0;
}




