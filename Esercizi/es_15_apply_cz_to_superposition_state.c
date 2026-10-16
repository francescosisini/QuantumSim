#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {

  QubitState* state2 = initializeState(2);
  
  initializeStateTo(state2, 0);
  printf("Stato di partenza (stato |00>):\n");
  printState(state2);
  applyHadamard(state2, 0);
  applyHadamard(state2, 1);
  printf("Dopo Hadamard:\n");
  printState(state2);
  applyCZ(state2, 1, 0);
  printf("\nRisultato dopo gate CZ:\n");
  printState(state2);
  
  return 0;
}

