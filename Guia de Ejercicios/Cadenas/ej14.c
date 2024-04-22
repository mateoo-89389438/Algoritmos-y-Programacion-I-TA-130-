#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool es_palindroma(const char s[]){
  int l = (strlen(s)-1);
  for(size_t i = 0; i <= (l/2); i++){
    if(s[i] != s[l-i]){
      return false;
    }
  }
  return true;
}

int main(){
  char cadena[] = "neuquen";
  if(es_palindroma(cadena)){
    puts("Es palindroma");
  }
  else{
    puts("no es palindroma");
  }
}