//EJ1.

//a) 
struct inventario{
    char descripcion [30];
    int numeroParte;
    float precio;
    int cantidad;
    int lugar;
};

typedef struct inventario inventario_t;

//b) 
struct direccion{
    char pais [40];
    char provincia[30];
    char ciudad[20];
    char direccion[30];
    char codigoPostal[10];
};

typedef struct direccion direccion_t;

