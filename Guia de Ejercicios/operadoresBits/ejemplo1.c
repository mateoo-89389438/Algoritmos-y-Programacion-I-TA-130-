#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MASK_ON 0x40

//el bit 6 define el estado(ON - OFF)
bool get_on(uint8_t reg){
  return reg & MASK_ON;
}

int main() {
  
  if(get_on(0x8A)){
    puts("ON");
  }
  else{
    puts("OFF");
  }
  return 0;
}