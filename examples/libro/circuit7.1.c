#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(2); // Inizializza due qubit entangled

    // Stato entangled iniziale
    applyHadamard(state, 0); // Crea la sovrapposizione
    applyCNOT(state, 0, 1);  // Entanglement con il CNOT
    printf("Stato iniziale entangled:\n");
    printState(state);

    // Fabbri applica una trasformazione sul suo qubit
    applyX(state, 0); // Ad esempio, trasforma secondo il bit classico "Sud"
    printf("Stato dopo la trasformazione di Fabbri:\n");
    printState(state);

    // Magri decodifica
    applyCNOT(state, 0, 1); // CNOT per la decodifica
    applyHadamard(state, 0); // Hadamard per la decodifica

    // Magri misura i due qubit
    MeasurementResult result1 = measure(state, 0);
    MeasurementResult result2 = measure(state, 1);
    printf("Risultati delle misure: %d, %d\n", result1.result, result2.result);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
