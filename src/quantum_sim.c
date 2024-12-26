/*
 * QuantumSim: A Quantum Circuit Simulator for C Programmers
 * Copyright (C) 2024 Francesco Sisini
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "quantum_sim.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <time.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/**
 * Inizializza lo stato quantistico a uno stato di base specifico.
 */
void initializeStateTo(QubitState *state, int index) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        state->amplitudes[i] = 0.0 + 0.0 * I;
    }
    state->amplitudes[index] = 1.0 + 0.0 * I;
}

/**
 * Stampa lo stato quantistico completo del sistema.
 */
void printState(QubitState *state) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        printf("Stato %lld: %f + %fi | ", i, creal(state->amplitudes[i]), cimag(state->amplitudes[i]));
        // Stampa la rappresentazione binaria dell'indice i (da MSB a LSB)
        for (int j = state->numQubits - 1; j >= 0; j--) {
            printf("%d", (i >> j) & 1);
        }
        printf("\n");
    }
}

/**
 * Inizializza lo stato quantistico con tutti i qubit nello stato |0>.
 */
QubitState* initializeState(int numQubits) {
    QubitState *state = (QubitState *)malloc(sizeof(QubitState));
    state->numQubits = numQubits;
    long long dim = 1LL << numQubits;
    state->amplitudes = (double complex *)calloc(dim, sizeof(double complex));

    // Imposta lo stato |0>^N
    state->amplitudes[0] = 1.0 + 0.0 * I;

    return state;
}

/**
 * Inizializza il qubit target nello stato |1> mantenendo lo stato degli altri qubit.
 */
void initializeSingleQubitToOne(QubitState* state, int target) {
    long long dim = 1LL << state->numQubits;

    for (long long i = 0; i < dim; i++) {
        if (((i >> target) & 1) == 0) {
            long long j = i ^ (1LL << target);
            state->amplitudes[j] = state->amplitudes[i];
            state->amplitudes[i] = 0.0 + 0.0 * I;
        }
    }
}

/**
 * Libera la memoria allocata per lo stato quantistico.
 */
void freeState(QubitState *state) {
    free(state->amplitudes);
    free(state);
}

/**
 * Applica un gate a un singolo qubit nello stato quantistico.
 */
void applySingleQubitGate(QubitState *state, int target, double complex gate[2][2]) {
    long long dim = 1LL << state->numQubits;
    double complex *new_amplitudes = (double complex *)malloc(dim * sizeof(double complex));

    for (long long i = 0; i < dim; i++) {
        int bitValue = (i >> target) & 1;
        long long j = i ^ (1LL << target);

        if (bitValue == 0) {
            new_amplitudes[i] = gate[0][0] * state->amplitudes[i] + gate[0][1] * state->amplitudes[j];
        } else {
            new_amplitudes[i] = gate[1][0] * state->amplitudes[j] + gate[1][1] * state->amplitudes[i];
        }
    }

    for (long long i = 0; i < dim; i++) {
        state->amplitudes[i] = new_amplitudes[i];
    }

    free(new_amplitudes);
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

void applyY(QubitState *state, int target) {
    double complex Y_GATE[2][2] = {
        {0, -I},
        {I, 0}
    };
    applySingleQubitGate(state, target, Y_GATE);
}

void applyZ(QubitState *state, int target) {
    double complex Z[2][2] = {
        {1, 0},
        {0, -1}
    };
    applySingleQubitGate(state, target, Z);
}

void applyT(QubitState *state, int target) {
    double complex T[2][2] = {
        {1, 0},
        {0, cexp(I * M_PI / 4.0)}
    };
    applySingleQubitGate(state, target, T);
}

void applyTdag(QubitState *state, int target) {
    double complex Tdag[2][2] = {
        {1, 0},
        {0, cexp(-I * M_PI / 4.0)}
    };
    applySingleQubitGate(state, target, Tdag);
}

void applyS(QubitState *state, int target) {
    double complex S[2][2] = {
        {1, 0},
        {0, I}
    };
    applySingleQubitGate(state, target, S);
}

/**
 * Applica un gate CNOT al sistema quantistico.
 */
void applyCNOT(QubitState *state, int control, int target) {
    long long dim = 1LL << state->numQubits;
    double complex *new_amplitudes = (double complex *)malloc(dim * sizeof(double complex));

    for (long long i = 0; i < dim; i++) {
        new_amplitudes[i] = state->amplitudes[i];
    }

    for (long long i = 0; i < dim; i++) {
        int control_bit = (i >> control) & 1;
        int target_bit = (i >> target) & 1;

        if (control_bit == 1) {
            long long j = i ^ (1LL << target);
            new_amplitudes[i] = state->amplitudes[j];
            new_amplitudes[j] = state->amplitudes[i];
        }
    }

    for (long long i = 0; i < dim; i++) {
        state->amplitudes[i] = new_amplitudes[i];
    }

    free(new_amplitudes);
}

/**
 * Applica un gate Controlled-Z (CZ) al sistema quantistico.
 */
void applyCZ(QubitState *state, int control, int target) {
    long long dim = 1LL << state->numQubits; // Dimensione dello spazio di Hilbert

    for (long long i = 0; i < dim; i++) {
        int control_bit = (i >> control) & 1; // Estrae il valore del qubit di controllo
        int target_bit = (i >> target) & 1;   // Estrae il valore del qubit target

        // Se il qubit di controllo è 1 e il target è 1, inverti il segno
        if (control_bit == 1 && target_bit == 1) {
            state->amplitudes[i] *= -1; // Inversione del segno dell'ampiezza
        }
    }
}


void applyCPhaseShift(QubitState *state, int control, int target, double complex phase) {
    long long dim = 1LL << state->numQubits;

    for (long long i = 0; i < dim; i++) {
        int control_bit = (i >> control) & 1;
        int target_bit = (i >> target) & 1;

        if (control_bit == 1 && target_bit == 1) {
            state->amplitudes[i] *= phase;
        }
    }
}

/**
 * Misura il valore di un qubit specificato nello stato quantistico e collassa il sistema.
 */
MeasurementResult measure(QubitState *state, int qubit) {
    long long dim = 1LL << state->numQubits;
    double prob0 = 0.0;

    for (long long i = 0; i < dim; i++) {
        if (((i >> qubit) & 1) == 0) {
            prob0 += pow(cabs(state->amplitudes[i]), 2);
        }
    }

    double prob1 = 1.0 - prob0;
    double rand_val = (double)rand() / RAND_MAX;
    int result = (rand_val < prob0) ? 0 : 1;

    double scale_factor = 0.0;
    if (result == 0) {
        scale_factor = 1.0 / sqrt(prob0);
        for (long long i = 0; i < dim; i++) {
            if (((i >> qubit) & 1) == 1) {
                state->amplitudes[i] = 0.0 + 0.0 * I;
            } else {
                state->amplitudes[i] *= scale_factor;
            }
        }
    } else {
        scale_factor = 1.0 / sqrt(prob1);
        for (long long i = 0; i < dim; i++) {
            if (((i >> qubit) & 1) == 0) {
                state->amplitudes[i] = 0.0 + 0.0 * I;
            } else {
                state->amplitudes[i] *= scale_factor;
            }
        }
    }

    MeasurementResult m_result;
    m_result.prob0 = prob0;
    m_result.prob1 = prob1;
    m_result.result = result;

    return m_result;
}

/**
 * Esegue una misura su tutti i qubit del sistema e collassa lo stato.
 */
int* measure_all(QubitState *state) {
    long long dim = 1LL << state->numQubits;
    double cumulativeProb = 0.0;
    double randNum = (double)rand() / RAND_MAX;
    long long collapse_index = -1;

    for (long long i = 0; i < dim; i++) {
        cumulativeProb += pow(cabs(state->amplitudes[i]), 2);
        if (randNum < cumulativeProb) {
            collapse_index = i;
            break;
        }
    }

    int* results = (int*)malloc(state->numQubits * sizeof(int));
    for (int i = 0; i < state->numQubits; i++) {
        results[i] = (collapse_index >> i) & 1;
    }

    for (long long j = 0; j < dim; j++) {
        if (j == collapse_index) {
            state->amplitudes[j] = 1.0 + 0.0 * I;
        } else {
            state->amplitudes[j] = 0.0 + 0.0 * I;
        }
    }

    return results;
}

QubitAmplitudes getQubitAmplitudes(QubitState* state, int target) {
    long long dim = 1LL << state->numQubits;

    QubitAmplitudes result;
    result.amplitude0 = 0.0 + 0.0 * I;
    result.amplitude1 = 0.0 + 0.0 * I;

    for (long long i = 0; i < dim; i++) {
        if (((i >> target) & 1) == 0) {
            result.amplitude0 += state->amplitudes[i];
        } else {
            result.amplitude1 += state->amplitudes[i];
        }
    }

    return result;
}

void printQubitAmplitudes(QubitAmplitudes amplitudes) {
    printf("Ampiezza di |0>: %f + %fi\n", creal(amplitudes.amplitude0), cimag(amplitudes.amplitude0));
    printf("Ampiezza di |1>: %f + %fi\n", creal(amplitudes.amplitude1), cimag(amplitudes.amplitude1));
}

//------------------ 3 qubit gates ---------------------------//

void applyToffoli(QubitState* state, int control1, int control2, int target) {
    applyHadamard(state, target);
    applyCNOT(state, control2, target);
    applyTdag(state, target);
    applyCNOT(state, control1, target);
    applyT(state, target);
    applyCNOT(state, control2, target);
    applyTdag(state, target);
    applyCNOT(state, control1, target);
    applyT(state, target);
    applyHadamard(state, target);
    //---
    applyT(state, control2);
    applyCNOT(state, control1, control2);
    applyT(state, control1);
    applyTdag(state, control2);
    applyCNOT(state, control1, control2);
}

void applyFredkin(QubitState* state, int control, int target1, int target2) {
    applyToffoli(state, control, target1, target2);
    applyCNOT(state, target1, target2);
    applyToffoli(state, control, target1, target2);
    applyCNOT(state, target1, target2);
    applyToffoli(state, control, target1, target2);
    applyCNOT(state, target1, target2);
}

void applyCCZ(QubitState* state, int control1, int control2, int target) {
    applyHadamard(state, target);
    applyToffoli(state, control1, control2, target);
    applyHadamard(state, target);
    applyZ(state, target);
    applyToffoli(state, control1, control2, target);
    applyHadamard(state, target);
}

void applyCCY(QubitState* state, int control1, int control2, int target) {
    applyToffoli(state, control1, control2, target);
    applyY(state, target);
    applyToffoli(state, control1, control2, target);
}

void applyCCPhase(QubitState* state, int control1, int control2, int target, double phase) {
    applyToffoli(state, control1, control2, target);
    applyPhase(state, target, phase);
    applyToffoli(state, control1, control2, target);
}

void applyPhase(QubitState* state, int qubit, double phase) {
    long long dim = 1LL << state->numQubits;

    for (long long i = 0; i < dim; i++) {
        if (((i >> qubit) & 1) == 1) {
            state->amplitudes[i] *= cexp(I * phase);
        }
    }
}
