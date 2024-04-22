#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct inventario {
    char descripcion[31];
    int numero_de_parte;
    float precio;
    int cantidad_en_almacen;
    int lugar_de_almacenamiento;
};

struct inventario *crear_inventario(const char *desc, int num_parte, float precio, int cantidad, int lugar) {
    struct inventario *inv = (struct inventario *)malloc(sizeof(struct inventario));
    if (inv == NULL) {
        return NULL; // Error: no se pudo asignar memoria
    }
    strncpy(inv->descripcion, desc, sizeof(inv->descripcion) - 1);
    inv->numero_de_parte = num_parte;
    inv->precio = precio;
    inv->cantidad_en_almacen = cantidad;
    inv->lugar_de_almacenamiento = lugar;
    return inv;
}

void liberar_inventario(struct inventario *inv) {
    free(inv);
}

int main() {
    struct inventario *mi_producto = crear_inventario("Producto A", 12345, 19.99, 50, 101);
    if (mi_producto != NULL) {
        printf("Descripción: %s\n", mi_producto->descripcion);
        printf("Número de parte: %d\n", mi_producto->numero_de_parte);
        printf("Precio: %.2f\n", mi_producto->precio);
        printf("Cantidad en almacén: %d\n", mi_producto->cantidad_en_almacen);
        printf("Lugar de almacenamiento: %d\n", mi_producto->lugar_de_almacenamiento);
        liberar_inventario(mi_producto);
    } else {
        printf("Error: No se pudo crear el inventario.\n");
    }
    return 0;
}
