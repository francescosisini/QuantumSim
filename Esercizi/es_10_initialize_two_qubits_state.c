#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {

  QubitState* state2 = initializeState(2);
  initializeStateTo(state2, 0);
  printf("Stato |00>:\n");
  printState(state2);
  
  initializeStateTo(state2, 1);
  printf("\nStato |01>:\n");
  printState(state2);

  initializeStateTo(state2, 2);
  printf("\nStato |10>:\n");
  printState(state2);
  
  initializeStateTo(state2, 3);
  printf("\nStato |11>:\n");
  printState(state2);
  
  return 0;
}

