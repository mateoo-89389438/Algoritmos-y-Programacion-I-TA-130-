#include <stdio.h>

//programa para leer chars hasta que lo pare el usuario
int main(){
	int c;
	while( (c = getchar()) != EOF){ //EOF == crl+d
		printf("%c\n", c);
	}
	
	puts("chau");
	return 0;

}