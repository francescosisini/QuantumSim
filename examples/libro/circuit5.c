#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(3); // Tre qubit inizializzati a |000>

    // Stato iniziale
    printf("Stato iniziale:\n");
    printState(state);

    // Imposta i bit di input a=1, b=1
    applyX(state, 0); // Imposta il primo qubit (a) a |1>
    applyX(state, 1); // Imposta il secondo qubit (b) a |1>
    printf("Stato dopo l'inizializzazione degli input:\n");
    printState(state);


    // Applica la porta Toffoli (per il bit di riporto)
    applyToffoli(state, 0, 1, 2);
    
    // Applica il gate CNOT (per il bit di somma)
    applyCNOT(state, 0, 1);
    
    printf("Stato dopo l'implementazione del circuito half-adder:\n");
    printState(state);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
