#include "quantum_sim.h"
#include <stdio.h>

void circuit() {
    int numQubits = 2; // Definisci il numero di qubits
    QubitState *state = initializeState(numQubits); // Inizializza lo stato quantistico

    printf("Stato quantistico inizializzato.\n");

    // Applicare Hadamard a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("Hadamard applicato a tutti i qubits.\n");

    // Supponiamo che l'elemento marcato sia lo stato |11>
    // Applicare l'oracolo di Grover
    applyCNOT(state, 0, 1);  // Controllo il primo qubit, target il secondo qubit
    applyX(state, 0);  // Applico X gate al primo qubit
    applyCNOT(state, 0, 1);  // Controllo il primo qubit, target il secondo qubit
    applyX(state, 0);  // Applico X gate al primo qubit

    printf("Oracolo di Grover applicato.\n");

    // Applicare la diffusione di Grover
    // Applicare Hadamard a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyHadamard(state, i);
    }

    // Applicare X a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyX(state, i);
    }

    // Applicare una porta multi-controlled-Z (in questo caso, controllato su due qubits)
    applyCNOT(state, 0, 1);
    applyZ(state, 1);
    applyCNOT(state, 0, 1);

    // Applicare X a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyX(state, i);
    }

    // Applicare Hadamard a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("Diffusione di Grover applicata.\n");

    // Misurare lo stato finale
    int *results = measure_all(state);
    printf("Risultato della misura:\n");
    for (int i = 0; i < numQubits; i++) {
        printf("Qubit %d: %d\n", i, results[i]);
    }

    free(results);
    freeState(state); // Libera la memoria dello stato quantistico

    printf("Memoria liberata.\n");
}
