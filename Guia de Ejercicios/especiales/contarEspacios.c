#include <stdio.h>
#include <ctype.h>

int main(){

	int c;
	size_t espacios = 0;
	while (  (c = getchar()) != EOF){
		if( isspace(c)){
			espacios++;
		}
	}

	printf("%zd\n", espacios);
	return 0;
	//En mi terminal (iMac) cuenta un espacio de más			
}
