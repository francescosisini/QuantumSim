#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(1);
    applyHadamard(state, 0);
    MeasurementResult result = measure(state, 0);
    printf("Risultato della misura: %d\n", result.result);
    freeState(state);
    return 0;
}
