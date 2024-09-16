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

#ifndef QUANTUM_SIM_H
#define QUANTUM_SIM_H

#include <complex.h>
#include <math.h>

typedef struct {
    int numQubits;
    double complex *amplitudes;
} QubitState;

typedef struct {
    double prob0;  // Probabilità di misurare 0
    double prob1;  // Probabilità di misurare 1
    int result;    // Risultato della misurazione (0 o 1)
} MeasurementResult;


typedef struct {
    double complex amplitude0;
    double complex amplitude1;
} QubitAmplitudes;

QubitState* initializeState(int numQubits);
void initializeStateTo(QubitState *state, int index);
void initializeSingleQubitToOne(QubitState *state, int targetQubit);
void freeState(QubitState *state);
void printState(QubitState *state);
void printStateIgnoringQubits(QubitState *state, int *ignoreQubits, int numIgnoreQubits);
void applyHadamard(QubitState *state, int target);
void applyX(QubitState *state, int target);
void applyZ(QubitState *state, int target);
void applyT(QubitState *state, int target);
void applyTdag(QubitState *state, int target);
void applyS(QubitState *state, int target);
void applyCNOT(QubitState *state, int control, int target);
void applyCPhaseShift(QubitState *state, int control, int target, double complex phase);
void applyToffoli(QubitState* state, int control1, int control2, int target);
void applySingleQubitGate(QubitState *state, int target, double complex gate[2][2]);
int* measure_all(QubitState *state);
MeasurementResult measure(QubitState *state, int qubit);
QubitAmplitudes getQubitAmplitudes(QubitState* state, int target);
void printQubitAmplitudes(QubitAmplitudes amplitudes);
#endif // QUANTUM_SIM_H
