#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(3); // Tre qubit: 1 dati, 2 ancillari

    // Stato iniziale del qubit dati
    initializeStateTo(state, 0);
    printf("Stato iniziale:\n");
    printState(state);

    // Codifica ridondante (CNOT per la duplicazione)
    applyCNOT(state, 0, 1);
    applyCNOT(state, 0, 2);
    printf("Stato dopo la codifica:\n");
    printState(state);

    // Simula un errore bit-flip sul secondo qubit
    applyX(state, 1);
    printf("Stato dopo il bit-flip:\n");
    printState(state);

    // Decodifica e correzione (CNOT inversi e misura)
    applyCNOT(state, 0, 1);
    applyCNOT(state, 0, 2);
    MeasurementResult result1 = measure(state, 1);
    MeasurementResult result2 = measure(state, 2);

    if (result1.result != result2.result) {
        applyX(state, 0); // Corregge l'errore
    }

    printf("Stato finale dopo la correzione:\n");
    printState(state);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
