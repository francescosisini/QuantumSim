#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {
  QubitState* q1 = initializeState(1);
  initializeStateTo(q1, 1);
  printState(q1);
  return 0;
}
