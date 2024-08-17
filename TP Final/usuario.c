#include "usuario.h"
#include "canal.h"
#include "server.h"
#include "lista.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define MAX_STRING 100

struct usuario {
	uint32_t IP;
	char *nombre; 	// puede haber nombres repetidos
	char *nick; 	// no hay nicks repetidos
	char *tag; 		// no hay tags repetidos
	int fd; 		// fd con el que se comunican servidor y usuario
	time_t ultimoPONG; // hora exacta en la que mandó su último pong
	// al inicio se setea la hora de ingreso al servidor
};

struct usuario *usuario_crear(const uint32_t IP, const int fd){

	struct usuario *nuevo_usuario = malloc(sizeof(struct usuario));
	if( nuevo_usuario == NULL) return NULL;

	nuevo_usuario->IP = IP;
	nuevo_usuario->fd = fd;

	return nuevo_usuario;
}

bool usuario_completar(struct usuario *user, const char *nick, const char *nombre){
	user->nick = malloc( (strlen(nick) + 1)*sizeof(char) );
	if(user->nick == NULL){
		return false;
	}
	user->nombre = malloc( (strlen(nombre) + 1)*sizeof(char) );
	if(user->nombre == NULL){
		free(user->nick);
		return false;
	}

	// Copio el nick y el nombre
	strcpy(user->nick, nick);
	strcpy(user->nombre, nombre);

	size_t tag_len = strlen(user->nick) + strlen(user->nombre) + 20;
	user->tag = malloc(tag_len*sizeof(char));
	if(user->tag == NULL){
		free(user->nick);
		free(user->nombre);
		return false;
	}
	
	// Creo el tag
	sprintf(user->tag, "%s!~%s@%d", user->nick, user->nombre, user->IP);

	// Agrego su hora de entrada al servidor como "primer PONG"
	time_t hora_actual = time(NULL); // hora actual
	user->ultimoPONG = hora_actual;
	return true;

}


void usuario_destruir(struct usuario *user){
	free(user->tag);
	free(user->nick);
	free(user->nombre);
	free(user);
}

uint32_t usuario_get_IP(const struct usuario *user){
	return user->IP;
}

char *usuario_get_nombre(const struct usuario *user){
	return user->nombre;
}

char *usuario_get_nick(const struct usuario *user){
	return user->nick;
}


char *usuario_get_tag(const struct usuario *user){
	return user->tag;
}

int usuario_get_fd(const struct usuario *user){
	return user->fd;
}

time_t usuario_get_ultimoPONG(const struct usuario *user){
	return user->ultimoPONG;
}



bool usuario_cambiar_nick(const server_t *server, struct usuario *user, const char *nuevo_nick){
	//mensaje a todos avisando el cambio de nick
	//tagviejo NICK nicknuevo
	char *aviso = malloc(strlen(user->tag) + strlen(nuevo_nick) + 7);
	if(aviso == NULL) return false;
	sprintf(aviso, "%s NICK %s\n", user->tag, nuevo_nick);

	// Itero sobre todos los canales del servidor
	lista_iter_t *iter = lista_iter_crear(server_get_canales(server));
	if (iter == NULL) {
		free(aviso);
		return false;
	}

	while (!lista_iter_al_final(iter)) {
		struct canal *canal_actual = lista_iter_ver_actual(iter);
		if(canal_verificar_usuario(canal_actual, user)){
			//le envio el mensaje a todos los usuarios del canal
			server_mensaje_canal(server, canal_actual, aviso);	
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	free(aviso);
	// Le cambio el nick al usuario
	strcpy(user->nick, nuevo_nick);
	
	// creo el nuevo_tag
	size_t tag_len = strlen(nuevo_nick) + strlen(user->nombre) + 10 + 4;
	char *nuevo_tag = malloc(tag_len * sizeof(char));
	if(nuevo_tag == NULL) return false;
	sprintf(nuevo_tag, "%s!~%s@%d", nuevo_nick, user->nombre, user->IP);
	// Le cambio el tag al usuario
	strcpy(user->tag, nuevo_tag);
	free(nuevo_tag);
	return true;
}

bool usuario_join_canal(struct usuario *user, const char *nombre_canal, server_t *server){
	// compruebo si existe el canal:
	struct canal *canal = server_get_canal(server, nombre_canal);
	//Si el canal no existe: 
	// lo creo y lo agrego a la lista de canales del servidor
	if(canal == NULL){
		canal = canal_crear(nombre_canal);
		if(canal == NULL) return false;
		if(!server_agregar_canal(server, canal)){
			canal_destruir(canal);
			return false;
		}
		// Hago admin al usuario
		canal_set_admin(canal, user->nick);
	}
	//agrego este usuario a la lista del respectivo canal
	return canal_agregar_usuario(canal, user);
}

void usuario_set_ultimoPONG(struct usuario *user){
	user->ultimoPONG = time(NULL);
}




