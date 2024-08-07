#include "quantum_sim.h"
#include <stdlib.h>
#include <math.h>
#include <complex.h>

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

void applyHadamard(QubitState *state, int target) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        if ((i >> target) & 1) {
            long long j = i ^ (1LL << target);
            double complex temp = state->amplitudes[i];
            state->amplitudes[i] = (state->amplitudes[j] + state->amplitudes[i]) / sqrt(2.0);
            state->amplitudes[j] = (state->amplitudes[j] - temp) / sqrt(2.0);
        }
    }
}

void applyPhase(QubitState *state, int target) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        if ((i >> target) & 1) {
            state->amplitudes[i] *= I; // Multiply by i (complex number)
        }
    }
}

void applyTGate(QubitState *state, int target) {
    double complex t = cexp(I * M_PI / 4.0);
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        if ((i >> target) & 1) {
            state->amplitudes[i] *= t; // Multiply by exp(i * pi / 4)
        }
    }
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

void applyX(QubitState *state, int target) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        if ((i >> target) & 1) {
            long long j = i ^ (1LL << target);
            double complex temp = state->amplitudes[i];
            state->amplitudes[i] = state->amplitudes[j];
            state->amplitudes[j] = temp;
        }
    }
}

void applyZ(QubitState *state, int target) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        if ((i >> target) & 1) {
            state->amplitudes[i] *= -1.0; // Multiply by -1
        }
    }
}

void applyGroverDiffusion(QubitState *state) {
    long long dim = 1LL << state->numQubits;
    double complex average = 0.0;
    for (long long i = 0; i < dim; i++) {
        average += state->amplitudes[i];
    }
    average /= dim;
    for (long long i = 0; i < dim; i++) {
        state->amplitudes[i] = 2.0 * average - state->amplitudes[i];
    }
}
