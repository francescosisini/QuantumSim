#include "quantum_sim.h"
#include <stdio.h>

void circuit() {
    int numQubits = 2;
    QubitState *state = initializeState(numQubits);

    // Istruzione non riconosciuta: OPENQASM 2.0;
    // Istruzione non riconosciuta: include "qelib1.inc";
    // Istruzione non riconosciuta: gate nG0 ( param ) q1, q2  {
    // Istruzione non riconosciuta: //***f(q1) ccostante***
    // Istruzione non riconosciuta: //id q1;
    applyX(state, 0);
    // Istruzione non riconosciuta: //***f(q1) NON-ccostante***
    applyCNOT(state, 32768, 0);
    // Istruzione non riconosciuta: }
    // Istruzione non riconosciuta: 
    // Istruzione non riconosciuta: 
    // Istruzione non riconosciuta: id q[0];
    applyX(state, 1);
    applyHadamard(state, 0);
    applyHadamard(state, 1);
    // Istruzione non riconosciuta: //oracolo
    applyCNOT(state, 32768, 1);
    // Istruzione non riconosciuta: 
    applyHadamard(state, 0);
    int result = measure(state, 0);
    c[0] = result;
    printState(state);
    freeState(state);
}
