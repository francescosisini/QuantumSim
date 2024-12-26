#include "../../src/quantum_sim.h"

int circuit(void) {
    // Inizializza uno stato quantistico con 3 qubit
    QubitState* state = initializeState(3);

     printState(state);
     applyX(state,1);
     applyX(state,2);
     applyX(state,0);
    
     
    // Applica il gate CCZ
    applyCCZ(state, 0, 1, 2);
     applyX(state,1);
     applyX(state,2);


    // Stampa lo stato finale
    printState(state);

    return 0;
}
