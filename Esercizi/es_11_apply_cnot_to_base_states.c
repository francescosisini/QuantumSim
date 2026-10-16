#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {

  QubitState* state2 = initializeState(2);
  
  initializeStateTo(state2, 0);
  printf("Stato di partenza (stato |00>):\n");
  printState(state2);
  applyCNOT(state2, 1, 0);
  printf("\nRisultato dopo gate CNOT:\n");
  printState(state2);
  printf("\n---------------------------\n\n");
  
  initializeStateTo(state2, 1);
  printf("Stato di partenza (stato |01>):\n");
  printState(state2);
  applyCNOT(state2, 1, 0);
  printf("\nRisultato dopo gate CNOT:\n");
  printState(state2);
  printf("\n---------------------------\n\n");

  initializeStateTo(state2, 2);
  printf("Stato di partenza (stato |10>):\n");
  printState(state2);
  applyCNOT(state2, 1, 0);
  printf("\nRisultato dopo gate CNOT:\n");
  printState(state2);
  printf("\n---------------------------\n\n");
  
  initializeStateTo(state2, 3);
  printf("Stato di partenza (stato |11>):\n");
  printState(state2);
  applyCNOT(state2, 1, 0);
  printf("\nRisultato dopo gate CNOT:\n");
  printState(state2);
  
  return 0;
}

