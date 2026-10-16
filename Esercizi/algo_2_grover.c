#include "../src/quantum_sim.h"
#include <math.h>
#include <stdio.h>

// Applica Hadamard-Walsh su tutti i qubit
void applyHadamardWalsh(QubitState *state) {
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }
}

// Oracolo 
void applyOracle(QubitState *state) {
    printf("\nApplicazione dell'oracolo per marcare gli stati target\n");
    // Marca lo stato |110⟩ e |111⟩ usando i gate CCZ
    applyX(state, 0);
    applyCCZ(state, 1, 2, 0);
    applyX(state, 0);
    applyCCZ(state, 1, 2, 0);
    printf("Stato marcato: |110⟩ e |111⟩ \n");
    printState(state);
}

// Operatore di diffusione
void applyDiffusion(QubitState *state) {
    printf("\nApplicazione dell'operatore di diffusione per amplificare gli stati target\n");
    // Step 1: Applica H su tutti i qubit
    applyHadamardWalsh(state);
    // Step 2: Inverte il segno di tutti gli stati
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
    }
    // Step 3: CCZ riflette rispetto a |000⟩
    applyCCZ(state, 1, 2, 0);
    // Step 4: Ripristina i qubit applicando X
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
    }
    // Step 5: Applica H su tutti i qubit
    applyHadamardWalsh(state);
    printState(state);
}

// Algoritmo di Grover
void circuit() {
    printf("Avvio dell'algoritmo di Grover\n");

    // Inizializza lo stato con 3 qubit
    QubitState *state = initializeState(3);
    printf("\nStato iniziale con 3 qubit (|000⟩)\n");
    printState(state);

    // Step 1: Applica H su tutti i qubit
    printf("\nApplicazione di Hadamard su tutti i qubit\n");
    applyHadamardWalsh(state);
    printState(state);

    // Step 2: Applica l'oracolo
    applyOracle(state);

    // Step 3: Applica l'operatore di diffusione
    applyDiffusion(state);

    // Misura i qubit
    printf("\nMisurazione dello stato finale\n");
    for (int i = 0; i < state->numQubits; i++) {
        MeasurementResult r = measure(state, i);
        printf("Misura del qubit %d: %d\n", i, r.result);
    }
    printf("\nStato finale dopo la misura\n");
    printState(state);
}
