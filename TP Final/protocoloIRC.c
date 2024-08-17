#include "protocoloIRC.h"
#include "usuario.h"
#include "canal.h"
#include "server.h"
#include "lista.h"
#include "cadenas.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char comandosIRC[][MAX_STRING] = {"PRIVMSG", "NICK", "JOIN", "PART", "NAMES", "TOPIC", "LIST", "USERS", "QUIT", "PING", "PONG"};


char *comandoUSER(const char *s){

	//verifico el comando
	char campo0[MAX_STRING];
	extraer_campo(campo0, s, 0);
	char user[] = "USER";

	if(!son_iguales(campo0, user) || cantidad_campos(s) != 5){
		return NULL;
	}
	// saco el nombre que me paso el usuario
	char *nombre = malloc(strlen(s)+1);
	if(nombre == NULL) return NULL;
	extraer_campo(nombre, s, 1);
	if(strlen(nombre) == 0){
		free(nombre);
		return NULL;
	}
	return nombre;
}

char *comandoNICK(const char *s){

	//verifico el comando
	char campo0[MAX_STRING];
	extraer_campo(campo0, s, 0);

	if(!son_iguales(campo0, comandosIRC[1]) || cantidad_campos(s) != 2){
		return NULL;
	}

	// saco el nick que me paso el usuario
	char *nick = malloc(strlen(s)+1);
	if(nick == NULL) return NULL;
	extraer_campo(nick, s, 1);
	if(strlen(nick) == 0){
		free(nick);
		return NULL;
	}
	return nick;
}


bool verificarNICK(server_t *server, const char *nick){

	lista_iter_t *iter = lista_iter_crear(server_get_usuarios(server));
	while (!lista_iter_al_final(iter)){
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if (son_iguales(usuario_get_nick(usuario_actual), nick)){
			lista_iter_destruir(iter);
			return false;
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return true;
}


bool comandoNAMES(server_t *server, struct usuario *user, char *nombre_canal){

	// Verifico si el canal existe
	struct canal *canal = server_get_canal(server, nombre_canal);
	if(canal != NULL){
		//el canal existe:

		//saco el admin
		char *nick_admin = canal_get_admin(canal);

		char *succession = malloc(500 * sizeof(char));
		if(succession == NULL) return false;

		sprintf(succession, "%s = ", canal_get_nombre(canal));
		lista_iter_t *iter = lista_iter_crear(canal_get_usuarios(canal));
		while (!lista_iter_al_final(iter)){
			struct usuario *usuario_actual = lista_iter_ver_actual(iter);
			char *nick_actual = usuario_get_nick(usuario_actual);
			char nick_con_prefijo[strlen(nick_actual) + 2]; 

			//Si es admin le pongo el @
			if(!strcmp(nick_actual, nick_admin)){
				sprintf(nick_con_prefijo, "@%s", nick_actual);
				strcat(succession, nick_con_prefijo);
			} 
			else{
				strcat(succession, nick_actual);
			}
			strcat(succession, " ");
			lista_iter_avanzar(iter);
		}
		lista_iter_destruir(iter);
		server_mensaje_codigo(server, user, "353", succession);
		free(succession);
	}
	
	server_mensaje_codigo(server, user, "366", "Terminó la lista");
	return true;
}

bool comandoJOIN(server_t *server, struct usuario *user, const char *s){
	//saco el campo 0 de la cadena recibida
	char nombre_canal[MAX_STRING];
	extraer_campo(nombre_canal, s, 1);
	if(nombre_canal[0] != '#'){
		server_mensaje_codigo(server, user, "476", "Nombre de canal invalido");
		return false;
	}
	usuario_join_canal(user, nombre_canal, server);
	
	//mensaje a todos avisando el ingreso del nuevo usario
	char *aviso = malloc(strlen(usuario_get_tag(user)) + strlen(nombre_canal) + 8);
	if(aviso == NULL) return false;
	
	sprintf(aviso, "%s JOIN %s\n", usuario_get_tag(user), nombre_canal);
	struct canal *canal = server_get_canal(server, nombre_canal);
	if(canal == NULL){
		free(aviso);
		return false;
	} 
	server_mensaje_canal(server, canal , aviso);
	free(aviso);
	comandoNAMES(server, user, nombre_canal);
	return true;
}

bool comandoLIST(server_t *server, struct usuario *user){

	server_mensaje_codigo(server, user, "321", "Arranca la lista");

	lista_iter_t *iter = lista_iter_crear(server_get_canales(server));
	while (!lista_iter_al_final(iter)){
		struct canal *canal_actual = lista_iter_ver_actual(iter);
		if((canal_get_topic(canal_actual)) != NULL){
			char *mensaje = malloc(strlen(canal_get_nombre(canal_actual)) + strlen(canal_get_topic(canal_actual)) + 2);
			if(mensaje == NULL){
				lista_iter_destruir(iter);
				return false;
			}
			sprintf(mensaje, "%s %s", canal_get_nombre(canal_actual), canal_get_topic(canal_actual));
			server_mensaje_codigo(server, user, "322", mensaje);
			free(mensaje);
		}
		else{
			server_mensaje_codigo(server, user, "322", canal_get_nombre(canal_actual));
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	server_mensaje_codigo(server, user, "323", "Terminó la lista");
	return true;
}

bool comandoPART(server_t *server, struct usuario *user, char *nombre_canal){

	// Verifico si el canal existe
	struct canal *canal = server_get_canal(server, nombre_canal);
	if(canal == NULL){
		// El canal no existe
		server_mensaje_codigo(server, user, "403", "El canal no existe");
		return false;
	}

	if(canal_verificar_usuario(canal, user)){

		if(!canal_remover_usuario(canal, user)){
			return false;
		}
		canal_remover_usuario(canal, user);
		// El usuario está en el canal
		char *mensaje = malloc(strlen(usuario_get_tag(user)) + strlen(canal_get_nombre(canal)) + 8);
		if(mensaje == NULL){
			return false;
		}
		sprintf(mensaje, "%s PART %s\n", usuario_get_tag(user), canal_get_nombre(canal));
		server_mensaje_canal(server, canal, mensaje);
		free(mensaje);
		return true;
	}
	else{
		// El usuario no estaba en el canal
		server_mensaje_codigo(server, user, "442", "El usuario no está en el canal");
		return false;
	}

	return false;
}

void comandoPING(server_t *server){	
	lista_iter_t *iter = lista_iter_crear(server_get_usuarios(server));
	while (!lista_iter_al_final(iter)){
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);

		char *mensaje = malloc(strlen(server_get_idservidor(server)) + strlen(usuario_get_nick(usuario_actual)) + strlen(server_get_codigoPING(server)) + 10);
		if(mensaje == NULL){
			lista_iter_destruir(iter);
			return;
		}
		sprintf(mensaje, "%s PING %s %s\n", server_get_idservidor(server), usuario_get_nick(usuario_actual), server_get_codigoPING(server));
		write(usuario_get_fd(usuario_actual), mensaje, strlen(mensaje));
		free(mensaje);
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
}

bool comandoPONG(server_t *server, struct usuario *user, char *s){
	if(cantidad_campos(s) != 2){
		return false;
	}
	//verifico si el pong mandado es correcto
	char campo1[MAX_STRING];
	extraer_campo(campo1, s, 1);
	if(!son_iguales(campo1, server_get_codigoPING(server))){
		return false;
	}

	usuario_set_ultimoPONG(user);
	return true;
}

bool comandoPRIVMSG(server_t *server, struct usuario *user, char *s){

	// veo si el destinatario es usuario o canal
	char campo1[MAX_STRING];
	extraer_campo(campo1, s, 1);

	//ES CANAL
	if(campo1[0] == '#'){ 
		// Verifico si el canal existe
		struct canal *canal = server_get_canal(server, campo1);
		if(canal == NULL){
			server_mensaje_codigo(server, user, "403", "El canal no existe");
			return false;
		}

		lista_iter_t *iter = lista_iter_crear(canal_get_usuarios(canal));
		while (!lista_iter_al_final(iter)) {
			struct usuario *usuario_actual = lista_iter_ver_actual(iter);
			if (!strcmp(usuario_get_nick(usuario_actual), usuario_get_nick(user))) {
				// El usuario está en ese canal

				// Guardo el mensaje que envió el usuario
				char campo2[MAX_STRING];
				extraer_campo(campo2, s, 2);
				char *mensaje = malloc(strlen(usuario_get_tag(user)) + strlen(canal_get_nombre(canal)) + strlen(campo2) + 12);
				if (mensaje == NULL){
					lista_iter_destruir(iter);
					return false;
				}
				sprintf(mensaje, "%s PRIVMSG %s %s\n", usuario_get_tag(user), canal_get_nombre(canal), campo2);

				// Le mando el mensaje a todos MENOS al usuario
				lista_iter_t *iter2 = lista_iter_crear(canal_get_usuarios(canal));
				if(iter2 == NULL){
					free(mensaje);
					lista_iter_destruir(iter);
					return false;
				}
				while (!lista_iter_al_final(iter2)) {
					struct usuario *usuario_actual2 = lista_iter_ver_actual(iter2);
					if (strcmp(usuario_get_nick(usuario_actual2), usuario_get_nick(user)) != 0) {
						write(usuario_get_fd(usuario_actual2), mensaje, strlen(mensaje));
					}
					lista_iter_avanzar(iter2);
				}
				free(mensaje);
				lista_iter_destruir(iter2);
				lista_iter_destruir(iter);
				return true;
			}
			lista_iter_avanzar(iter);
		}
		lista_iter_destruir(iter);


		// El usuario no estaba en el canal
		server_mensaje_codigo(server, user, "404", "El canal existe pero el usuario no está en el canal");
		return false;
	}
	//ES USUARIO
	else{
		// Verifico si el usuario destinatario existe
		struct usuario *usuarioDestino = server_get_usuario_nombre(server, campo1);
		if(usuarioDestino == NULL){
			server_mensaje_codigo(server, user, "401", "El usuario destino no existe");
			return false;
		}

		// Guardo el mensaje que envio el usuario
		char campo2[MAX_STRING];
		extraer_campo(campo2, s, 2);
		char *mensaje = malloc(strlen(usuario_get_tag(user)) + strlen(usuario_get_nombre(usuarioDestino)) + strlen(campo2) + 12);
		sprintf(mensaje, "%s PRIVMSG %s %s\n", usuario_get_tag(user), usuario_get_nombre(usuarioDestino), campo2);
		write(usuario_get_fd(usuarioDestino), mensaje, strlen(mensaje));
		free(mensaje);
	}

	return false;
}


bool comandoQUIT(server_t *server, struct usuario *user, char *motivo){

	char *mensaje = malloc(strlen(usuario_get_tag(user)) + strlen(motivo) + 30);
	if (mensaje == NULL) {
		return false;
	}
	sprintf(mensaje, "%s QUIT salió del chat %s\n", usuario_get_tag(user), motivo);
	// Itero sobre todos los canales del servidor
	lista_iter_t *iter = lista_iter_crear(server_get_canales(server));
	if (iter == NULL) {
		free(mensaje);
		return false;
	}
	while (!lista_iter_al_final(iter)) {
		struct canal *canal_actual = lista_iter_ver_actual(iter);
		if(canal_verificar_usuario(canal_actual, user)){
			canal_remover_usuario(canal_actual, user);
			server_mensaje_canal(server, canal_actual, mensaje);
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	free(mensaje);
	return server_eliminar_usuario(server, usuario_get_fd(user));
}

bool comandoTOPIC(server_t *server, struct usuario *user, char *s){

	// Verifico si el canal existe
	char campo1[MAX_STRING];
	extraer_campo(campo1, s, 1);
	
	struct canal *canal = server_get_canal(server, campo1);
	if(canal == NULL){
		server_mensaje_codigo(server, user, "403", "El canal no existe");
		return false;
	}

	lista_iter_t *iter = lista_iter_crear(canal_get_usuarios(canal));
	while (!lista_iter_al_final(iter)) {
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if (!strcmp(usuario_get_nick(usuario_actual), usuario_get_nick(user))) {
			// El usuario está en ese canal
			if(cantidad_campos(s) == 2){
				//El usuario NO mandó topico (lo esta pidiendo)
				char *topic = canal_get_topic(canal);

				if(topic == NULL){
					char *mensaje = malloc(strlen(canal_get_nombre(canal)) + 20);
					sprintf(mensaje, "%s :No hay tópico", canal_get_nombre(canal));
					server_mensaje_codigo(server, user, "331", mensaje);
					free(mensaje);
				}
				else{
					char *mensaje = malloc(strlen(canal_get_nombre(canal)) + strlen(canal_get_topic(canal)) + 20);
					sprintf(mensaje, "%s %s", canal_get_nombre(canal), canal_get_topic(canal));
					server_mensaje_codigo(server, user, "332", mensaje);
					free(mensaje);
				}
				lista_iter_destruir(iter);
				return true;
			}
			else if(cantidad_campos(s) == 3){
				// El usuario SÍ mandó topico (lo esta seteando)
				char campo2[MAX_STRING];
				extraer_campo(campo2, s, 2);
				canal_set_topic(canal, campo2);
				// mensaje a todos los usuarios del canal con el nuevo topico
				char *mensaje = malloc(strlen(usuario_get_tag(user)) + strlen(canal_get_nombre(canal)) + strlen(canal_get_topic(canal)) + 10);
				sprintf(mensaje, "%s TOPIC %s %s\n", usuario_get_tag(user), canal_get_nombre(canal), canal_get_topic(canal));
				server_mensaje_canal(server, canal , mensaje);
				free(mensaje);
				lista_iter_destruir(iter);
				return true;
			}
			lista_iter_destruir(iter);
			return false;

		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);

	// El usuario no estaba en el canal
	server_mensaje_codigo(server, user, "404", "El canal existe pero el usuario no está en el canal");
	return false;

}

bool comandoUSERS(server_t *server, struct usuario *user){
	server_mensaje_codigo(server, user, "392", "Arranca la lista");

	lista_iter_t *iter = lista_iter_crear(server_get_usuarios(server));
	size_t i = 0;
	while (!lista_iter_al_final(iter)){
		struct usuario *usuario_actual = lista_iter_ver_actual(iter);
		if(strcmp(usuario_get_nick(user), usuario_get_nick(usuario_actual))){
			char *mensaje = malloc(strlen(usuario_get_nick(usuario_actual)) + strlen(usuario_get_nombre(usuario_actual)) + 10 + 3);
			if(mensaje == NULL){
				lista_iter_destruir(iter);
				return false;
			}
			sprintf(mensaje, "%s %s %d", usuario_get_nick(usuario_actual), usuario_get_nombre(usuario_actual), usuario_get_IP(usuario_actual));
			server_mensaje_codigo(server, user, "393", mensaje);
			free(mensaje);
			i++;
		}
		lista_iter_avanzar(iter);
	}

	if(i == 0){
		// No hay mas usuarios conectados
		server_mensaje_codigo(server, user, "395", "No hay nadie más conectado");
	}
	lista_iter_destruir(iter);
	server_mensaje_codigo(server, user, "394", "Termina la lista");
	return true;
}





