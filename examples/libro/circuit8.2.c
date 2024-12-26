#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(2); // Due qubit

    // Stato iniziale
    initializeStateTo(state, 0);
    printf("Stato iniziale:\n");
    printState(state);

    // Applica gate Hadamard al primo qubit
    applyHadamard(state, 0);
    printf("Stato dopo Hadamard:\n");
    printState(state);

    // Applica gate CNOT
    applyCNOT(state, 0, 1);
    printf("Stato dopo CNOT:\n");
    printState(state);

    // Misura
    MeasurementResult result1 = measure(state, 0);
    MeasurementResult result2 = measure(state, 1);
    printf("Risultati delle misure: %d, %d\n", result1.result, result2.result);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
