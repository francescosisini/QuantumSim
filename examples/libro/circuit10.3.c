#include "quantum_sim.h"
#include <stdio.h>

int circuit(void) {
    QubitState* state = initializeState(2);
    applyX(state,1);
    // Applica Hadamard ai qubit
    applyHadamard(state, 0); //|+>
    applyHadamard(state, 1); //|->
    // Oracolo per una funzione bilanciata
    applyCNOT(state, 0, 1);
    // Applica Hadamard al qubit di input
    applyHadamard(state, 0);
    MeasurementResult result = measure(state, 0);
    if (result.result == 0) {
        printf("La funzione \'e costante.\n");
    } else {
        printf("La funzione \'e bilanciata.\n");
    }
    freeState(state);
}
