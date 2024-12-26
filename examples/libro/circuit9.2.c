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

// Funzione per applicare l'oracolo per gli stati target |11⟩ e |01⟩
void applyOracle(QubitState *state) {
    printf("[INFO] Applicazione dell'oracolo\n");
    
    // Marca lo stato |11⟩ usando un gate CZ
    applyCZ(state, 0, 1);
    printf("[DEBUG] Marcato lo stato |11⟩\n");
    
    // Marca lo stato |01⟩ usando X, CZ, X
    applyX(state, 0);           // Trasforma |01⟩ in |11⟩
    applyCZ(state, 0, 1);       // Marca |11⟩ (equivalente a |01⟩ prima della trasformazione)
    applyX(state, 0);           // Ripristina lo stato originale
    printf("[DEBUG] Marcato lo stato |01⟩\n");

    printState(state);
}

// Funzione per l'operatore di diffusione (inversione rispetto alla media)
void applyDiffusion(QubitState *state) {
    printf("[INFO] Applicazione dell'operatore di diffusione\n");
    
    // Applicazione della sequenza Hadamard -> X -> CZ -> X -> Hadamard
    applyHadamardWalsh(state);
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
    }
    applyCZ(state, 0, 1);
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
    }
    applyHadamardWalsh(state);

    printf("[DEBUG] Operatore di diffusione applicato\n");
    printState(state);
}

// Funzione principale
void circuit() {
    printf("[INFO] Avvio dell'algoritmo di Grover\n");

    // Inizializza lo stato con 2 qubit
    QubitState *state = initializeState(2);
    printf("[INFO] Stato iniziale con 2 qubit\n");
    printState(state);

    // Applica Hadamard-Walsh per creare la sovrapposizione uniforme
    applyHadamardWalsh(state);

    // Applica l'oracolo per marcare gli stati |11⟩ e |01⟩
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

