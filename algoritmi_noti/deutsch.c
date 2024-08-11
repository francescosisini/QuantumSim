#include "quantum_sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>



void circuit() {
    int numQubits = 2;
    QubitState *state = initializeState(numQubits);

    // Inizializzazione degli stati: |0>|1>
    applyX(state, 1);  // Applica X al secondo qubit per iniziarlo in |1>

    // Applica Hadamard a entrambi i qubit
    applyHadamard(state, 0);  // Applica Hadamard al primo qubit
    applyHadamard(state, 1);  // Applica Hadamard al secondo qubit

    printf("Stato dopo Hadamard su entrambi i qubit:\n");
    printState(state);

    // Implementazione dell'oracolo U_f: qui useremo una funzione bilanciata
    // Supponiamo che f(x) = x (quindi l'oracolo inverte il secondo qubit se il primo è 1)
    applyCNOT(state, 0, 1);  // Applica CNOT con il primo qubit come controllo e il secondo come target

    printf("Stato dopo l'applicazione dell'oracolo U_f (bilanciato):\n");
    printState(state);

    // Applica Hadamard al primo qubit
    applyHadamard(state, 0);

    printf("Stato dopo l'ultima applicazione di Hadamard al primo qubit:\n");
    printState(state);

    // Misura il primo qubit per determinare se la funzione è costante o bilanciata
    int* results = measure_all(state);
    printf("Risultato della misura:\n");
    printf("Qubit 0: %d (0 = costante, 1 = bilanciata)\n", results[0]);

    // Pulizia della memoria
    free(results);
    freeState(state);
}

