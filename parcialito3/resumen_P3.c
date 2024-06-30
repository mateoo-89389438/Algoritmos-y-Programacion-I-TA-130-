
//ARGUMENTOS DE LA LINEA DE COMANDOS
int main(int argc, char *argv[]) {

    if (argc != N ) { //N es el numero que quieras recibir de argumentos
        return 1;
    }    

    //Suponiendo un uso: ./programa <archivo> numero
    FILE *fi = fopen(argv[1], "rb"); 

    if (fi == NULL) {
        return 1;
    }

    //convierto el numero a entero
    char numero = atoi(argv[2]);
    if (numero < 0){ //ejemplo de verificacion de dato numerico
        return 1
    }
    
    fclose(fi);
}

