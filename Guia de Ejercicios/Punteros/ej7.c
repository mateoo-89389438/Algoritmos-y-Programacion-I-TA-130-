
void suma(int a, int b, long int * suma){
    *suma = (long int)a+b;
}

void resta(int a, int b, long int * resta){
    *resta = (long int)a-b;
}

void producto(int multiplicando, int multiplicador, float * producto){
    *producto = (float)multiplicando * multiplicador;
}

void division(int dividendo, int divisor, double * resultado_division){
    *resultado_division = (double)dividendo / divisor;
}

void modulo (int dividendo, int divisor, double * resto){
    *resto = (double)dividendo % divisor;
}