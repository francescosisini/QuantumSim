#include "quantum_sim.h"
#include <stdlib.h>
#include <stdio.h>

void circuit() {
    int numQubits = 6; // Definisci il numero di qubits
    int numIterations = 8; // Numero di iterazioni (circa sqrt(2^numQubits))
    QubitState *state = initializeState(numQubits); // Inizializza lo stato quantistico

    // Stato marcato |111111>
    int markedState[] = {1, 1, 1, 1, 1, 1};

    printf("Stato quantistico inizializzato.\n");

    // Applicare Hadamard a tutti i qubits per creare una sovrapposizione
    for (int i = 0; i < numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("Hadamard applicato a tutti i qubits.\n");

    // Iterazioni dell'algoritmo di Grover
    for (int iter = 0; iter < numIterations+4; iter++) {
        printf("Iterazione %d\n", iter + 1);

        // --- Inizio dell'oracolo di Grover ---
        // Questo oracolo inverte la fase dello stato |111111>

        // Applica una serie di CNOT per marcare lo stato |111111>
        // CNOT con controllo sui qubits 0-4 e target sul qubit 5
        for (int i = 0; i < numQubits - 1; i++) {
            applyCNOT(state, i, numQubits - 1);
        }

        // Applica Z al sesto qubit (Qubit 5) per invertire la fase
        applyZ(state, numQubits - 1);

        // Riapplica la serie di CNOT per completare l'oracolo
        for (int i = 0; i < numQubits - 1; i++) {
            applyCNOT(state, i, numQubits - 1);
        }

        printf("Oracolo di Grover applicato.\n");
        // --- Fine dell'oracolo di Grover ---

        // --- Inizio della diffusione di Grover ---
        // La diffusione amplifica le ampiezze degli stati marcati

        // Applicare Hadamard a tutti i qubits
        for (int i = 0; i < numQubits; i++) {
            applyHadamard(state, i);
        }

        // Applicare X a tutti i qubits
        for (int i = 0; i < numQubits; i++) {
            applyX(state, i);
        }

        // Applica una serie di CNOT con controllo sui qubits 0-4 e target sul qubit 5
        for (int i = 0; i < numQubits - 1; i++) {
            applyCNOT(state, i, numQubits - 1);
        }

        // Riapplicare X a tutti i qubits
        for (int i = 0; i < numQubits; i++) {
            applyX(state, i);
        }

        // Riapplicare Hadamard a tutti i qubits
        for (int i = 0; i < numQubits; i++) {
            applyHadamard(state, i);
        }

        printf("Diffusione di Grover applicata.\n");
        // --- Fine della diffusione di Grover ---
    }

    // Misurare lo stato finale
    int *results = measure_all(state);
    printf("Risultato della misura:\n");

    int found = 1; // Flag per determinare se abbiamo trovato lo stato marcato
    for (int i = 0; i < numQubits; i++) {
        printf("Qubit %d: %d\n", i, results[i]);
        if (results[i] != markedState[i]) {
            found = 0;
        }
    }

    if (found) {
        printf("Lo stato marcato |111111> è stato trovato!\n");
    } else {
        printf("Lo stato marcato |111111> NON è stato trovato.\n");
    }

    free(results);
    freeState(state); // Libera la memoria dello stato quantistico

    printf("Memoria liberata.\n");
}
