// quantum_density.c

#include "quantum_density.h"
#include "quantum_sim.h"  // Per QubitState, etc.
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <math.h>

/* 
 * Funzione di supporto: moltiplicazione di due matrici complesse quadrate (dimensione dim x dim).
 * Le matrici A, B e C sono memorizzate in ordine row-major.
 */
static void multiplyMatrices(const double complex *A, const double complex *B, double complex *C, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            double complex sum = 0;
            for (int k = 0; k < dim; k++) {
                sum += A[i * dim + k] * B[k * dim + j];
            }
            C[i * dim + j] = sum;
        }
    }
}

/* 
 * Funzione di supporto: calcola il coniugato trasposto (dagger) di una matrice U di dimensione dim x dim.
 * Il risultato viene scritto in U_dag (già allocato con dim*dim elementi).
 */
static void conjugateTranspose(const double complex *U, double complex *U_dag, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            U_dag[j * dim + i] = conj(U[i * dim + j]);
        }
    }
}

/* Inizializza una matrice densità per "numQubits" allocando la struttura e la matrice a zero. */
DensityMatrix* initializeDensityMatrix(int numQubits) {
    DensityMatrix *dm = malloc(sizeof(DensityMatrix));
    if (!dm) {
        perror("Errore allocazione DensityMatrix");
        exit(1);
    }
    dm->numQubits = numQubits;
    int dim = 1 << numQubits;
    dm->matrix = calloc(dim * dim, sizeof(double complex));
    if (!dm->matrix) {
        perror("Errore allocazione matrice densità");
        free(dm);
        exit(1);
    }
    return dm;
}

/* Libera la memoria associata a una DensityMatrix. */
void freeDensityMatrix(DensityMatrix *dm) {
    if (dm) {
        free(dm->matrix);
        free(dm);
    }
}

/* Stampa la matrice densità in formato testo. */
void printDensityMatrix(DensityMatrix *dm) {
    if (!dm || !dm->matrix) return;
    int dim = 1 << dm->numQubits;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            double complex val = dm->matrix[i * dim + j];
            printf("(%g %+gi) ", creal(val), cimag(val));
        }
        printf("\n");
    }
}

/* Converte uno stato puro (rappresentato da QubitState) nella corrispondente matrice densità: 
   \rho = |psi><psi|. */
DensityMatrix* pureStateToDensityMatrix(QubitState *state) {
    if (!state) return NULL;
    DensityMatrix *dm = initializeDensityMatrix(state->numQubits);
    int dim = 1 << state->numQubits;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            dm->matrix[i * dim + j] = state->amplitudes[i] * conj(state->amplitudes[j]);
        }
    }
    return dm;
}

/* Applica una trasformazione unitaria completa U (di dimensione 2^(numQubits) x 2^(numQubits)) alla matrice densità:
   \rho -> U \rho U^\dagger. */
void applyUnitaryDensity(DensityMatrix *dm, double complex *U) {
    int dim = 1 << dm->numQubits;
    double complex *temp = calloc(dim * dim, sizeof(double complex));
    double complex *U_dag = calloc(dim * dim, sizeof(double complex));
    if (!temp || !U_dag) {
        perror("Errore allocazione in applyUnitaryDensity");
        exit(1);
    }
    // Calcola U * rho
    multiplyMatrices(U, dm->matrix, temp, dim);
    // Calcola U^\dagger
    conjugateTranspose(U, U_dag, dim);
    // Calcola (U * rho) * U^\dagger
    double complex *newMatrix = calloc(dim * dim, sizeof(double complex));
    if (!newMatrix) {
        perror("Errore allocazione newMatrix in applyUnitaryDensity");
        exit(1);
    }
    multiplyMatrices(temp, U_dag, newMatrix, dim);
    // Copia il risultato in dm->matrix
    for (int i = 0; i < dim * dim; i++) {
        dm->matrix[i] = newMatrix[i];
    }
    free(temp);
    free(U_dag);
    free(newMatrix);
}

/* Applica un gate a 1 qubit (matrice 2x2) al qubit 'target' della matrice densità.
   Espande il gate alla dimensione completa del sistema e lo applica tramite
   \rho -> U \rho U^\dagger. */
void applySingleQubitGateDensity(DensityMatrix *dm, int target, double complex gate[2][2]) {
    int n = dm->numQubits;
    int dim = 1 << n;
    double complex *U = calloc(dim * dim, sizeof(double complex));
    if (!U) {
        perror("Errore allocazione U in applySingleQubitGateDensity");
        exit(1);
    }
    // Costruzione dell'operatore completo U.
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int valid = 1;
            int bit_i = (i >> target) & 1;
            int bit_j = (j >> target) & 1;
            for (int k = 0; k < n; k++) {
                if (k == target) continue;
                int bi = (i >> k) & 1;
                int bj = (j >> k) & 1;
                if (bi != bj) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                U[i * dim + j] = gate[bit_i][bit_j];
            }
        }
    }
    applyUnitaryDensity(dm, U);
    free(U);
}

/* Applica un canale quantistico (definito da numOperators operatori di Kraus)
   alla matrice densità:
   \rho -> \sum_i K_i \rho K_i^\dagger.
   "krausOperators" è un array di puntatori a matrici, ognuna di dimensione 2^(numQubits) x 2^(numQubits). */
void applyKrausChannelDensity(DensityMatrix *dm, int numOperators, double complex **krausOperators) {
    int dim = 1 << dm->numQubits;
    double complex *newRho = calloc(dim * dim, sizeof(double complex));
    if (!newRho) {
        perror("Errore allocazione newRho in applyKrausChannelDensity");
        exit(1);
    }
    double complex *temp = calloc(dim * dim, sizeof(double complex));
    double complex *temp2 = calloc(dim * dim, sizeof(double complex));
    double complex *K_dag = calloc(dim * dim, sizeof(double complex));
    if (!temp || !temp2 || !K_dag) {
        perror("Errore allocazione in applyKrausChannelDensity");
        exit(1);
    }
    for (int op = 0; op < numOperators; op++) {
        double complex *K = krausOperators[op];
        // Calcola temp = K * rho
        multiplyMatrices(K, dm->matrix, temp, dim);
        // Calcola K_dag (coniugato trasposto di K)
        conjugateTranspose(K, K_dag, dim);
        // Calcola temp2 = (K * rho) * K_dag
        multiplyMatrices(temp, K_dag, temp2, dim);
        // Aggiunge temp2 a newRho
        for (int i = 0; i < dim * dim; i++) {
            newRho[i] += temp2[i];
        }
    }
    // Aggiorna la matrice densità
    for (int i = 0; i < dim * dim; i++) {
        dm->matrix[i] = newRho[i];
    }
    free(newRho);
    free(temp);
    free(temp2);
    free(K_dag);
}
