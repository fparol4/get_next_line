/**
  Implementação de uma variável 'static' e estudo
  do seu comportamento ao longo de diferentes funções
*/
#include "stdio.h"

typedef struct s_memory {
  int counter;
} s_memory;

static s_memory memory;

void increment_with_pointer(s_memory *memory) {
  memory->counter++;
  printf("inner_memory.counter: %d \n", memory->counter);
}
void increment_static() {
  memory.counter++;
  printf("static_memory.counter: %d \n", memory.counter);
}

int main(void) {
  s_memory inner_memory;
  inner_memory.counter = 0;
  for (int i = 1; i <= 5; i++) {
    increment_with_pointer(&inner_memory);
    increment_static();
  }
}
