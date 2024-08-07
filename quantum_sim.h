#ifndef QUANTUM_SIM_H
#define QUANTUM_SIM_H

#include <complex.h>

typedef struct {
    int numQubits;
    double complex *amplitudes;
} QubitState;

QubitState* initializeState(int numQubits);
void freeState(QubitState *state);

void applyHadamard(QubitState *state, int target);
void applyPhase(QubitState *state, int target);
void applyTGate(QubitState *state, int target);
void applyCNOT(QubitState *state, int control, int target);
void applyX(QubitState *state, int target);
void applyZ(QubitState *state, int target);
void applyGroverDiffusion(QubitState *state);

#endif // QUANTUM_SIM_H
