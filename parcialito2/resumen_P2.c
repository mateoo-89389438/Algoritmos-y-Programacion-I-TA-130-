//ENUMERATIVOS

//decalarar un enumerativo sin typedef
enum dia{
    LUN, 
    MAR, 
    MIE, 
};

//redefinir el enumerativo
typedef enum dia dia_t

//decalarar un enumerativo con typedef
typedef enum{
    LUN, 
    MAR, 
    MIE, 
}dia_t;


//ESTRUCTURAS


//definir una estructura directamente con typedef
typedef struct{
    char nombre[MAX];
    char * apellido;
    float altura;
}nombreEstructura_t;


//definir un particular de esa estructura
nombreEstructura_t persona1 = {
    .nombre = "Gandalf",
    .edad = 125,
    .altura = 1.75,
};


//ejempo funcion que trabaja con una estructura
void mostrarPersona(const alumno_t * p){
    printf("Nombre: %s\nEdad: %d\n", p->nombre, p->edad);
}

//Pedir memoria para una estructura 
persona_t * p = malloc(sizeof(persona_t))


//Operador flechita
(*p).edad = p->edad



//TABLAS DE BUSQUEDA
//primero hay que tener un enumerativo
typedef enum{
    ARGENTINA 
    BRASIL
    URUGUAY
} capitan_t;

//defino mi tabla de busqueda
char * capitanSelecciones[] = {
    [ARGENTINA] = "Messi";
    [BRASIL] = "Neymar";
    [URUGUAY] = "Suarez";
}

//Funcion para usar la tabla de busqueda
void imprimirCapitan(capital_t c){
    printf("El capitan de tu pais es: %s\n", capitanSelecciones[c]);
}


//MANEJO DE BITS

//declarar mascara de bits
#define MASK_NAME 0xFFCCAA //**siempre en hexa

//declarar corrimiento de bits
#define SHIFT_NAME 16 //**siempre en decimal











