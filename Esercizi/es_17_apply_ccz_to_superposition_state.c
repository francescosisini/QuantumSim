#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {

  QubitState* state3 = initializeState(3);
  
  initializeStateTo(state3, 0);
  printf("Stato di partenza (stato |000>):\n");
  printState(state3);
  applyHadamard(state3, 0);
  applyHadamard(state3, 1);
  applyHadamard(state3, 2);
  printf("Dopo Hadamard:\n");
  printState(state3);
  applyCCZ(state3, 1, 2, 0);
  printf("\nRisultato dopo gate CCZ:\n");
  printState(state3);
  
  return 0;
}

