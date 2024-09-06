#include <stdio.h>
#include "quantum_sim.h"

void test_gate(const char* gate_name, void (*gate_func)(QubitState*, int), QubitState *state, int target) {
    printf("| %-10s | Qubit %-10d | Initial State:\n", gate_name, target);
    printState(state);  // Stato iniziale
    gate_func(state, target);  // Applica il gate
    printf("-> After:\n");
    printState(state);  // Stato dopo il gate
    printf("|\n");
}

void test_cnot_gate(QubitState *state, int control, int target) {
    printf("| CNOT        | Control: Qubit %-3d | Target: Qubit %-3d | Initial State:\n", control, target);
    printState(state);  // Stato iniziale
    applyCNOT(state, control, target);  // Applica CNOT
    printf("-> After:\n");
    printState(state);  // Stato dopo CNOT
    printf("|\n");
}

void test_measurement(QubitState *state, int qubit) {
    printf("| Measure     | Qubit %-10d | Initial State:\n", qubit);
    printState(state);  // Stato iniziale
    MeasurementResult result = measure(state, qubit);  // Misurazione del qubit
    printf("-> Probabilities: |0>: %.6f |1>: %.6f | Measurement Result: %-2d |\n", result.prob0, result.prob1, result.result);
}

void test_state_combinations(void (*gate_func)(QubitState*, int), const char* gate_name) {
    for (int i = 0; i < 4; i++) {
        QubitState *state = initializeState(2);  // Inizializza stato a 2 qubit
        initializeStateTo(state, i);  // Imposta lo stato di partenza nei 4 stati computazionali
        test_gate(gate_name, gate_func, state, 0);  // Applica il gate
        freeState(state);
    }
    
    for (int i = 0; i < 4; i++) {
        QubitState *state = initializeState(2);  // Inizializza stato a 2 qubit
        applyHadamard(state, 0);  // Applica Hadamard per sovrapposizione
        test_gate(gate_name, gate_func, state, 0);  // Applica il gate
        freeState(state);
    }
}

void circuit() {
    printf("+-------------+-------------------+---------------------------------------------------+\n");
    printf("| Gate        | Target/Control     | State                                              |\n");
    printf("+-------------+-------------------+---------------------------------------------------+\n");

    // Test sui 4 stati computazionali e di Hadamard
    test_state_combinations(applyHadamard, "Hadamard");
    test_state_combinations(applyX, "Pauli-X");
    test_state_combinations(applyZ, "Pauli-Z");
    test_state_combinations(applyT, "T");
    test_state_combinations(applyS, "S");

    // Test CNOT
    for (int i = 0; i < 4; i++) {
        QubitState *state = initializeState(2);
        initializeStateTo(state, i);
        test_cnot_gate(state, 0, 1);
        freeState(state);
    }

    // Test misurazioni
    for (int i = 0; i < 4; i++) {
        QubitState *state = initializeState(2);
        initializeStateTo(state, i);
        test_measurement(state, 0);
        test_measurement(state, 1);
        freeState(state);
    }

    printf("+-------------+-------------------+---------------------------------------------------+\n");
}
