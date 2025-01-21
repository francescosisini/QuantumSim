
#include "../../src/quantum_sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <time.h>

int circuit(void) {
    srand(time(NULL)); // Inizializza il generatore di numeri casuali

    // Inizializza lo stato quantistico con 1 qubit
    QubitState *state = initializeState(1);

    // Circuito 1: Applicazione del gate Hadamard seguito da una misurazione
    printf("Circuito 1: Applicazione del gate Hadamard seguito da una misurazione\n");
    initializeStateTo(state, 0); // Stato iniziale |0>
    applyHadamard(state, 0);      // Applica il gate Hadamard
    printf("Stato dopo H:\n");
    printState(state);
    MeasurementResult m1 = measure(state, 0); // Misura il qubit 0
    printf("Risultato della misurazione: %d\n\n", m1.result);

    // Circuito 2: Applicazione dei gate Hadamard e Pauli-X seguiti da una misurazione
    printf("Circuito 2: Applicazione dei gate Hadamard e Pauli-X seguiti da una misurazione\n");
    initializeStateTo(state, 0); // Reset allo stato |0>
    applyHadamard(state, 0);      // Applica il gate Hadamard
    applyX(state, 0);              // Applica il gate Pauli-X
    printf("Stato dopo H e X:\n");
    printState(state);
    MeasurementResult m2 = measure(state, 0); // Misura il qubit 0
    printf("Risultato della misurazione: %d\n\n", m2.result);

    // Libera la memoria allocata per lo stato quantistico
    freeState(state);

    return 0;
}
