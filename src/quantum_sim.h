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
