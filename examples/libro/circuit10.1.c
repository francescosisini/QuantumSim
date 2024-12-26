#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    // Inizializza un sistema con 2 qubit
    QubitState* state = initializeState(2);

    // Applica Hadamard al qubit 0
    applyHadamard(state, 0);

    // Applica CNOT con controllo su qubit 0 e target su qubit 1
    applyCNOT(state, 0, 1);

    // Stampa lo stato quantistico
    printState(state);

    // Misura il qubit 0
    MeasurementResult result0 = measure(state, 0);

    // Misura il qubit 1
    MeasurementResult result1 = measure(state, 1);

    printf("Risultati delle misure: qubit 0 = %d, qubit 1 = %d\n", result0.result, result1.result);

    // Libera la memoria
    freeState(state);

    return 0;
}
