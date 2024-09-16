#include <stdio.h>
#include "quantum_sim.h"

void circuit(QubitState* state) {
    // Inizializza lo stato con 3 qubit
    state = initializeState(3);  
    
    int control1 = 0;
    int control2 = 1;
    int target = 2;

    printState(state);

    // Applica la porta Toffoli
    applyToffoli(state, control1, control2, target);

    // Stampa lo stato dopo aver applicato la porta Toffoli
    printf("Stato dopo l'applicazione del Toffoli:\n");
    printState(state);

    applyX(state,0);
    applyX(state,1);

    printState(state);

    // Applica la porta Toffoli
    applyToffoli(state, control1, control2, target);

    // Stampa lo stato dopo aver applicato la porta Toffoli
    printf("Stato dopo l'applicazione del Toffoli:\n");
    printState(state);



    // Libera la memoria dello stato
    freeState(state);
}
