#include "quantum_sim.h"
#include <stdio.h>

// Definizione della funzione f(x)
void applyUf(QubitState* state, int x, int y, int type) {
    switch (type) {
        case 0: // f(x) = 0, costante
            // Nessuna operazione
            break;
        case 1: // f(x) = 1, costante
            applyZ(state, y);
            break;
        case 2: // f(x) = x, bilanciata
            applyCNOT(state, x, y);
            break;
        case 3: // f(x) = !x, bilanciata
            applyCNOT(state, x, y);
            applyX(state, y);
            break;
    }
}

int circuit(void) {
    QubitState* state = initializeState(2); // Due qubit: controllo e target

    // Stato iniziale |0>|1>

    applyX(state, 1);           // Configura il secondo qubit a |1>
    printf("Stato iniziale:\n");
    printState(state);

    // Applica Hadamard a entrambi i qubit
    applyHadamard(state, 0);
    applyHadamard(state, 1);
    printf("Stato dopo Hadamard:\n");
    printState(state);

    // Applicazione di U_f
    int type = 0; // Scegliere il tipo di funzione: 0, 1, 2 o 3
    applyUf(state, 0, 1, type);
    printf("Stato dopo U_f:\n");
    printState(state);

    // Applica Hadamard al primo qubit
    applyHadamard(state, 0);
    printf("Stato dopo Hadamard finale:\n");
    printState(state);

    // Misura del primo qubit
    MeasurementResult result = measure(state, 0);
    printf("Risultato della misura: %d\n", result.result);

    // Interpretazione del risultato
    if (result.result == 0) {
        printf("La funzione f(x) \'e costante.\n");
    } else {
        printf("La funzione f(x) \'e bilanciata.\n");
    }

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
