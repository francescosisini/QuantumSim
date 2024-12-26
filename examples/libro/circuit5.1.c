#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(2); // Due qubit inizializzati a |00>

    // Stato iniziale
    printf("Stato iniziale:\n");
    printState(state);

    // Imposta il primo qubit (controllo) a |1>
    applyX(state, 0);
    printf("Stato dopo X sul primo qubit:\n");
    printState(state);

    // Applica il gate CNOT
    applyCNOT(state, 0, 1);
    printf("Stato dopo CNOT (controllo: qubit 0, target: qubit 1):\n");
    printState(state);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
