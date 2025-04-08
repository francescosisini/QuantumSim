#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "../src/quantum_sim.h"
#include "../src/quantum_density.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void circuit(void) {
    // 1. Inizializzazione dello stato puro a 2 qubit (|00>)
    QubitState *state = initializeState(2);
    printf("Stato puro iniziale:\n");
    printState(state);

    // 2. Applica Hadamard sul qubit 0 (LSB)
    applyHadamard(state, 0);
    printf("Dopo Hadamard su q0:\n");
    printState(state);

    // 3. Applica un gate di fase sul qubit 0: trasforma |01> -> e^(i*pi/4)|01>
    // (ricorda che in questo ordering il qubit 0 è il LSB)
    applyPhase(state, 0, M_PI/4);
    printf("Dopo applicazione della fase (pi/4) su q0:\n");
    printState(state);

    // 4. Converte lo stato puro in matrice densità e stampa il risultato
    DensityMatrix *dm = pureStateToDensityMatrix(state);
    printf("Matrice densità (dallo stato puro):\n");
    printDensityMatrix(dm);

    // 5. Applica il canale di dephasing sul qubit 0 con p = 0.5.
    // Costruzione degli operatori di Kraus:
    //    K0 = sqrt(1-p)*I,
    //    K1 = sqrt(p)*Z, con Z = diag(1, -1) applicato sul qubit 0 (LSB).
    int n = dm->numQubits;     // n = 2
    int dim = 1 << n;          // dim = 4
    double p = 0.5;
    double complex *K0 = calloc(dim * dim, sizeof(double complex));
    double complex *K1 = calloc(dim * dim, sizeof(double complex));
    if (!K0 || !K1) {
        perror("Errore allocazione operatori Kraus");
        exit(1);
    }
    // K0^(2): assegna sqrt(1-p) a ogni elemento diagonale
    for (int i = 0; i < dim; i++) {
        K0[i * dim + i] = sqrt(1 - p);
    }
    // K1^(2): per ogni elemento diagonale, il fattore è determinato dal valore del qubit 0 (LSB)
    for (int i = 0; i < dim; i++) {
        double factor = ((i & 1) == 0) ? 1.0 : -1.0;
        K1[i * dim + i] = sqrt(p) * factor;
    }
    double complex *krausOperators[2];
    krausOperators[0] = K0;
    krausOperators[1] = K1;

    applyKrausChannelDensity(dm, 2, krausOperators);
    printf("Matrice densità dopo dephasing su q0 (p=0.5):\n");
    printDensityMatrix(dm);

    // Pulizia delle risorse allocate.
    freeDensityMatrix(dm);
    freeState(state);
    free(K0);
    free(K1);
}

