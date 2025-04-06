// noise_channels.c

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "quantum_density.h"
#include "noise_channels.h"

// Funzione helper: estende un operatore 2x2 a un sistema di n qubit
// in modo che agisca come "op" sul qubit target e come identità sugli altri.
void extendKrausOperator(int n, int target, double complex op[2][2], double complex *K_ext) {
    int dim = 1 << n;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int valid = 1;
            // Per ogni qubit diverso dal target, i e j devono avere lo stesso bit
            for (int k = 0; k < n; k++) {
                if (k == target) continue;
                int bit_i = (i >> k) & 1;
                int bit_j = (j >> k) & 1;
                if (bit_i != bit_j) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                int i_bit = (i >> target) & 1;
                int j_bit = (j >> target) & 1;
                K_ext[i * dim + j] = op[i_bit][j_bit];
            } else {
                K_ext[i * dim + j] = 0;
            }
        }
    }
}

// Wrapper per il dephasing su un singolo qubit.
// p rappresenta la probabilità di errore di dephasing.
void applyDephasing(DensityMatrix *dm, int targetQubit, double p) {
    int n = dm->numQubits;
    int dim = 1 << n;
    // Operatori di Kraus per il dephasing su un singolo qubit:
    // K0 = sqrt(1-p)*I,  K1 = sqrt(p)*Z  con Z = diag(1, -1)
    double complex K0_single[2][2] = { {sqrt(1 - p), 0}, {0, sqrt(1 - p)} };
    double complex K1_single[2][2] = { {sqrt(p), 0}, {0, -sqrt(p)} };

    double complex *K0 = calloc(dim * dim, sizeof(double complex));
    double complex *K1 = calloc(dim * dim, sizeof(double complex));
    if (!K0 || !K1) {
        perror("Errore allocazione operatori Kraus in applyDephasing");
        exit(1);
    }
    extendKrausOperator(n, targetQubit, K0_single, K0);
    extendKrausOperator(n, targetQubit, K1_single, K1);

    double complex *krausOps[2];
    krausOps[0] = K0;
    krausOps[1] = K1;
    applyKrausChannelDensity(dm, 2, krausOps);

    free(K0);
    free(K1);
}

// Wrapper per l'ampiezza damping su un singolo qubit.
// gamma rappresenta la probabilità di perdita di eccitazione (legata a T1).
void applyAmplitudeDamping(DensityMatrix *dm, int targetQubit, double gamma) {
    int n = dm->numQubits;
    int dim = 1 << n;
    // Operatori di Kraus per l'ampiezza damping:
    // K0 = [[1,0],[0,sqrt(1-gamma)]],  K1 = [[0,sqrt(gamma)],[0,0]]
    double complex K0_single[2][2] = { {1, 0}, {0, sqrt(1 - gamma)} };
    double complex K1_single[2][2] = { {0, sqrt(gamma)}, {0, 0} };

    double complex *K0 = calloc(dim * dim, sizeof(double complex));
    double complex *K1 = calloc(dim * dim, sizeof(double complex));
    if (!K0 || !K1) {
        perror("Errore allocazione operatori Kraus in applyAmplitudeDamping");
        exit(1);
    }
    extendKrausOperator(n, targetQubit, K0_single, K0);
    extendKrausOperator(n, targetQubit, K1_single, K1);

    double complex *krausOps[2];
    krausOps[0] = K0;
    krausOps[1] = K1;
    applyKrausChannelDensity(dm, 2, krausOps);

    free(K0);
    free(K1);
}

// Wrapper per il canale depolarizzante su un singolo qubit.
// p rappresenta la probabilità complessiva di errore.
void applyDepolarizing(DensityMatrix *dm, int targetQubit, double p) {
    int n = dm->numQubits;
    int dim = 1 << n;
    // Operatori di Kraus per il canale depolarizzante:
    // K0 = sqrt(1 - 3p/4)*I, K1 = sqrt(p/4)*X, K2 = sqrt(p/4)*Y, K3 = sqrt(p/4)*Z.
    double complex K0_single[2][2] = { {sqrt(1 - 3*p/4), 0}, {0, sqrt(1 - 3*p/4)} };
    // Pauli X = [[0,1],[1,0]]
    double complex K1_single[2][2] = { {0, sqrt(p/4)}, {sqrt(p/4), 0} };
    // Pauli Y = [[0,-i],[i,0]]
    double complex K2_single[2][2] = { {0, -I*sqrt(p/4)}, {I*sqrt(p/4), 0} };
    // Pauli Z = [[1,0],[0,-1]]
    double complex K3_single[2][2] = { {sqrt(p/4), 0}, {0, -sqrt(p/4)} };

    double complex *K0_ext = calloc(dim * dim, sizeof(double complex));
    double complex *K1_ext = calloc(dim * dim, sizeof(double complex));
    double complex *K2_ext = calloc(dim * dim, sizeof(double complex));
    double complex *K3_ext = calloc(dim * dim, sizeof(double complex));
    if (!K0_ext || !K1_ext || !K2_ext || !K3_ext) {
        perror("Errore allocazione operatori Kraus in applyDepolarizing");
        exit(1);
    }
    extendKrausOperator(n, targetQubit, K0_single, K0_ext);
    extendKrausOperator(n, targetQubit, K1_single, K1_ext);
    extendKrausOperator(n, targetQubit, K2_single, K2_ext);
    extendKrausOperator(n, targetQubit, K3_single, K3_ext);

    double complex *krausOps[4];
    krausOps[0] = K0_ext;
    krausOps[1] = K1_ext;
    krausOps[2] = K2_ext;
    krausOps[3] = K3_ext;
    applyKrausChannelDensity(dm, 4, krausOps);

    free(K0_ext);
    free(K1_ext);
    free(K2_ext);
    free(K3_ext);
}
