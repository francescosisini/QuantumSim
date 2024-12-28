#include "../../src/quantum_sim.h"
#include <math.h>
#include <stdio.h>

// Funzione per applicare Hadamard-Walsh
void applyHadamardWalsh(QubitState *state) {
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }
    printf("Applicato Hadamard-Walsh su tutti i qubit\n");
    printState(state);
}

// Funzione per applicare l'oracolo 
void applyOracle(QubitState *state) {
    printf("Applicazione dell'oracolo\n");
    
    // Marca lo stato 10 usando un gate CZ
    applyX(state,0);
    applyCZ(state, 1, 0);
    applyX(state,0);
    printf(" Marcato lo stato 10\n");
      printState(state);
}

/**
 * Applica l'operatore di diffusione basato su Z e CZ
 */
void applyDiffusion(QubitState *state) {
    printf("Applicazione dell'operatore di diffusione\n");

    // Step 1: Hadamard su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }

    // Step 2: Z su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyZ(state, i); // Inverte il segno di tutti gli stati
    }

    // Step 3: Controlled-Z (CZ) tra i qubit
    applyCZ(state, 0, 1); // CZ applica una riflessione rispetto a |00>

    // Step 4: Hadamard su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("Operatore di diffusione applicato\n");
    printState(state);
}


// Funzione principale
void circuit() {
    printf("Avvio dell'algoritmo di Grover\n");

    // Inizializza lo stato con 2 qubit
    QubitState *state = initializeState(2);
    printf("Stato iniziale con 2 qubit\n");
    printState(state);

    // Applica Hadamard-Walsh per creare la sovrapposizione uniforme
    applyHadamardWalsh(state);

    // Applica l'oracolo per marcare gli stati |11⟩ e |01⟩
    applyOracle(state);

    // Applica l'operatore di diffusione
    applyDiffusion(state);

    // Misura i qubit
    printf("Misurazione dello stato finale\n");
    for (int i = 0; i < state->numQubits; i++) {
        MeasurementResult result = measure(state, i);
        printf("Misura del qubit %d: %d\n", i, result.result);
    }

    printf("Stato finale dopo la misurazione\n");
    printState(state);
}

