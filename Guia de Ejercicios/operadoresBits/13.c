#include <stdint.h>
#include <stdio.h>

//a.
int lzcnt(uint32_t n){
	//creo la mascara adentro del for
	for(int i =0; i < 8 * sizeof(n); i++){
		if(n & (1 << (31 - i))){
			return i;
		}
	}
	return 32;
}


//b.
int popcnt(uint32_t n){
	int cont = 0;
	for(size_t i  = 0; i < 8 * sizeof(n); i++){
		if(n & (1 << i)){
			cont ++;
		}
	}
	return cont;
}

//c


//d. 
uint32_t blsi(uint32_t n){
	for(size_t i = 0; i < 32; i++){
		if(n & (1 << i)){
			uint32_t mask = (1 << i);
			return mask;
		}
	}

	return 0;
}

//e. 
uint32_t blsmsk(uint32_t n){

	for(size_t i = 0; i < 32; i++){
		if(n & (1 << i)){
			uint32_t mask = ((1 << (i + 1)) - 1);
			return mask;
		}
	}

	return 0;
}

//f.
uint32_t blsr(uint32_t n){
	for(size_t i = 0; i < 32; i++){
		if(n & (1 << i)){
			uint32_t mask = (n & (~(1 << i)));
			return mask;
		}
	}

	return 0;
}

//g.
int tzcnt(uint32_t n){
	int cont = 0;
	for(size_t i = 0; i < 32; i ++){
		if((n & (1 << i))){
			return cont;
		}
		cont++;
	}
	return cont;
}

//h.
uint32_t pext(uint32_t a, uint32_t m) {
	uint32_t resultado = 0;
	uint32_t bit_pos = 0;

	for (uint32_t i = 0; i < 32; i++) {
		if (m & (1 << i)) {
			if (a & (1 << i)) {
				resultado |= (1 << bit_pos);
			}
			bit_pos++;
		}
	}

	return resultado;
}

int main(){

	uint32_t registro = 0xCA; //1100 1010
	printf("la cantidad de ceros es: %d\n", lzcnt(registro));
	printf("la cantidad de unos es: %d\n", popcnt(registro));
	printf("extract lowest set isolated bit: %b\n", blsi(registro));
	printf("get mask up to lowest set bit: %b\n", blsmsk(registro));
	printf("reset lowest set bit: %b\n", blsr(registro));
	printf("trailing zeros count: %d\n", tzcnt(registro));

	uint32_t a = 0b10111001; // 185 en decimal
    	uint32_t m = 0b10011100; // 156 en decimal

    	printf("parallel bits extract: %b\n", pext(a, m)); 


    	return 0;
    }




