#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {

  QubitState* state3 = initializeState(3);
  
  initializeStateTo(state3, 2);
  printf("Stato di partenza (stato |010>):\n");
  printState(state3);
  applyToffoli(state3, 1, 2, 0);
  printf("\nRisultato dopo gate Toffoli:\n");
  printState(state3);
  
    printf("\n---------------------------\n\n");
  
  initializeStateTo(state3, 7);
  printf("Stato di partenza (stato |111>):\n");
  printState(state3);
  applyToffoli(state3, 1, 2, 0);
  printf("\nRisultato dopo gate Toffoli:\n");
  printState(state3);
  
  return 0;
}

