/*
 * Test di Verifica dei Gate di QuantumSim
 * Questo programma testa tutti i gate nella libreria QuantumSim per assicurarsi che funzionino correttamente.
 * Inizializza gli stati dei qubit, applica i gate e stampa lo stato dopo ogni operazione.
 */

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>
#include "../src/quantum_sim.h"

int circuit (){
    // Inizializza il generatore di numeri casuali per le misurazioni
    srand(time(NULL));

    // Numero di qubit per il test
    int numQubits = 3;

    // Inizializza lo stato quantistico con tutti i qubit in |0>
    QubitState *state = initializeState(numQubits);
    printf("Stato iniziale:\n");
    printState(state);
    printf("\n");

    // Test del gate X sul qubit 0
    printf("Applico il gate X al qubit 0:\n");
    applyX(state, 0);
    printState(state);
    printf("\n");

    // Ripristina lo stato
    initializeStateTo(state, 0);
    printf("Stato ripristinato a |000>:\n");
    printState(state);
    printf("\n");

    // Test del gate Y sul qubit 1
    printf("Applico il gate Y al qubit 1:\n");
    applyY(state, 1);
    printState(state);
    printf("\n");

    // Ripristina lo stato
    initializeStateTo(state, 0);
    printf("Stato ripristinato a |000>:\n");
    printState(state);
    printf("\n");

    // Test del gate Z sul qubit 2
    printf("Applico il gate Z al qubit 2:\n");
    applyZ(state, 2);
    printState(state);
    printf("\n");

    // Test del gate Hadamard sul qubit 0
    printf("Applico il gate Hadamard al qubit 0:\n");
    applyHadamard(state, 0);
    printState(state);
    printf("\n");

    // Test del gate S sul qubit 1
    printf("Applico il gate S al qubit 1:\n");
    applyS(state, 1);
    printState(state);
    printf("\n");

    // Test del gate T sul qubit 2
    printf("Applico il gate T al qubit 2:\n");
    applyT(state, 2);
    printState(state);
    printf("\n");

    // Ripristina lo stato
    initializeStateTo(state, 0);
    printf("Stato ripristinato a |000>:\n");
    printState(state);
    printf("\n");

    // Test del gate CNOT con qubit di controllo 0 e qubit target 1
    printf("Applico il gate CNOT con qubit di controllo 0 e qubit target 1:\n");
    // Inizializza il qubit 0 a |1>
    initializeSingleQubitToOne(state, 0);
    printf("Prima del CNOT:\n");
    printState(state);
    applyCNOT(state, 0, 1);
    printf("Dopo il CNOT:\n");
    printState(state);
    printf("\n");

    // Ripristina lo stato
    initializeStateTo(state, 0);
    printf("Stato ripristinato a |000>:\n");
    printState(state);
    printf("\n");

    // Test del gate Toffoli (CCNOT) con qubit di controllo 0 e 1, qubit target 2
    printf("Applico il gate Toffoli con qubit di controllo 0 e 1, qubit target 2:\n");
    // Inizializza i qubit 0 e 1 a |1>
    initializeSingleQubitToOne(state, 0);
    initializeSingleQubitToOne(state, 1);
    printf("Prima del Toffoli:\n");
    printState(state);
    applyToffoli(state, 0, 1, 2);
    printf("Dopo il Toffoli:\n");
    printState(state);
    printf("\n");

    // Ripristina lo stato
    initializeStateTo(state, 0);
    printf("Stato ripristinato a |000>:\n");
    printState(state);
    printf("\n");

    // Test del gate Fredkin (CSWAP) con qubit di controllo 0, qubit target 1 e 2
    printf("Applico il gate Fredkin con qubit di controllo 0, qubit target 1 e 2:\n");
    // Inizializza il qubit 0 a |1> e il qubit 1 a |1>
    initializeSingleQubitToOne(state, 0);
    initializeSingleQubitToOne(state, 1);
    printf("Prima del Fredkin:\n");
    printState(state);
    applyFredkin(state, 0, 1, 2);
    printf("Dopo il Fredkin:\n");
    printState(state);
    printf("\n");

    // Ripristina lo stato
    initializeStateTo(state, 0);
    printf("Stato ripristinato a |000>:\n");
    printState(state);
    printf("\n");

    // Test della misura sul qubit 0
    printf("Misuro il qubit 0:\n");
    applyHadamard(state, 0);  // Porta il qubit 0 in sovrapposizione
    printState(state);
    MeasurementResult meas0 = measure(state, 0);
    printf("Risultato della misura del qubit 0: %d (Probabilità: |0>: %f, |1>: %f)\n", meas0.result, meas0.prob0, meas0.prob1);
    printState(state);
    printf("\n");

    // Ripristina lo stato
    initializeStateTo(state, 0);
    printf("Stato ripristinato a |000>:\n");
    printState(state);
    printf("\n");

    // Test della misura su tutti i qubit
    printf("Misuro tutti i qubit:\n");
    // Porta tutti i qubit in sovrapposizione
    applyHadamard(state, 0);
    applyHadamard(state, 1);
    applyHadamard(state, 2);
    printState(state);
    int *measAll = measure_all(state);
    printf("Risultati della misura:\n");
    for (int i = numQubits - 1; i >= 0; i--) {
        printf("Qubit %d: %d\n", i, measAll[i]);
    }
    free(measAll);
    printState(state);
    printf("\n");

    // Libera la memoria allocata per lo stato quantistico
    freeState(state);

    return 0;
}
