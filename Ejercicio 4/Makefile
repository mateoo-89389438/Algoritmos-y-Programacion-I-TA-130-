CFLAGS= -Wall -Werror -std=c99 -pedantic
TARGET = cliente

all: $(TARGET)

$(TARGET): cliente.o comunicador.o terminal.o cadenas.o color.o
	gcc cliente.o comunicador.o terminal.o cadenas.o color.o -o $(TARGET) 

cliente.o: cliente.c comunicador.h terminal.h cadenas.h color.h
	gcc $(CFLAGS) -c cliente.c

comunicador.o: comunicador.c comunicador.h
	gcc $(CFLAGS) -c comunicador.c

color.o: color.c color.h
	gcc $(CFLAGS) -c color.c

terminal.o: terminal.c terminal.h 
	gcc $(CFLAGS) -c terminal.c

cadenas.o: cadenas.c cadenas.h
	gcc $(CFLAGS) -c cadenas.c

clean:
	rm -vf *.o $(TARGET)

