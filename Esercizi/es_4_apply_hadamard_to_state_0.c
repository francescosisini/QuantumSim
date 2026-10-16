#include <stdio.h>
#include "../src/quantum_sim.h"
int circuit(void) {
  QubitState* q1 = initializeState(1);
  MeasurementResult result;
  initializeStateTo(q1, 0);
  applyHadamard(q1, 0);
  printState(q1);
 
  printf("Risultato della misura:\n");
  result = measure(q1, 0);
  printf("probabilita stato |0>: %lf\n", result.prob0);
  printf("probabilita stato |1>: %lf\n", result.prob1);
  printf("il qubit è stato misurato nello stato: |%d>\n", result.result);
  printf("\n");
  
  return 0;
}

