#include "../src/quantum_sim.h"
#include <math.h>
#include <complex.h>
#include <stdio.h>

#define M_PI acos(-1)

// Funzione per inizializzare lo stato in una sovrapposizione uniforme
void initializeGrover(QubitState *state) {
    printf("[INFO] Inizializzazione della sovrapposizione uniforme\n");
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }
    printState(state);
}

// Funzione che implementa l'oracolo per marcare lo stato target |101⟩
void applyOracle(QubitState *state) {
    printf("[INFO] Applicazione dell'oracolo per marcare lo stato |101⟩\n");

    // Trasforma |101⟩ in |111⟩
    applyX(state, 0);
    applyX(state, 2);

    // Applica il Toffoli per invertire lo stato target
    applyToffoli(state, 0, 1, 2);

    // Ripristina i qubit
    applyX(state, 0);
    applyX(state, 2);

    printState(state);
}

// Funzione che implementa l'operatore di diffusione
void applyDiffusion(QubitState *state) {
    printf("[INFO] Applicazione dell'operatore di diffusione\n");

    // Preparazione: Hadamard e X
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
        applyX(state, i);
    }

    // Applica il Toffoli per l'inversione dello stato medio
    applyToffoli(state, 0, 1, 2);

    // Ripristino: X e Hadamard
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
        applyHadamard(state, i);
    }

    printState(state);
}

// Funzione principale per eseguire l'algoritmo di Grover
void circuit() {
    printf("[INFO] Avvio dell'algoritmo di Grover\n");

    // Inizializza lo stato
    QubitState *state = initializeState(3);
    printState(state);

    // Inizializzazione della sovrapposizione uniforme
    initializeGrover(state);

    // Calcolo del numero di iterazioni ottimali
    int numQubits = state->numQubits;
    int N = 1 << numQubits; // N = 2^numQubits
    int numIterations = (int)(M_PI * sqrt(N) / 4);
    printf("[INFO] Numero ottimale di iterazioni: %d\n", numIterations);

    // Ciclo delle iterazioni di Grover
    for (int i = 0; i < numIterations; i++) {
        printf("[INFO] Iterazione %d\n", i + 1);

        // Applicazione dell'oracolo
        applyOracle(state);

        // Applicazione dell'operatore di diffusione
        applyDiffusion(state);
    }

    // Misura dello stato finale
    printf("[INFO] Misura dello stato finale\n");
    for (int i = 0; i < state->numQubits; i++) {
        MeasurementResult result = measure(state, i);
        printf("[RESULT] Misura del qubit %d: %d\n", i, result.result);
    }

    printState(state);
}
