#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(3); // Tre qubit: 1 da teletrasportare, 2 entangled

    // Stato del qubit da teletrasportare
    initializeStateTo(state, 0); // Inizializza il primo qubit
    applyHadamard(state, 0);     // Stato iniziale da teletrasportare

    // Stato entangled tra il secondo e il terzo qubit
    applyHadamard(state, 1);
    applyCNOT(state, 1, 2);
    printf("Stato iniziale:\n");
    printState(state);

    // Misura di Bell sui primi due qubit
    applyCNOT(state, 0, 1);
    applyHadamard(state, 0);
    MeasurementResult result1 = measure(state, 0);
    MeasurementResult result2 = measure(state, 1);
    printf("Risultati della misura di Bell: %d, %d\n", result1.result, result2.result);

    // Magri applica trasformazioni basate sui risultati
    if (result1.result == 1) applyX(state, 2);
    if (result2.result == 1) applyZ(state, 2);

    printf("Stato del qubit teletrasportato:\n");
    printState(state);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
