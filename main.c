#include <stdio.h>
#include "quantum_sim.h"

void circuit(QubitState *state);

int main() {
    int numQubits = 2; // Utilizziamo 2 qubits per il circuito di Grover
    QubitState *state = initializeState(numQubits);
    
    circuit(state);
    
    // Visualizzare lo stato finale
    long long dim = 1LL << numQubits;
    for (long long i = 0; i < dim; i++) {
        printf("State[%lld] = %.2f + %.2fi\n", i, creal(state->amplitudes[i]), cimag(state->amplitudes[i]));
    }
    
    freeState(state);
    return 0;
}
