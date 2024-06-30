#include "comunicador.h"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>

struct comunicador {
	char *error;
	int sockfd;
};

comunicador_t *comunicador_crear() {
	comunicador_t *c = malloc(sizeof(comunicador_t));
	if(c == NULL) return NULL;

	c->sockfd = -1;
	c->error = NULL;

	return c;
}

void comunicador_destruir(comunicador_t *c) {
	if(comunicador_esta_conectado(c))
		close(c->sockfd);
	free(c);
}

bool comunicador_conectar(comunicador_t *c, const char *direccion, int puerto) {
	c->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(c->sockfd == -1) {
		c->error = "Falló la creación del socket";
		return false;
	}

	struct hostent *he = gethostbyname(direccion);
	if(he == NULL) {
		c->error = "No se pudo resolver la dirección";
		return false;
	}

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = *(in_addr_t *)he->h_addr_list[0];
	servaddr.sin_port = htons(puerto);

	if(connect(c->sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
		c->error = "Falló la conexión con el servidor";
		return false;
	}

	return true;
}

bool comunicador_esta_conectado(const comunicador_t *c) {
	return c->sockfd != -1;
}

char *comunicador_get_error(const comunicador_t *c) {
	return c->error;
}

int comunicador_get_sockfd(const comunicador_t *c) {
	return c->sockfd;
}

int comunicador_esperar_datos(comunicador_t *c) {
	if(! comunicador_esta_conectado(c)) {
		c->error = "Comunicador no conectado";
		return -1;
	}

	struct pollfd fds[2];
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	fds[1].fd = c->sockfd;
	fds[1].events = POLLIN;

	if(poll(fds, 2, -1) < 0) {
		c->error = "Falla esperando datos";
		close(c->sockfd);
		c->sockfd = -1;
		return -1;
	}

	for (size_t i = 0; i < 2; i++) {
		if (fds[i].revents & POLLIN) {
			return fds[i].fd;
		}
	}
	
	c->error = "La realidad, ni idea ;)";
	return -1;
}


