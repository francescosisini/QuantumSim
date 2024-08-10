#include "quantum_sim.h"
#include <stdio.h>

void circuit() {
    int numQubits = 2;
    QubitState *state = initializeState(numQubits);

    // Stato iniziale: |00>
    printf("Stato iniziale:\n");
    for (int i = 0; i < (1 << numQubits); i++) {
        printf("Stato %d: %f + %fi\n", i, creal(state->amplitudes[i]), cimag(state->amplitudes[i]));
    }

    // Applicare X al qubit di controllo per portarlo nello stato |10>
    applyX(state, 0);

    // Stato dopo X
    printf("Stato dopo X:\n");
    for (int i = 0; i < (1 << numQubits); i++) {
        printf("Stato %d: %f + %fi\n", i, creal(state->amplitudes[i]), cimag(state->amplitudes[i]));
    }

    // Applicare CNOT con controllo su qubit 0 e target su qubit 1
    applyCNOT(state, 0, 1);

    // Stato dopo CNOT
    printf("Stato dopo CNOT:\n");
    for (int i = 0; i < (1 << numQubits); i++) {
        printf("Stato %d: %f + %fi\n", i, creal(state->amplitudes[i]), cimag(state->amplitudes[i]));
    }

    freeState(state);
}
