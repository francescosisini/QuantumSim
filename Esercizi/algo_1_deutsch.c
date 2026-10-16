#include "../src/quantum_sim.h"
#include <stdio.h>

// Definizione della funzione f(x)
void applyUf(QubitState* state, int x, int y, int type) {
    switch (type) {
        case 0: // f(x) = 0, costante
            break;
        case 1: // f(x) = 1, costante
            applyX(state, y);
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
    // Scelta di U_f
    int type;
    printf("Scegli il tipo di funzione f(x):\n");
    printf("  0 -> f(x) = 0   (costante)\n");
    printf("  1 -> f(x) = 1   (costante)\n");
    printf("  2 -> f(x) = x   (bilanciata)\n");
    printf("  3 -> f(x) = !x  (bilanciata)\n");
    printf("Inserisci il tipo (0-3): ");
    scanf("%d", &type);
    // Controllo di validità
    if (type < 0 || type > 3) {
        printf("Usa un valore tra 0 e 3.\n");
        return;
    }

    // Preparazione dello stato iniziale in |0>|1>
    QubitState* state = initializeState(2);
    applyX(state, 1);
    printf("\nStato iniziale:\n");
    printState(state);

    // Applicazione di Hadamard a entrambi i qubit
    applyHadamard(state, 0);
    applyHadamard(state, 1);
    printf("\nStato dopo H sui 2 qubits:\n");
    printState(state);

    // Applicazione di U_f
    applyUf(state, 0, 1, type);
    printf("\nStato dopo U_f:\n");
    printState(state);

    // Applicazione di Hadamard al primo qubit
    applyHadamard(state, 0);
    printf("\nStato dopo H sul primo qubit:\n");
    printState(state);

    // Misura del primo qubit
    MeasurementResult res = measure(state, 0);
    printf("\nRisultato misura: %d\n", res.result);

    // Interpretazione del risultato
    if (res.result == 0) {
        printf("f(x) \'e costante.\n");
    } else {
        printf("f(x) \'e bilanciata.\n");
    }

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
