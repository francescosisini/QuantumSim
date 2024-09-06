#include "quantum_sim.h"
#include <stdio.h>
#include <math.h>

// Funzione per stampare lo stato quantistico
void print_state(QubitState *state) {
    long long dim = 1LL << state->numQubits; // Dimensione dello spazio di Hilbert
    for (long long i = 0; i < dim; i++) {
        printf("Stato %lld: %f + %fi\n", i, creal(state->amplitudes[i]), cimag(state->amplitudes[i]));
    }
}

// Funzione per calcolare e restituire la probabilità di uno stato specifico
void print_specific_state(QubitState *state, int target_state) {
    double prob = pow(cabs(state->amplitudes[target_state]), 2);
    printf("Probabilità dello stato target |1010> (decimale %d): %f\n", target_state, prob);
}

// Funzione per calcolare e restituire la probabilità di ogni stato
void print_probabilities(QubitState *state) {
    long long dim = 1LL << state->numQubits;
    double max_prob = 0.0;
    int max_state = -1;

    printf("Probabilità di ciascuno stato:\n");
    for (long long i = 0; i < dim; i++) {
        double prob = pow(cabs(state->amplitudes[i]), 2);
        printf("Stato %lld: probabilità %f\n", i, prob);
        if (prob > max_prob) {
            max_prob = prob;
            max_state = i;
        }
    }

    printf("\nStato con la probabilità più alta: |%04lld> (decimale: %lld) con probabilità %f\n", max_state, max_state, max_prob);
    if (max_state == 10) {
        printf("Lo stato target |1010> è stato trovato con alta probabilità!\n");
    } else {
        printf("Lo stato target |1010> NON è stato trovato come stato con la probabilità più alta.\n");
    }
}

// Oracolo che inverte il segno dello stato target |1010> (decimale 10)
void apply_grover_oracle(QubitState *state) {
    printf("Stato prima dell'oracolo:\n");
    print_state(state);

    // Applica gate X per mappare |1010> a |1111> per applicare il controllo
    applyX(state, 0); // Inverti qubit 0
    applyX(state, 2); // Inverti qubit 2

    // Applica CNOT controllato per segnare lo stato |1111>
    applyCNOT(state, 0, 1);
    applyCNOT(state, 1, 2);
    applyCNOT(state, 2, 3);
    applyZ(state, 3);  // Pauli-Z sul qubit 3

    // Re-inverti i qubit per tornare allo stato |1010>
    applyX(state, 0);
    applyX(state, 2);

    printf("Stato dopo l'oracolo:\n");
    print_state(state);
}

// Operatore di diffusione (inversione rispetto alla media)
void apply_grover_diffusion(QubitState *state) {
    printf("Stato prima della diffusione:\n");
    print_state(state);
    
    // Applica Hadamard a tutti i qubit
    for (int i = 0; i < 4; i++) {
        applyHadamard(state, i);
    }

    // Inverti rispetto allo stato |0000> usando Pauli-X e CNOT
    for (int i = 0; i < 4; i++) {
        applyX(state, i);
    }

    // Applica CNOT per riflettere rispetto a |0000>
    applyCNOT(state, 0, 1);
    applyCNOT(state, 1, 2);
    applyCNOT(state, 2, 3);
    applyZ(state, 3);  // Pauli-Z sul qubit 3

    // Re-inverti i qubit
    for (int i = 0; i < 4; i++) {
        applyX(state, i);
    }

    // Applica Hadamard a tutti i qubit di nuovo
    for (int i = 0; i < 4; i++) {
        applyHadamard(state, i);
    }

    printf("Stato dopo la diffusione:\n");
    print_state(state);
}

void circuit() {
    QubitState *state = initializeState(4); 
    printf("Stato iniziale:\n");

    // Inizializza lo stato di tutti i qubit in una sovrapposizione uniforme
    for (int i = 0; i < 4; i++) {
        applyHadamard(state, i);
    }
    print_state(state);

    // Numero di ripetizioni di Grover, approssimativamente sqrt(16) = 4
    int num_iterations = 4;

    // Esegui l'algoritmo di Grover
    for (int i = 0; i < num_iterations; i++) {
        printf("\nIterazione %d:\n", i + 1);
        apply_grover_oracle(state);        // Applica l'oracolo
        apply_grover_diffusion(state);     // Applica l'operatore di diffusione
        print_specific_state(state, 10);   // Stampa la probabilità dello stato target |1010>
    }

    // Stampa lo stato finale dopo l'algoritmo di Grover
    printf("\nStato finale dopo Grover:\n");
    print_state(state);

    // Calcola e stampa la probabilità di ciascun stato
    print_probabilities(state);
}
