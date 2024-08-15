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

typedef struct {
    int numQubits;
    double complex *amplitudes;
} QubitState;

QubitState* initializeState(int numQubits);
void initializeStateTo(QubitState *state, int index);
void freeState(QubitState *state);
void printState(QubitState *state);
void applyHadamard(QubitState *state, int target);
void applyX(QubitState *state, int target);
void applyZ(QubitState *state, int target);
void applyCNOT(QubitState *state, int control, int target);
int* measure_all(QubitState *state);
int measure(QubitState *state, int qubit);  
#endif // QUANTUM_SIM_H
