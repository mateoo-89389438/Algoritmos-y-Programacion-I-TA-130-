//definir una constante
#define N 3
#define MAX 100

//definir un arreglos de chars (texto en un vector)
char texto[] = "texto de ejemplo";

//definir una matriz
float matriz[][3] = { //*siempre definir el numero de columnas, las filas no es necesario.
    {1, 2, 3},
    {4, 6, 9},
};

//definir un arreglo de arreglos de caracteres
char cadena[3][MAX] = {
    "Hola",
    "que",
    "tal"
};

//funcion que recibe una matriz como argumento
void funcion(size_t n, size_t m, int matriz[n][m]);
//** siempre primero los valores n,m antes de la matriz

//leer caracteres ingresados por el usuario
int c; //**Tiene que ser int porque EOF no es char
while ( (c = getchar()) != EOF){…} 

//leer una cadena ingresada por el usuario
char buffer[MAX]; //hay que crear un arreglo auxiliar para guardar el texto
fgets(buffer, MAX, stdin); //lo guarda como un texto

//convertir el texto a numerico
int m = atoi(buffer); //el numero que ingresaste como texto se guardo numericamente en m

//Tamaños dentro de un arreglo
int valores[] = {10, 20, 30, 40, 50};

sizeof(int); == 4; 

sizeof(valores); == 5*sizeof(int) == 5*4 == 20;








