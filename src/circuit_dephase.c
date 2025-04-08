#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "../src/quantum_sim.h"
#include "../src/quantum_density.h"

void circuit(void) {
    // 1. Inizializza uno stato puro a 2 qubit.
    QubitState* state = initializeState(2);
    printf("Stato puro iniziale:\n");
    printState(state);

    // 2. Applica Hadamard sul qubit 0.
    applyHadamard(state, 0);
    printf("Dopo Hadamard su q0:\n");
    printState(state);

    // 3. Converte lo stato puro in una matrice densità.
    DensityMatrix* dm = pureStateToDensityMatrix(state);
    printf("Matrice densità (dalla conversione dello stato puro):\n");
    printDensityMatrix(dm);

    // 4. Applica un canale di dephasing sul primo qubit con p = 0.5.
    // Gli operatori di Kraus per un singolo qubit sono:
    //    K0 = sqrt(1-p)*I     e    K1 = sqrt(p)*Z, dove Z = diag(1, -1).
    // Estendiamo questi operatori al sistema a 2 qubit:
    //    K0^(2) = K0 ⊗ I   e   K1^(2) = K1 ⊗ I.
    int n = dm->numQubits;    // n = 2
    int dim = 1 << n;         // dim = 4
    double p = 0.5;
    double complex *K0 = calloc(dim * dim, sizeof(double complex));
    double complex *K1 = calloc(dim * dim, sizeof(double complex));
    if (!K0 || !K1) {
        perror("Errore allocazione operatori Kraus");
        exit(1);
    }
    // K0^(2): sqrt(1-p) su tutti gli elementi diagonali
    for (int i = 0; i < dim; i++) {
        K0[i * dim + i] = sqrt(1 - p);
    }
    // K1^(2): sqrt(p) * (Z ⊗ I)
    // Z ⊗ I = diag(1, 1, -1, -1)
    for (int i = 0; i < dim; i++) {
        double factor = (i < (dim / 2)) ? 1.0 : -1.0;
        K1[i * dim + i] = sqrt(p) * factor;
    }
    double complex *krausOperators[2];
    krausOperators[0] = K0;
    krausOperators[1] = K1;

    applyKrausChannelDensity(dm, 2, krausOperators);
    printf("Matrice densità dopo dephasing sul qubit 0 (p=0.5):\n");
    printDensityMatrix(dm);

    // Pulizia delle risorse allocate.
    freeDensityMatrix(dm);
    freeState(state);
    free(K0);
    free(K1);
}

