#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {
  QubitState* q1 = initializeState(1);

  initializeStateTo(q1, 0);   // stato |0⟩
  printf("Stato di partenza:\n");
  printState(q1);

  // Pauli X
  applyX(q1, 0);
  printf("\nRisultato dopo Pauli X:\n");
  printState(q1);

  // Pauli Y
  initializeStateTo(q1, 0);   // reset a |0⟩
  applyY(q1, 0);
  printf("\nRisultato dopo Pauli Y:\n");
  printState(q1);

  // Pauli Z
  initializeStateTo(q1, 0);   // reset a |0⟩
  applyZ(q1, 0);
  printf("\nRisultato dopo Pauli Z:\n");
  printState(q1);

  return 0;
}

