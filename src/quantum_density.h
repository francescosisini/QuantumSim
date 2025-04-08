#ifndef QUANTUM_DENSITY_H
#define QUANTUM_DENSITY_H

#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "quantum_sim.h"  // Include le definizioni per QubitState, etc.

// Struttura per rappresentare la matrice densità.
// La matrice è memorizzata in ordine "row-major" ed ha dimensione 2^(numQubits) x 2^(numQubits)
typedef struct {
    int numQubits;
    double complex *matrix;
} DensityMatrix;

// Inizializza una matrice densità per 'numQubits' (allocazione e inizializzazione a zero)
DensityMatrix* initializeDensityMatrix(int numQubits);

// Libera la memoria associata a una matrice densità
void freeDensityMatrix(DensityMatrix *dm);

// Stampa a video la matrice densità
void printDensityMatrix(DensityMatrix *dm);

// Converte uno stato puro (QubitState) nella corrispondente matrice densità
// (cioè, \rho = |psi><psi|)
DensityMatrix* pureStateToDensityMatrix(QubitState *state);

// Applica una trasformazione unitaria U (matrice di dimensione 2^(numQubits) x 2^(numQubits))
// alla matrice densità: \rho -> U \rho U^\dagger
void applyUnitaryDensity(DensityMatrix *dm, double complex *U);

// Applica un gate a 1-qubit (matrice 2x2) al qubit 'target' della matrice densità.
// Questa funzione dovrà espandere il gate alla dimensione del sistema (tramite prodotto tensoriale).
void applySingleQubitGateDensity(DensityMatrix *dm, int target, double complex gate[2][2]);

// Applica un canale quantistico (modello tramite operatori di Kraus)
// alla matrice densità: \rho -> \sum_i K_i \rho K_i^\dagger.
// 'numOperators' è il numero di operatori, e 'krausOperators' è un array di matrici (ognuna di dimensione 2^(numQubits) x 2^(numQubits)).
void applyKrausChannelDensity(DensityMatrix *dm, int numOperators, double complex **krausOperators);

#endif // QUANTUM_DENSITY_H
