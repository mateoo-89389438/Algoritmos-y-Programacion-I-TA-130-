#include <stdbool.h>
#include <stdio.h>



//a.
void completar_con_ceros(int *v, size_t len){
	for(size_t i = 0; i < len; i++){
		v[i] = 0;
	}
}


//c
void suma_elementos(int *v, size_t len, size_t *suma){
	for(size_t j = 0; j < len; j++){
		*suma += v[j];
	}
}

//f.
bool maximo(int *v, size_t len, size_t *max){
	if( len == 0){
		return false;
	}

	*max = v[0];
	for(size_t k = 1; k < len; k++){
		if(v[k] > *max){
			*max = v[k];
		}
	}

	return true;
}

//h.
void cuadrados(int *v, size_t len){
	for(size_t i = 0; i < len; i++){
		v[i] = (v[i])*v[i];
	}
}



int main() {
  int v[] = {1,2,3,4};
  size_t suma = 0;
  suma_elementos(v, 4, &suma);
  printf("suma: %zd\n", suma);

  size_t max;
  if( (maximo(v, 4, &max)) ){
  	printf("maximo: %zd\n", max);
  }

  cuadrados(v, 4);
  for(size_t j = 0; j < 4; j++){
    printf("%d ", v[j]);
  }
  puts("");

  
  completar_con_ceros(v, 4);
  for(size_t j = 0; j < 4; j++){
    printf("%d ", v[j]);
  }
  puts("");



  return 0;
}