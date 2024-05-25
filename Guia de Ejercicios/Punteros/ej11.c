#include <stdbool.h>
#include <stdio.h>


bool veccmp(double * v1, size_t lenv1, const double * v2, size_t lenv2){
	if( v1 == NULL || v1 == NULL || (lenv1 != lenv2)){
		return false;
	}

	for(size_t i = 0; i < lenv2; i++){
		if(v1[i] != v2[i]){
			return false;
		}
	}

	return true;
}

int main(){

	double v[] = {1, 2, 3, 4};
	double w[] = {1 , 2 ,3 , 4};
	size_t lenv = 4;
	size_t lenw = 4;

	if(veccmp(w, lenw, v, lenv)){
		puts("Son iguales");
	}
	else{
		puts("Son distintos");
	}

	return 0;
}