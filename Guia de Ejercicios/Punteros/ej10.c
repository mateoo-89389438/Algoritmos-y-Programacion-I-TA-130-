#include <stdbool.h>
#include <stdio.h>


bool veccpy(double * dest, size_t ldest, const double * orig, size_t lorig){
	if( orig == NULL || (ldest < lorig)){
		return false;
	}

	size_t i;
	for(i = 0; i < lorig; i++){
		dest[i] = orig[i];
	}
	dest[i] = '\0';

	if(dest == NULL){
		return false;
	}

	return true;

}

int main(){

	double v[] = {1, 2, 3, 4};
	double w[] = {0 , 0 ,0 , 0};
	size_t lenv = 4;
	size_t lenw = 4;

	if(veccpy(w, lenw, v, lenv)){
		for(size_t j = 0; j < lenw; j++){
			printf("%f ", w[j]);
		}
	}

	return 0;
}