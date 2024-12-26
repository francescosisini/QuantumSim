#include "quantum_sim.h"
#include <stdio.h>
#include <math.h>

#define M_PI acos(-1.0)

int circuit(void) {
    // Inizializza lo stato quantistico con 1 qubit
    QubitState* state = initializeState(1);

    // Stato iniziale |0>
    initializeStateTo(state, 0);
    printf("Stato iniziale:\n");
    printState(state);

    // Rotazione attorno all'asse Y
    double theta = M_PI / 4; // Angolo di rotazione (45 gradi)
    double complex rotation[2][2] = {
        {cos(theta / 2), -sin(theta / 2)},
        {sin(theta / 2), cos(theta / 2)}
    };
    applySingleQubitGate(state, 0, rotation);
    printf("Stato dopo la rotazione:\n");
    printState(state);

    // Misurazione
    MeasurementResult result = measure(state, 0);
    printf("Risultato della misurazione: %d\n", result.result);

    // Libera la memoria allocata
    freeState(state);
    return 0;
}
