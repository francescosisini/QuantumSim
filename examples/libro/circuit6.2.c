#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(2); // Due qubit inizializzati a |00>

    // Stato iniziale
    printf("Stato iniziale:\n");
    printState(state);

    // Applica il gate Hadamard sul primo qubit
    applyHadamard(state, 0);
    printf("Stato dopo Hadamard sul primo qubit:\n");
    printState(state);

    // Applica il gate CNOT
    applyCNOT(state, 0, 1);
    printf("Stato dopo CNOT (entanglement):\n");
    printState(state);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
