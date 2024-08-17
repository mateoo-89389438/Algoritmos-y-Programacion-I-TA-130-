CFLAGS= -Wall -Werror -std=c99 -pedantic
TARGET = servidor

all: $(TARGET)

$(TARGET): servidor.o server.o usuario.o canal.o protocoloIRC.o cadenas.o lista.o 
	gcc servidor.o server.o usuario.o canal.o protocoloIRC.o cadenas.o lista.o  -o $(TARGET)

servidor.o: servidor.c server.h usuario.h canal.h protocoloIRC.h cadenas.h lista.h 
	gcc $(CFLAGS) -c servidor.c

server.o: server.c server.h usuario.h canal.h lista.h protocoloIRC.h cadenas.h 
	gcc $(CFLAGS) -c server.c

usuario.o: usuario.c usuario.h
	gcc $(CFLAGS) -c usuario.c

canal.o: canal.c canal.h usuario.h lista.h
	gcc $(CFLAGS) -c canal.c

protocoloIRC.o: protocoloIRC.c protocoloIRC.h usuario.h canal.h server.h
	gcc $(CFLAGS) -c protocoloIRC.c

cadenas.o: cadenas.c cadenas.h
	gcc $(CFLAGS) -c cadenas.c

lista.o: lista.c lista.h
	gcc $(CFLAGS) -c lista.c

clean:
	rm -vf *.o $(TARGET)
