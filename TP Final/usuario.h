#ifndef USUARIO_H
#define USUARIO_H

#include "lista.h"
#include "server.h"

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

struct usuario;

// Crea un usuario:
struct usuario *usuario_crear(const uint32_t IP, const int fd);

// Pre: el usuario fue creado
// Completa el nick y el nombre y crea la lista de canales de un usuario 
// Agrega la hora de ingreso al servidor como ultimo PONG
bool usuario_completar(struct usuario *user, const char *nick, const char *nombre);

// Pre: el usuario fue creado y completado
// Destruye un usuario:
void usuario_destruir(struct usuario *user);


//GETTERS
// Pre: el usuario fue completado

// Devuelve la direccion de IP del usuario
uint32_t usuario_get_IP(const struct usuario *user);

// Devuelve el nombre del usuario:
char *usuario_get_nombre(const struct usuario *user);

// Devuelve el nick del usuario: 
char *usuario_get_nick(const struct usuario *user);

// Devuelve el tag del usuario:
char *usuario_get_tag(const struct usuario *user);

// Devuelve el fd del usuario: 
int usuario_get_fd(const struct usuario *user);

// Devuelve el ultimo PONG del usuario: 
time_t usuario_get_ultimoPONG(const struct usuario *user);


//SETTERS

// Pre: el nick no esta ocupado
// Cambia el nick del usuario:
// Post: cambio el tag del usuario
// Post: Se envio un mensaje avisando el cambio a todos los usuarios que estén en canales compartidos con el usuario
bool usuario_cambiar_nick(const server_t *server, struct usuario *user, const char *nuevo_nick);

// Pre: el nombre del canal es válido (empieza con #)
// Verifica si el canal existe. Si no existe lo crea.
// Une al usuario al canal:
// Post: la lista de usuarios del canal esta actualizada con el nuevo usuario
// *Post: la lista de canales del servidor esta actualizada con el nuevo canal
bool usuario_join_canal(struct usuario *user, const char *nombre_canal, server_t *server);

// Actualiza el tiempo del ultimo pong del usuario
void usuario_set_ultimoPONG(struct usuario *user);

#endif

