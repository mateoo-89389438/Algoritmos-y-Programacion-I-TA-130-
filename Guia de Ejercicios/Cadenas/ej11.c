#include <stdio.h>
#include <string.h>

size_t longitud(const char s[]){
  size_t i;
  for (i = 0; s[i] != '\0'; i++){
  }
  return i;
}

int comparar(const char s1[], const char s2[]){
  size_t i;
  for(i=0;s1[i] != '\0' && s1[i] == s2[i]; i++);
  return s1[i] - s2[1]; 
}




int main (){
  char s1[] = "aaaa";
  char s2[] = "a";
  
  printf("%zu\n", sizeof(s2));

  return 0;
}