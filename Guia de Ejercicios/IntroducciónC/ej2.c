#include <stdio.h>

float Fahrenheit_to_C(float f){
    return (f - 32)*5.0/9.0;
}

int main(){
    printf("C = %.3f", Fahrenheit_to_C(-12.3456));
    return 0;
}
