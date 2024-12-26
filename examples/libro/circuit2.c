#include <stdio.h>
#include "../src/quantum_sim.h"

void circuit(void){
    QubitState* state = initializeState(1); // Stato iniziale con un qubit
    printState(state);                     // Stampa lo stato iniziale |0>
    applyHadamard(state, 0);              // Applica il gate Hadamard
    printState(state);                     // Stampa lo stato in sovrapposizione
    measure(state, 0);                    // Misura il qubit
    printState(state);                     // Stampa lo stato post-misura
    freeState(state);                      // Libera la memoria
    return 0;
}
