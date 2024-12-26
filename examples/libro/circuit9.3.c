#include "../../src/quantum_sim.h"
#include <math.h>
#include <stdio.h>

#include "../../src/quantum_sim.h"
#include <math.h>
#include <stdio.h>

// Funzione per applicare Hadamard-Walsh su tutti i qubit
void applyHadamardWalsh(QubitState *state) {
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }
    printf(" Applicato Hadamard-Walsh su tutti i qubit per creare la sovrapposizione uniforme\n");
    printState(state);
}

// Funzione per applicare l'oracolo 
void applyOracle(QubitState *state) {
    printf(" Applicazione dell'oracolo per marcare gli stati target\n");
    
    // Marca lo stato |110⟩ e |111⟩ usando i gate CCZ
    applyX(state, 0);
    applyCCZ(state, 1, 2, 0);
    applyX(state, 0);
    applyCCZ(state, 1, 2, 0);

    printf("Stato marcato: |110⟩ e |111⟩ \n");
    printState(state);
}

/**
 * Applica l'operatore di diffusione basato su Z e CZ
 */
void applyDiffusion(QubitState *state) {
    printf(" Applicazione dell'operatore di diffusione per amplificare gli stati target\n");

    // Step 1: Applica Hadamard su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }

    // Step 2: Inverte il segno di tutti gli stati (applica gate X)
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
    }

    // Step 3: Applica un gate CCZ per la riflessione rispetto a |000⟩
    applyCCZ(state, 1, 2, 0);

    // Step 4: Ripristina i qubit applicando di nuovo X
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
    }

    // Step 5: Applica Hadamard su tutti i qubit per completare la riflessione
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("Operatore di diffusione applicato con successo\n");
    printState(state);
}

// Funzione principale per l'esecuzione dell'algoritmo di Grover
void circuit() {
    printf(" Avvio dell'algoritmo di Grover\n");

    // Inizializza lo stato con 3 qubit
    QubitState *state = initializeState(3);
    printf(" Stato iniziale con 3 qubit (|000⟩)\n");
    printState(state);

    // Step 1: Applica Hadamard-Walsh per creare la sovrapposizione uniforme
    applyHadamardWalsh(state);

    // Step 2: Applica l'oracolo per marcare gli stati target
    applyOracle(state);

    // Step 3: Applica l'operatore di diffusione per amplificare gli stati target
    applyDiffusion(state);

    // Misura i qubit
    printf(" Misurazione dello stato finale\n");
    for (int i = 0; i < state->numQubits; i++) {
        MeasurementResult result = measure(state, i);
        printf("Misura del qubit %d: %d\n", i, result.result);
    }

    printf(" Stato finale dopo la misurazione\n");
    printState(state);
}
