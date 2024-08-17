#include "cadenas.h"
#include "server.h"
#include "protocoloIRC.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>


#define PUERTO_DEFAULT 6667
#define MAX_STRING 100
#define PING_TIME 60*1
#define BREAK_TIME 60*5


int flag = 0;
server_t *mi_servidor;

void liberar_recursos() {
	flag = 1;
    	// mensaje de despedida
	server_mensaje_general(mi_servidor, "Se cierra el servidor\n");
    	// Liberar el servidor
	if (mi_servidor != NULL) {
	  	// cierro el canal de comunicacion
		close(server_get_sockfd(mi_servidor));
		server_destruir(mi_servidor);
	}
	printf("\nRecursos liberados. Cerrando el servidor...\n");
}

int main(int argc, char *argv[]){

	int puerto;
	if(argc == 1){
		puerto = PUERTO_DEFAULT;
	}
	else if(argc == 2){
		puerto = atoi(argv[1]);

	}
	else{
		fprintf(stdout, "Uso: %s <puerto>\n", argv[0]);
		return 1;
	}

	char *nombre_servidor = "mi_servidor [TA130]";

	// Creo el servidor
	mi_servidor = server_crear(nombre_servidor);

	if(!server_conectar(mi_servidor, puerto)){
		fprintf(stdout, "%s\n", server_get_error(mi_servidor));
		server_destruir(mi_servidor);
		return 1;
	}
	fprintf(stdout, "Servidor escuchando en el puerto %d\n", puerto);
	int sockfd = server_get_sockfd(mi_servidor);

	// Se activa si se recibe un ctrl+C
	signal(SIGINT, liberar_recursos);

	time_t tiempo_base = time(NULL);
	time_t tiempo_datos = tiempo_base; //solo incializo la variable

	while(1){
		if(flag == 1){
			break;
		}
		int fd;
		if(( fd = server_esperar_datos(mi_servidor) ) != -1 ){ 
			tiempo_datos = time(NULL);
			
			// se que hay datos en el socket del servidor
			if(fd == sockfd){
				struct usuario *nuevo_usuario = server_aceptar_usuario(mi_servidor, sockfd);

				// Comando USER: USER usuario host server nombrereal:
				char *s1 = leer_linea_archivos(usuario_get_fd(nuevo_usuario));
				if((cantidad_campos(s1)) != 5){
					server_rechazar_usuario(mi_servidor, nuevo_usuario);
					free(s1);
					continue;
				}
				char *nombre = comandoUSER(s1);
				free(s1);
				if(nombre == NULL){
					server_rechazar_usuario(mi_servidor, nuevo_usuario);
					continue;
				}

				// Comando NICK: NICK nick
				char *s2 = leer_linea_archivos(usuario_get_fd(nuevo_usuario));
				if((cantidad_campos(s2)) != 2){
					server_rechazar_usuario(mi_servidor, nuevo_usuario);
					free(nombre);
					free(s2);
					continue;
				}

				char *nick = comandoNICK(s2);
				if(nick == NULL){
					server_rechazar_usuario(mi_servidor, nuevo_usuario);
					free(nick);	
					free(nombre);
					free(s2);
					continue;
				}

				// Verifico que el nick no esté ocupado
				while (!verificarNICK(mi_servidor, nick)) {
					char *aviso = malloc(MAX_STRING * sizeof(char));
					sprintf(aviso, "%s 433 nick ocupado\n", server_get_idservidor(mi_servidor));
					write(usuario_get_fd(nuevo_usuario), aviso, strlen(aviso));
					free(aviso);

					s2 = leer_linea_archivos(usuario_get_fd(nuevo_usuario));
					nick = comandoNICK(s2);

					if (nick == NULL) {
						free(s2);
						free(nombre);
						server_rechazar_usuario(mi_servidor, nuevo_usuario);
						continue;
					}
				}

				if(server_agregar_usuario(mi_servidor, nuevo_usuario, nick, nombre)){
					char *bienvenida = malloc(MAX_STRING * sizeof(char));
					sprintf(bienvenida, "Bienvenido al IRC %s", usuario_get_tag(nuevo_usuario));
					server_mensaje_codigo(mi_servidor, nuevo_usuario, "001", bienvenida);
					free(bienvenida);
				}
				free(s2);
				free(nombre);
				free(nick);	
			}
			// se que hay datos en algun fd para leer y manipular
			else{				
				// veo que usuario es el que me esta hablando
				struct usuario *usuario = server_get_usuario_fd(mi_servidor, fd);            

				// Obtengo el comando que me mandaron
				char *s3 = leer_linea_archivos(fd);

				// Trabajo la linea leida
				char campo0[MAX_STRING];
				extraer_campo(campo0, s3, 0);
				size_t comandoIRC = buscar_cadena(campo0, comandosIRC, 11);

				if( comandoIRC == NICK ){ 
					char *nuevo_nick = comandoNICK(s3);
					// Verifico que el nick no esté ocupado
					while(!verificarNICK(mi_servidor, nuevo_nick)){
						server_mensaje_codigo(mi_servidor, usuario, "433", "nick ocupado");
						free(s3);
						free(nuevo_nick);
						s3 = leer_linea_archivos(fd);
						nuevo_nick = comandoNICK(s3); 
					}
					// Como el nick está libre lo seteo
					usuario_cambiar_nick(mi_servidor, usuario, nuevo_nick);
					free(nuevo_nick);
				}
				else if( comandoIRC == JOIN){ 
					if(cantidad_campos(s3) == 2){
						comandoJOIN(mi_servidor, usuario, s3);
					}
				}
				else if( comandoIRC == LIST ){ 
					if(cantidad_campos(s3) == 1){
						comandoLIST(mi_servidor, usuario);
					}
				}
				else if( comandoIRC == NAMES ){ 
					if(cantidad_campos(s3) == 2){
						char nombre_canal[MAX_STRING];
						extraer_campo(nombre_canal, s3, 1);
						comandoNAMES(mi_servidor, usuario, nombre_canal);
					}
				}
				else if( comandoIRC == PART ){ 
					if(cantidad_campos(s3) == 2){
						char nombre_canal[MAX_STRING];
						extraer_campo(nombre_canal, s3, 1);
						comandoPART(mi_servidor, usuario, nombre_canal);
					}
				}
				else if( comandoIRC == PONG){ 
					if(!comandoPONG(mi_servidor, usuario, s3)){
						comandoQUIT(mi_servidor, usuario, "porque contestó mal el PING");
					}
				}
				else if(comandoIRC == PRIVMSG){ 
					if(cantidad_campos(s3) == 3){
						comandoPRIVMSG(mi_servidor, usuario, s3);
					}
				}
				else if(comandoIRC == QUIT){ 
					if(cantidad_campos(s3) == 1){
						comandoQUIT(mi_servidor, usuario, "porque pidió salir");
					}
				}
				else if(comandoIRC == TOPIC){ 
					if( (cantidad_campos(s3) == 2) || (cantidad_campos(s3) == 3) ){
						comandoTOPIC(mi_servidor, usuario, s3);
					}
				}
				else if(comandoIRC == USERS){ 
					if(cantidad_campos(s3) == 1){
						comandoUSERS(mi_servidor, usuario);	
					}
				}
				free(s3);
			}
		}
		else{
			if(flag == 0){
				// Si ya pasó un tiempo (PING_TIME) le mando el ping a cada usuario
				time_t tiempo_actual = time(NULL); // Obtengo el tiempo actual
				if (difftime(tiempo_actual, tiempo_base) >= PING_TIME) {
					comandoPING(mi_servidor);
					tiempo_base = tiempo_actual; // Actualizo el tiempo base
					server_verificar_PONGS(mi_servidor, tiempo_actual);
				}
			}
		}
		// Si ya pasó un tiempo (BREAK_TIME) sin recibir datos cierro todo 
		time_t tiempo_actual = time(NULL); // Obtengo el tiempo actual
		if (difftime(tiempo_actual, tiempo_datos) >= BREAK_TIME){
			fprintf(stdout, "%s\n", server_get_error(mi_servidor));
			server_destruir(mi_servidor);
			return 1;
		}	
	}	
	return 0;
}	

