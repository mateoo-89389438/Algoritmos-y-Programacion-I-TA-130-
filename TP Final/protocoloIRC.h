#ifndef PROTOCOLOIRC_H
#define PROTOCOLOIRC_H

#include "usuario.h"
#include "server.h"

#include <stdbool.h>
#include <time.h>

#define MAX_STRING 100

typedef enum {
	PRIVMSG, 	// PRIVMSG <nombre_destinatario> :<mensaje>  (envia un mensaje)
	NICK,		// NICK <nuevo_nick> 	(cambia el nick)
	JOIN,		// JOIN <canal> 	(se une a un canal)
	PART,		// PART <canal> 	(abandona un canal)
	NAMES,	// NAMES <canal> (lista todos los usuarios en un canal)
	TOPIC, 	// TOPIC <canal> 	(pide el topico)  // TOPIC <canal> <topico>  (cambia el topico)
	LIST,		// LIST 	(lista todos los canales del servidor)
	USERS,	// USERS 	(lista todos los usuarios del servidor)
	QUIT,		// QUIT 	(desconecta al usuario del servidor)
	PING,		// PING <codigo>
	PONG,		// PONG <codigo>
} comandosIRC_t;

extern char comandosIRC[][MAX_STRING];


// Si el comando es correcto devuelve el nombre, si no NULL
char *comandoUSER(const char *s);

// Devuelve el nick solicitado por el usuario
char *comandoNICK(const char *s);

// True si el nick esta libre
// False si el nick esta ocupado
bool verificarNICK(server_t *server, const char *nick);

// Si el nombre del canal es valido se une el usuario al canal y se actualiza todo.
bool comandoJOIN(server_t *server, struct usuario *user, const char *s);

// Le envia al usuario una lista de todos los canales del servidor 
bool comandoLIST(server_t *server, struct usuario *user);

// Pre: el canal existe
// Le envia al usuario una lista de todos los usuarios de un canal
bool comandoNAMES(server_t *server, struct usuario *user, char *nombre_canal);

// Saca a un usuario de un canal.
// Post: si el usuario era administrador pierde los permisos y nadie lo reemplaza
bool comandoPART(server_t *server, struct usuario *user, char *nombre_canal);

// Se le envia un mensaje 'idservidor PONG nick codigo' a cada uno de los usuarios del servidor
void comandoPING(server_t *server);

// Verifica si se respondio el comando PONG en tiempo y forma
bool comandoPONG(server_t *server, struct usuario *user, char *s);

// Pre: el destinatario es un nombre, no un nick
// Envia un mensaje a un usuario o un canal
bool comandoPRIVMSG(server_t *server, struct usuario *user, char *s);

//Desconecta al usuario del servidor.
bool comandoQUIT(server_t *server, struct usuario *user, char *motivo);

// Contesta o setea el topico segun corresponda
bool comandoTOPIC(server_t *server, struct usuario *user, char *s);

// Le envia al usuario una lista de todos los usuarios del servidor.
bool comandoUSERS(server_t *server, struct usuario *user);

#endif

