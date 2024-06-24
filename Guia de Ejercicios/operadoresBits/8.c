#include <stdint.h>
#include <stdio.h>

//RGB = 0xRRGGBB
#define MASK_COLOR 0XFF
#define SHIFT_RED 16
#define SHIFT_GREEN 8

//a.
uint8_t get_rojo(uint32_t r){
    return (r >> SHIFT_RED) & MASK_COLOR;
}

//b.
uint8_t get_verde(uint32_t r){
    return (r >> SHIFT_GREEN) & MASK_COLOR;
}

//c. 
uint8_t get_azul(uint32_t r){
    return (r & MASK_COLOR);
}

//d.
void get_componentesRGB(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b ){
	*r = get_rojo(color);
	*g = get_verde(color);
	*b = get_azul(color);
}


int main(){

	uint32_t miColor = 0xFFCCAA; 
	uint8_t red, green, blue;

	get_componentesRGB(miColor, &red, &green, &blue);

	puts("#SIN PUNTEROS#");
	printf("R: %X\n", get_rojo(miColor));
	printf("G: %X\n", get_verde(miColor));
  	printf("B: %X\n", get_azul(miColor));

  	puts("");
  
  	puts("#CON PUNTEROS#");
  	printf("RED: %X, GREEN: %X, BLUE: %X", red, green, blue);
	return 0;
}





