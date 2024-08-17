#ifndef CANAL_H
#define CANAL_H

#include "lista.h"

#include <stdbool.h>


struct usuario;
struct canal;

// Crea un canal:
struct canal *canal_crear(const char *nombre);

// Pre: el canal fue creado
// Destruye un canal:
void canal_destruir(struct canal *canal);

// Pre: el usuario existe
// Une a un usuario al canal:
// Post: la lista de usuarios del canal esta actualizada con el nuevo usuario
bool canal_agregar_usuario(struct canal *canal, struct usuario *nuevo_user);

// Pre: el usuario existe
// Devuelve true si el usuario está en el canal, false si no
bool canal_verificar_usuario(struct canal *canal, struct usuario *user);

// Pre: el usuario existe
// Elimina un usuario de un canal:
// Post: la lista de usuarios del canal esta actualizada sin el usuario
bool canal_remover_usuario(struct canal *canal, struct usuario *user);

//GETTERS

// Devuelve el nombre de un canal:
char *canal_get_nombre(const struct canal *canal);

// Devuelve el topico de ese canal. NULL si no tiene topico.
char *canal_get_topic(const struct canal *canal);

// Devuelve la lista de usuarios que pertenecen a un canal:
lista_t *canal_get_usuarios(const struct canal *canal);

// Devuelve el nick del admin de un canal si es que tiene admin
char *canal_get_admin(const struct canal *canal);


//SETTERS

// Cambia el topico de ese canal:
bool canal_set_topic(struct canal *canal, const char *nuevo_topic);

// Pre: no habia admin (porque el admin no se puede cambiar)
// Setea el administrador de un canal
bool canal_set_admin(struct canal *canal, const char *nick_admin);

#endif


