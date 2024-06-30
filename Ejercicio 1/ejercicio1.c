#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

#define INICIO -10
#define FIN 10
#define PASO 0.001

#define N_MAX 10

double factorial(unsigned int n){
	return = sqrt(2*PI*n)*pow(n/(exp(1)), n);	
}


double seno(double x, unsigned int n_max){
	double s = 0;
	for(int n=0; n<=n_max; n++){
		s += (pow(-1,n)*pow(x,2*n+1))/factorial(2*n+1);
	}
	return s;
}



int main(){
	printf("x, 	sin x\n");
	for (double i = INICIO; i <= FIN; i += PASO){
		printf("%f,		%f \n", i, seno(i,N_MAX));
	}
	
	return 0;
}




