#ifndef SERVER_H
#define SERVER_H

#include "lista.h"
#include "canal.h"

#include <stdbool.h>
#include <time.h>

struct usuario;
struct canal;

typedef struct server server_t;

//// MANEJO DEL SERVER 

// Crea un server:
server_t *server_crear();

// Lo destruye:
void server_destruir(server_t *server);

// Conecta el server generando el sockfd y se pone a escuchar en un puerto
bool server_conectar(server_t *server, const int puerto);


////GETTERS

// Devuelve el nombre del servidor:
char *server_get_idservidor(const server_t *server); 

// Devuelve el descriptor de archivo del socket con el server:
int server_get_sockfd(const server_t *server);

// Devuelve el mensaje de error del comunicador (si falló). Es una cadena estática:
char *server_get_error(const server_t *server);

// Devuelve la lista de canales del servidor
lista_t *server_get_usuarios(const server_t *server);

// Devuelve la lista de canales del servidor
lista_t *server_get_canales(const server_t *server);

// Devuelve el codigo PING del servidor
char *server_get_codigoPING(const server_t *server);



//// MANEJO DE USUARIOS 

// Acepta al usuario que se quiere conectar
struct usuario *server_aceptar_usuario(server_t *server, const int sockfd);

// Rechaza al usuario que intentó conectarse
// Post: cierra el canal con el usuario y libera el usuario
void server_rechazar_usuario(server_t *server, struct usuario *user);

// Pre: el usuario ingresó su nick y su nombre
// Completa todos los datos del usuario
// Agrega el usuario (a la lista de usuarios) del servidor
bool server_agregar_usuario(server_t *server, struct usuario *user, const char *nick, const char *nombre);

// Pre: el usuario ya habia sido aceptado y agregado correctamente con todos sus datos
// Elimina un usario (de la lista de usuarios) del servidor y cierra el fd de comunicacion
// Post: el usuario ya no esta en la lista de usuarios del canal 
bool server_eliminar_usuario(server_t *server, const int fd);

// Busca entre los usuarios del server por el nombre y si existe lo devuelve, si no NULL
struct usuario *server_get_usuario_nombre(const server_t *server, const char *nombre_usuario);

// Busca entre los usuarios del server por el fd y si existe lo devuelve, si no NULL
struct usuario *server_get_usuario_fd(const server_t *server, const int fd);



///// MANEJO DE CANALES 

// Agrega un canal al servidor
bool server_agregar_canal(server_t *server, struct canal *canal);

// Busca entre los canales del server y si existe lo devuelve, si no NULL
struct canal *server_get_canal(const server_t *server, const char *nombre_canal);

// Elimina un canal del servidor
bool server_eliminar_canal(server_t *server, const char *nombre_canal);



///// FUNCIONES EXTRAS 

// Espera por datos tanto en el socket del servidor como por cada uno de los fds abiertos
// devuelve el numero de fd donde se registraron datos
// devuelve -1 si se rompio
int server_esperar_datos(server_t *server);

// Le envia un mensaje al usuario con el formato: idservidor xxx nick mensaje
void server_mensaje_codigo(const server_t *server, const struct usuario *user, const char *codigo, const char *mensaje);

// Le envia un mensaje a todos los usuarios en ese canal:
bool server_mensaje_canal(const server_t *server, const struct canal *canal , const char *mensaje);

// Le envia un mensaje a todos los usuarios en ese servidor:
void server_mensaje_general(const server_t *server, const char *mensaje);

// Verifica el tiempo transcurrido entre la hora actual y el ultimo pong recibido por cada usuario del servidor
// Se elimna del servidor a cada usuario que no contestó el PING en un tiempo razonable 
void server_verificar_PONGS(server_t *server, const time_t tiempo_actual);


#endif

