#include "../../src/quantum_sim.h"
#include <math.h>
#include <stdio.h>

// Funzione per applicare Hadamard-Walsh
void applyHadamardWalsh(QubitState *state) {
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }
    printf("[INFO] Applicato Hadamard-Walsh su tutti i qubit\n");
    printState(state);
}

// Funzione per applicare l'oracolo 
void applyOracle(QubitState *state) {
    printf("[INFO] Applicazione dell'oracolo\n");
    
    // Marca lo stato |10⟩ usando un gate CZ
    applyX(state,0);
    applyCCZ(state,1, 2, 0);
    applyX(state,0);
    applyCCZ(state,1, 2, 0);
    printf("[DEBUG] Marcato lo stato |110⟩ e |111⟩ \n");
      printState(state);
}

/**
 * Applica l'operatore di diffusione basato su Z e CZ
 */
void applyDiffusion(QubitState *state) {
    printf("[INFO] Applicazione dell'operatore di diffusione\n");

    // Step 1: Hadamard su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }

    // Step 2: Z su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i); // Inverte il segno di tutti gli stati
    }

    // Step 3: Controlled-Z (CZ) tra i qubit
    applyCCZ(state,1,2, 0); // CZ applica una riflessione rispetto a |00>


    // Step 2: Z su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i); // Inverte il segno di tutti gli stati
    }

    
    // Step 4: Hadamard su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("[DEBUG] Operatore di diffusione applicato\n");
    printState(state);
}


// Funzione principale
void circuit() {
    printf("[INFO] Avvio dell'algoritmo di Grover\n");

    // Inizializza lo stato con 3 qubit
    QubitState *state = initializeState(3);
    printf("[INFO] Stato iniziale con 3 qubit\n");
    printState(state);

    // Applica Hadamard-Walsh per creare la sovrapposizione uniforme
    applyHadamardWalsh(state);

    // Applica l'oracolo per marcare gli stati target
    applyOracle(state);

    // Applica l'operatore di diffusione
    applyDiffusion(state);


    // Misura i qubit
    printf("[INFO] Misurazione dello stato finale\n");
    for (int i = 0; i < state->numQubits; i++) {
        MeasurementResult result = measure(state, i);
        printf("[RESULT] Misura del qubit %d: %d\n", i, result.result);
    }

    printf("[INFO] Stato finale dopo la misurazione\n");
    printState(state);
}

