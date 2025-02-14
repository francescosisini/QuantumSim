#include "../src/quantum_sim.h"
#include <math.h>
#include <complex.h>
#include <stdio.h>


// Funzione principale per eseguire l'algoritmo di Grover
void circuit() {
    // Inizializza lo stato a 3 qubit
    QubitState *state = initializeState(3);

    // h q[0];
    applyHadamard(state, 0);

    // h q[1];
    applyHadamard(state, 1);

    // h q[2];
    applyHadamard(state, 2);
    
    // h q[0];
    applyHadamard(state, 0);

    // cx q[2], q[0];
    applyCNOT(state, 2, 0);

    // h q[0];
    applyHadamard(state, 0);

    // h q[2];
    applyHadamard(state, 2);

    // h q[0];
    applyHadamard(state, 0);

    // x q[2];
    applyX(state, 2);

    // cx q[1], q[0];
    applyCNOT(state, 1, 0);

    // h q[0];
    applyHadamard(state, 0);

    // h q[1];
    applyHadamard(state, 1);

    // h q[0];
    applyHadamard(state, 0);

    // x q[1];
    applyX(state, 1);

    // x q[0];
    applyX(state, 0);

    // h q[0];
    applyHadamard(state, 0);

    // ccx q[2], q[1], q[0]; (Toffoli gate)
    applyToffoli(state, 2, 1, 0);

    // h q[0];
    applyHadamard(state, 0);

    // x q[1];
    applyX(state, 1);

    // x q[2];
    applyX(state, 2);

    // x q[0];
    applyX(state, 0);

    // h q[1];
    applyHadamard(state, 1);

    // h q[2];
    applyHadamard(state, 2);

    // h q[0];
    applyHadamard(state, 0);

    printState(state);
}
