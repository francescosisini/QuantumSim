#include "quantum_sim.h"

void circuit(QubitState *state) {
    int numQubits = state->numQubits;

    // Applicare Hadamard a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyHadamard(state, i);
    }

    // Supponiamo che l'elemento marcato sia lo stato |11>
    // Applicare l'oracolo di Grover
    applyCNOT(state, 0, 1);  // Controllo il primo qubit, target il secondo qubit
    applyX(state, 0);  // Applico X gate al primo qubit
    applyCNOT(state, 0, 1);  // Controllo il primo qubit, target il secondo qubit
    applyX(state, 0);  // Applico X gate al primo qubit

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
}
