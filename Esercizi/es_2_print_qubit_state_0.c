#include <stdio.h>
#include "../src/quantum_sim.h"

void circuit(void) {
  QubitState* q1 = initializeState(1);
  initializeStateTo(q1, 0);
  printState(q1);
}
