/**
  Implementação de uma variável 'static' e estudo
  do seu comportamento ao longo de diferentes funções
*/
#include "stdio.h"

static int counter = 0;

void increment() {
  counter++;
  printf("C: %d \n", counter);
}

int main(void) {
  for (int i = 1; i <= 5; i++) {
    increment();
  }
}
