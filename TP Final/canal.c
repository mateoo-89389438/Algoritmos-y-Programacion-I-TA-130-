#include "canal.h"
#include "usuario.h"
#include "lista.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRING 100

struct canal {
	char *nombre;
	char *topic; 
	lista_t *usuarios; //lista enlazada de usuarios que pertenecen a este canal
	// no hay usuarios repetidos
	char *admin; //nick del usuario administrador del canal
	// hay un unico administrador. Este puede ser eliminado pero no reemplazado 
};

struct canal *canal_crear(const char *nombre){
	struct canal *nuevo_canal = malloc(sizeof(struct canal));
	if (nuevo_canal == NULL) return NULL;
	
	// De entrada no se ponen usuarios ni topic, solo nombre
	nuevo_canal->nombre = malloc(MAX_STRING * sizeof(char));
	if (nuevo_canal->nombre == NULL) {
		free(nuevo_canal);
		return NULL;
	}

	strcpy(nuevo_canal->nombre, nombre);
	nuevo_canal->topic = NULL;
	nuevo_canal->admin = NULL;
	nuevo_canal->usuarios = lista_crear(); 
	if (nuevo_canal->usuarios == NULL) {
		free(nuevo_canal->nombre);
		free(nuevo_canal);
		return NULL;
	}
	return nuevo_canal;
}

void canal_destruir(struct canal *canal){
	free(canal->nombre);
	lista_destruir(canal->usuarios, NULL);
	if(canal->topic){
		free(canal->topic);
	}
	if(canal->admin){
		free(canal->admin);
	}
	free(canal);
}

bool canal_agregar_usuario(struct canal *canal, struct usuario *nuevo_user){
	return lista_insertar_ultimo(canal->usuarios, nuevo_user);
}

bool canal_verificar_usuario(struct canal *canal, struct usuario *user) {
	if (canal == NULL || user == NULL) {
		return false;
	}

	lista_iter_t *iter = lista_iter_crear(canal->usuarios);
	if (iter == NULL) {
		return false;
	}

	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if (!strcmp(usuario_get_nick(usuario_actual), usuario_get_nick(user))){
			// el usuario está en el canal
			lista_iter_destruir(iter);
			return true;
		}
		lista_iter_avanzar(iter);
	}

	// el usuario no está en el canal
	lista_iter_destruir(iter);
	return false;
}


bool canal_remover_usuario(struct canal *canal, struct usuario *user){

	lista_iter_t *iter = lista_iter_crear(canal->usuarios);
	if (iter == NULL ) return false;

	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if(!strcmp(usuario_get_nombre(usuario_actual), usuario_get_nombre(user))){
			lista_iter_borrar(iter);
			lista_iter_destruir(iter);
			return true;
		}
		lista_iter_avanzar(iter);
	}

	lista_iter_destruir(iter);
	return false;
}


char *canal_get_nombre(const struct canal *canal){
	return canal->nombre;
}

char *canal_get_topic(const struct canal *canal){
	return canal->topic;
}

lista_t *canal_get_usuarios(const struct canal *canal){
	if(lista_esta_vacia(canal->usuarios)){
		return NULL;
	}
	return canal->usuarios;
}

char *canal_get_admin(const struct canal *canal){
	return canal->admin;
}


bool canal_set_topic(struct canal *canal, const char *nuevo_topic){

	if(canal->topic != NULL){ // Libero el topic viejo (si existe)
		free(canal->topic);
	}

	canal->topic = malloc( (strlen(nuevo_topic) + 1)*sizeof(char));
	if(canal->topic == NULL){
		return false;
	}

	strcpy(canal->topic, nuevo_topic);
	return true;
}



bool canal_set_admin(struct canal *canal, const char *nick_admin){
	
	// No deberia haber admin anterior
	if(canal->admin != NULL){ 
		return false; //no se puede cambiar de admin
	}

	canal->admin = malloc( (strlen(nick_admin) + 1)*sizeof(char));
	if(canal->admin == NULL){
		return false;
	}
	strcpy(canal->admin, nick_admin);
	return true;
}



