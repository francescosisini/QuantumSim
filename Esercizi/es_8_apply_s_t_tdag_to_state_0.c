#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {
  QubitState* q1 = initializeState(1);

  initializeStateTo(q1, 0);   // stato |0⟩
  printf("Stato di partenza:\n");
  printState(q1);

  // S
  applyS(q1, 0);
  printf("\nRisultato dopo gate S:\n");
  printState(q1);

  // T
  initializeStateTo(q1, 0);   // reset a |0⟩
  applyT(q1, 0);
  printf("\nRisultato dopo gate T:\n");
  printState(q1);

  // T dag
  initializeStateTo(q1, 0);   // reset a |0⟩
  applyTdag(q1, 0);
  printf("\nRisultato dopo gate Tdag:\n");
  printState(q1);

  return 0;
}

