#ifndef NOISE_CHANNELS_H
#define NOISE_CHANNELS_H

#include "quantum_density.h"

// Wrapper per il canale di dephasing su un singolo qubit.
// p rappresenta la probabilità di errore di dephasing.
void applyDephasing(DensityMatrix *dm, int targetQubit, double p);

// Wrapper per l'ampiezza damping su un singolo qubit.
// gamma rappresenta la probabilità di perdita di eccitazione.
void applyAmplitudeDamping(DensityMatrix *dm, int targetQubit, double gamma);

// Wrapper per il canale depolarizzante su un singolo qubit.
// p rappresenta la probabilità complessiva di errore.
void applyDepolarizing(DensityMatrix *dm, int targetQubit, double p);

#endif // NOISE_CHANNELS_H
