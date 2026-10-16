#include <stdio.h>
#include "../src/quantum_sim.h"

void circuit(void) {

  QubitState* state2 = initializeState(2);
  initializeStateTo(state2, 2);   // stato |10>
  printf("Stato di partenza (stato |10>):\n");
  printState(state2);

  applyHadamard(state2, 0);
  printf("\nDopo il primo Hadamard:\n");
  printState(state2);
  
  applyCZ(state2, 1, 0);
  printf("\nDopo il gate CZ:\n");
  printState(state2);

  applyHadamard(state2, 0);
  printf("\nDopo il secondo Hadamard:\n");
  printState(state2);

  freeState(state2);
}

