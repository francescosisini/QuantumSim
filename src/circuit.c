#include <stdio.h>
#include "../src/quantum_sim.h"

void circuit(void){
  
  QubitState* state = initializeState(2);
  printf("Inizializzazione:\n");
  printState(state);
  applyHadamard(state,0);
  printf("Hadamard su q0:\n");
  printState(state);
  
  
}
