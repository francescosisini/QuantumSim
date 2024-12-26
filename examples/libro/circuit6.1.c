#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(1); // Inizializza un qubit

    // Stato iniziale |0>
    printf("Stato iniziale:\n");
    printState(state);

    // Applica il gate Hadamard
    applyHadamard(state, 0);
    printf("Stato dopo Hadamard:\n");
    printState(state);

    // Misura
    MeasurementResult result = measure(state, 0);
    printf("Risultato della misurazione: %d\n", result.result);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}

