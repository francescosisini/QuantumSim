#include <stdio.h>
#include "../src/quantum_sim.h"

void circuit(void){
  
  QubitState* state = initializeState(4);
  printState(state);
  
}
