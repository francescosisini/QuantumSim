#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "../src/quantum_sim.h"
#include "../src/quantum_density.h"
#include "../src/noise_channels.h"  // Assicurati che questo header sia disponibile

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void circuit(void) {
    // 1. Inizializza uno stato puro a 2 qubit (|00>)
    QubitState *state = initializeState(2);
    // Lo stato iniziale |00> è già impostato dalla funzione initializeState.
    
    // 2. Applica Hadamard sul qubit 0 per generare coerenza
    // In questo modo lo stato diventa (|00> + |10>)/sqrt(2)
    applyHadamard(state, 0);
    printf("Stato puro dopo Hadamard su q0:\n");
    printState(state);

    // 3. Converte lo stato puro in matrice densità
    DensityMatrix *dm_orig = pureStateToDensityMatrix(state);
    printf("\nMatrice densità iniziale (dallo stato puro):\n");
    printDensityMatrix(dm_orig);

    // 4. Crea tre copie della matrice densità per applicare differenti canali di rumore.
    int n = dm_orig->numQubits;
    int dim = 1 << n;
    DensityMatrix *dm_dephasing = initializeDensityMatrix(n);
    DensityMatrix *dm_ampDamp   = initializeDensityMatrix(n);
    DensityMatrix *dm_depol     = initializeDensityMatrix(n);
    for (int i = 0; i < dim * dim; i++) {
        dm_dephasing->matrix[i] = dm_orig->matrix[i];
        dm_ampDamp->matrix[i]   = dm_orig->matrix[i];
        dm_depol->matrix[i]     = dm_orig->matrix[i];
    }

    // 5. Applica il canale di dephasing sul qubit 0 con p = 0.3.
    applyDephasing(dm_dephasing, 0, 0.3);
    printf("\nMatrice densità dopo Dephasing (p = 0.3) su q0:\n");
    printDensityMatrix(dm_dephasing);

    // 6. Applica il canale di amplitude damping sul qubit 0 con gamma = 0.3.
    applyAmplitudeDamping(dm_ampDamp, 0, 0.3);
    printf("\nMatrice densità dopo Amplitude Damping (gamma = 0.3) su q0:\n");
    printDensityMatrix(dm_ampDamp);

    // 7. Applica il canale depolarizzante sul qubit 0 con p = 0.3.
    applyDepolarizing(dm_depol, 0, 0.3);
    printf("\nMatrice densità dopo Depolarizing (p = 0.3) su q0:\n");
    printDensityMatrix(dm_depol);

    // Pulizia delle risorse allocate
    freeDensityMatrix(dm_orig);
    freeDensityMatrix(dm_dephasing);
    freeDensityMatrix(dm_ampDamp);
    freeDensityMatrix(dm_depol);
    freeState(state);
}
