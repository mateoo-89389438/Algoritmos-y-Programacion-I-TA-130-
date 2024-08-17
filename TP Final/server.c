#include "server.h"
#include "usuario.h"
#include "canal.h"
#include "protocoloIRC.h"
#include "lista.h"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <stdio.h>

#define POLLRDHUP 0x2000 
#define TIMEOUT 1000 // TIMEOUT:[ms] // -1 no se termina nunca
#define MAX_CLIENTES 100
#define PONG_TIME 60*1

struct server {
	char *idservidor; // nombre del servidor
	int sockfd; 	// fd principal del servidor
	char *error; 	// cadena con el error del servidor, si es que falló
	lista_t *usuarios;// lista enlazada de usuarios conectados al servidor
	lista_t *canales; // lista enlazada de canales existentes en el servidor
	// no hay usuarios ni canales repetidos
	char *codigoPING; // codigo que se le envia a todos los usuarios
};


server_t *server_crear(char *nombre_servidor) {
	server_t *s = malloc(sizeof(server_t));
	if (s == NULL) return NULL;
	

	s->sockfd = -1;
	s->error = NULL;
	s->usuarios = lista_crear();  
	if(s->usuarios == NULL){
		free(s);
	}
	s->canales = lista_crear();   
	if(s->canales == NULL){
		lista_destruir(s->usuarios, NULL);
		free(s);
		return NULL;
	}

	s->idservidor = malloc(strlen(nombre_servidor)+1);
	if(s->idservidor == NULL){
		lista_destruir(s->usuarios, NULL);
		lista_destruir(s->canales, NULL);
		free(s);
		return NULL;
	}
	strcpy(s->idservidor, nombre_servidor);

	char cadenaPING[] = "zzz";
	s->codigoPING = malloc(strlen(cadenaPING)+1);
	if(s->codigoPING == NULL){
		free(s->idservidor);
		lista_destruir(s->usuarios, NULL);
		lista_destruir(s->canales, NULL);
		free(s);
		return NULL;
	}

	strcpy(s->codigoPING, cadenaPING);

	return s;
}


void server_destruir(server_t *server) {

	// Libero a cada uno de los usuarios
	if (server->usuarios) {
		lista_iter_t *iter = lista_iter_crear(server->usuarios);    
		while (!lista_iter_al_final(iter)) {
			struct usuario *usuario_actual = lista_iter_ver_actual(iter);
			close(usuario_get_fd(usuario_actual));
			usuario_destruir(usuario_actual);
			lista_iter_avanzar(iter);
		}
		lista_iter_destruir(iter);
		lista_destruir(server->usuarios, NULL); 
	}


	// Libero a cada uno de los canales
	if (server->canales) {
		lista_iter_t *iter_canales = lista_iter_crear(server->canales);
		if (iter_canales) {
			while (!lista_iter_al_final(iter_canales)) {
				struct canal *canal_actual = lista_iter_ver_actual(iter_canales);
				if (canal_actual) {
					canal_destruir(canal_actual);  
				}
				lista_iter_avanzar(iter_canales);
			}
			lista_iter_destruir(iter_canales);
		}
		lista_destruir(server->canales, NULL); 
	}
	// Libero el nombre del servidor
	if (server->idservidor) {
		free(server->idservidor);
	}
	if (server->codigoPING) {
		free(server->codigoPING);
	}
	// Libero el server
	free(server);
}


bool server_conectar(server_t *server, const int puerto){

	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server->sockfd = sockfd;
	if(sockfd == -1){
		server->error = "ERROR Creación del socket";
		return false;
	}

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(puerto);

	if((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0){
		server->error = "ERROR No pudo conectarse el socket al puerto";
		return false;
	}

	if((listen(sockfd, 5)) != 0){
		server->error = "ERROR Falla al escuchar";
		return false;
	}

	fprintf(stdout, "Servidor creado y escuchando!\n");
	return true;
}

char *server_get_idservidor(const server_t *server){
	return server->idservidor;
}

int server_get_sockfd(const server_t *server){
	return server->sockfd;
}

char *server_get_error(const server_t *server){
	return server->error;
}

lista_t *server_get_usuarios(const server_t *server){
	return server->usuarios;
}

lista_t *server_get_canales(const server_t *server){
	return server->canales;
}

char *server_get_codigoPING(const server_t *server){
	return server->codigoPING;
}


struct usuario *server_aceptar_usuario(server_t *server, const int sockfd){

	struct sockaddr_in cli;
	socklen_t len = sizeof(cli);
	int fd = accept(sockfd, (struct sockaddr*)&cli, &len); // fd del nuevo usuario
	if(fd < 0){
		server->error = "ERROR Falló aceptar al cliente";
		return false;
	}

	int direccion = ntohl(cli.sin_addr.s_addr); //direccion de IP

	struct usuario *nuevo_usuario = usuario_crear(direccion, fd);
	if(nuevo_usuario == NULL) return false;
	return nuevo_usuario;
}

void server_rechazar_usuario(server_t *server, struct usuario *user){
	close(usuario_get_fd(user));
	free(user);
}


bool server_agregar_usuario(server_t *server, struct usuario *user, const char *nick, const char *nombre){
	// Completo el usuario con su nick y nombre 
	if(usuario_completar(user, nick, nombre)){
		if(lista_esta_vacia(server->usuarios)){
			return lista_insertar_primero(server->usuarios, user);			
		}
		return lista_insertar_ultimo(server->usuarios, user);		
	}
	return false;
}

bool server_eliminar_usuario(server_t *server, const int fd){

	// Busco el usuario correspondiente a este fd y lo borro	
	lista_iter_t *iter = lista_iter_crear(server->usuarios);
	if(iter == NULL) return false;

	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if (usuario_get_fd(usuario_actual) == fd) {
			close(usuario_get_fd(usuario_actual)); //cierro el canal de comunicacion
			usuario_destruir(usuario_actual);
			lista_iter_borrar(iter);
			lista_iter_destruir(iter);
			return true;
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return false;
}

struct usuario *server_get_usuario_nombre(const server_t *server, const char *nombre_usuario){
	lista_iter_t *iter = lista_iter_crear(server->usuarios);
	if (iter == NULL) return NULL;

	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if (!strcmp(usuario_get_nombre(usuario_actual), nombre_usuario)) {
			struct usuario *usuario_encontrado = usuario_actual;
			lista_iter_destruir(iter);
			return usuario_encontrado;
		}
		lista_iter_avanzar(iter);
	}

	// no se encontró el usuario => el usuario no existe
	lista_iter_destruir(iter);
	return NULL; 
}

struct usuario *server_get_usuario_fd(const server_t *server, const int fd){

	lista_iter_t *iter = lista_iter_crear(server->usuarios);
	if (iter == NULL) return NULL;

	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if (usuario_get_fd(usuario_actual) == fd) {
			struct usuario *usuario_encontrado = usuario_actual;
			lista_iter_destruir(iter);
			return usuario_encontrado;
		}
		lista_iter_avanzar(iter);
	}

	// no se encontró el usuario => el usuario no existe
	lista_iter_destruir(iter);
	return NULL; 
}


bool server_agregar_canal(server_t *server, struct canal *canal){
	return lista_insertar_ultimo(server->canales, canal);
}

struct canal *server_get_canal(const server_t *server, const char *nombre_canal){
	lista_iter_t *iter = lista_iter_crear(server->canales);
	if (iter == NULL) return NULL;

	while (!lista_iter_al_final(iter)) {
		struct canal *canal_actual = lista_iter_ver_actual(iter);
		if (strcmp(canal_get_nombre(canal_actual), nombre_canal) == 0) {
			struct canal *canal_encontrado = canal_actual;
			lista_iter_destruir(iter);
			return canal_encontrado;
		}
		lista_iter_avanzar(iter);
	}
	// no se encontró el canal => el canal no existe
	lista_iter_destruir(iter);
	return NULL; 
}

bool server_eliminar_canal(server_t *server, const char *nombre_canal){

	lista_iter_t *iter = lista_iter_crear(server->canales);
	if (iter == NULL) return false;

	while (!lista_iter_al_final(iter)){
		struct canal *canal_actual = lista_iter_ver_actual(iter);
		if (!strcmp(canal_get_nombre(canal_actual), nombre_canal)) {
			canal_destruir(canal_actual);
			lista_iter_borrar(iter);
			lista_iter_destruir(iter);
			return true;
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return false; 
}


static bool server_esta_conectado(const server_t *server){
	return server->sockfd != -1;
}

int server_esperar_datos(server_t *server){

	if(! server_esta_conectado(server)) {
		server->error = "Servidor no conectado";
		return -1;
	}
	
	struct pollfd fds[1 + MAX_CLIENTES];
	// main fd para nuevas conexiones
	fds[0].fd = server->sockfd;
	fds[0].events = POLLIN;
	size_t nfds = 1;

	lista_iter_t *iter = lista_iter_crear(server->usuarios);

	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		fds[nfds].fd = usuario_get_fd(usuario_actual);
		fds[nfds].events = POLLIN | POLLHUP | POLLRDHUP; //reviso los 3 tipos de eventos
		nfds++;
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);


	if (poll(fds, nfds, TIMEOUT) < 0) {
		server->error = "Falla esperando datos";
		close(server->sockfd);
		server->sockfd = -1;
		return -1;
	}

	for (size_t i = 0; i < nfds; i++) {
		if (fds[i].revents & POLLIN) {
			return fds[i].fd;
		}
		else if ((fds[i].revents & POLLHUP) || (fds[i].revents & POLLRDHUP)){
			if (i == 0) {
				server->error = "Error en el socket del servidor";
				return -1;
			} 
			else{
				if (!server_eliminar_usuario(server, fds[i].fd)) {
					return -1;
				}
				return fds[i].fd;
			}
		}
	}

	server->error = "Se llegó al timeout y no hubo datos nuevos";
	return -1;
}


void server_mensaje_codigo(const server_t *server, const struct usuario *user, const char *codigo, const char *mensaje){
	size_t aviso_len = strlen(server->idservidor) + strlen(codigo) + strlen(usuario_get_nick(user)) + strlen(mensaje) + 5;
	char *aviso = malloc(aviso_len);
	sprintf(aviso, "%s %s %s %s\n", server->idservidor, codigo, usuario_get_nick(user), mensaje);
	write(usuario_get_fd(user), aviso, strlen(aviso));
	free(aviso);
}


bool server_mensaje_canal(const server_t *server, const struct canal *canal , const char *mensaje){
	if(canal_get_usuarios(canal) != NULL){
		lista_iter_t *iter = lista_iter_crear(canal_get_usuarios(canal));
		if (iter == NULL) {
			return false;
		}
		while (!lista_iter_al_final(iter)) {
			struct usuario *usuario_actual = lista_iter_ver_actual(iter);
			write(usuario_get_fd(usuario_actual), mensaje, strlen(mensaje));
			lista_iter_avanzar(iter);
		}
		lista_iter_destruir(iter);
		return true;
	}
	return false;
}

void server_mensaje_general(const server_t *server, const char *mensaje){
	if(server->usuarios == NULL){
		return;
	}
	
	lista_iter_t *iter = lista_iter_crear(server->usuarios);
	if (iter == NULL) return;
	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		write(usuario_get_fd(usuario_actual), mensaje, strlen(mensaje));
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
}



void server_verificar_PONGS(server_t *server, const time_t tiempo_actual) {
	lista_iter_t *iter = lista_iter_crear(server->usuarios);
	if (iter == NULL) return;

	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if (difftime(tiempo_actual, usuario_get_ultimoPONG(usuario_actual)) > PONG_TIME) {
		    lista_iter_avanzar(iter); 
		    comandoQUIT(server, usuario_actual, "porque no respondió el PING a tiempo");  
		} 
		else {
		    lista_iter_avanzar(iter);
		}

	}
	lista_iter_destruir(iter);
}



