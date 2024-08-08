#include "quantum_sim.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <time.h>

QubitState* initializeState(int numQubits) {
    QubitState *state = (QubitState *)malloc(sizeof(QubitState));
    state->numQubits = numQubits;
    long long dim = 1LL << numQubits; // 2^numQubits
    state->amplitudes = (double complex *)calloc(dim, sizeof(double complex));
    state->amplitudes[0] = 1.0 + 0.0 * I; // |0>^N state
    return state;
}

void freeState(QubitState *state) {
    free(state->amplitudes);
    free(state);
}

void applySingleQubitGate(QubitState *state, int target, double complex gate[2][2]) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        if ((i >> target) & 1) {
            long long j = i ^ (1LL << target);
            double complex temp_i = state->amplitudes[i];
            double complex temp_j = state->amplitudes[j];
            state->amplitudes[i] = gate[0][0] * temp_j + gate[0][1] * temp_i;
            state->amplitudes[j] = gate[1][0] * temp_j + gate[1][1] * temp_i;
        }
    }
}

void applyHadamard(QubitState *state, int target) {
    double complex H[2][2] = {
        {1.0 / sqrt(2.0), 1.0 / sqrt(2.0)},
        {1.0 / sqrt(2.0), -1.0 / sqrt(2.0)}
    };
    applySingleQubitGate(state, target, H);
}

void applyX(QubitState *state, int target) {
    double complex X[2][2] = {
        {0, 1},
        {1, 0}
    };
    applySingleQubitGate(state, target, X);
}

void applyZ(QubitState *state, int target) {
    double complex Z[2][2] = {
        {1, 0},
        {0, -1}
    };
    applySingleQubitGate(state, target, Z);
}

void applyCNOT(QubitState *state, int control, int target) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        if ((i >> control) & 1) {
            long long j = i ^ (1LL << target);
            double complex temp = state->amplitudes[i];
            state->amplitudes[i] = state->amplitudes[j];
            state->amplitudes[j] = temp;
        }
    }
}

int* measure_all(QubitState *state) {
    long long dim = 1LL << state->numQubits;
    double *probabilities = (double *)malloc(dim * sizeof(double));
    if (probabilities == NULL) {
        printf("Errore nell'allocazione della memoria per le probabilità.\n");
        exit(1);
    }
    double totalProbability = 0.0;

    // Calcolare le probabilità di ciascuno stato base
    for (long long i = 0; i < dim; i++) {
        probabilities[i] = pow(cabs(state->amplitudes[i]), 2);
        totalProbability += probabilities[i];
    }

    // Normalizzare le probabilità
    for (long long i = 0; i < dim; i++) {
        probabilities[i] /= totalProbability;
    }

    // Generare un numero casuale per determinare il risultato della misura
    double randValue = (double)rand() / RAND_MAX;
    double cumulativeProbability = 0.0;
    int result = 0;
    for (long long i = 0; i < dim; i++) {
        cumulativeProbability += probabilities[i];
        if (randValue < cumulativeProbability) {
            result = i;
            break;
        }
    }

    // Collassare lo stato quantistico nel risultato della misura
    for (long long i = 0; i < dim; i++) {
        if (i == result) {
            state->amplitudes[i] = 1.0 + 0.0 * I;
        } else {
            state->amplitudes[i] = 0.0 + 0.0 * I;
        }
    }

    free(probabilities);

    // Creare un array per memorizzare i risultati della misura di ciascun qubit
    int *results = (int *)malloc(state->numQubits * sizeof(int));
    if (results == NULL) {
        printf("Errore nell'allocazione della memoria per i risultati.\n");
        exit(1);
    }
    for (int i = 0; i < state->numQubits; i++) {
        results[i] = (result >> i) & 1;
    }

    return results;
}
