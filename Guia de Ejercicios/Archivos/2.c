#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100

int main(int argc, char *argv[]){

	if(argc != 3){
		fprintf(stderr,"Uso: %s <entrada.txt> <salida.txt>\n", argv[0]);
		return 1;
	}

	FILE *fi = fopen(argv[1], "r");
	if(fi == NULL){
		return 1;
	}

	FILE *fo = fopen(argv[2], "w");
	if(fo == NULL){
		return 1;
	}

	char c;

	while(fread(&c, sizeof(char),1, fi) == 1){
		fwrite(&c, sizeof(char),1, fo);
	}

	fclose(fi);
	fclose(fo);

	return 0;
}