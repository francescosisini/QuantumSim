#include "quantum_sim.h"
#include <stdio.h>

// Dichiarazione delle quattro ipotesi dell'oracolo come funzioni
void oracle_constant_zero(QubitState *state) {
  
    // Oracle che implementa f(x) = 0
    // Non fa nulla allo stato
   
}

void oracle_constant_one(QubitState *state) {
    // Oracle che implementa f(x) = 1
    applyX(state, 1); // Applica X al secondo qubit
   
}

void oracle_balanced_identity(QubitState *state) {
    // Oracle che implementa f(x) = x (Identità)
   
  applyCNOT(state, 0, 1); // Applica CNOT con il primo qubit come controllo e il secondo come target
  
}

void oracle_balanced_not(QubitState *state) {
    // Oracle che implementa f(x) = NOT(x)
   applyX(state, 0); // Applica X al primo qubit
    applyCNOT(state, 0, 1); // Applica CNOT con il primo qubit come controllo e il secondo come target
  
   
}

void deutsch_algorithm(QubitState *state, void (*oracle)(QubitState *)) {
    printf("Stato iniziale:\n");
    printState(state);

    applyX(state, 1); // Applica X al secondo qubit
    printf("Dopo X sul secondo qubit:\n");
    printState(state);

    applyHadamard(state, 0); // Applica Hadamard al primo qubit
    applyHadamard(state, 1); // Applica Hadamard al secondo qubit
    printf("Dopo Hadamard su entrambi i qubit:\n");
    printState(state);

    // Applica l'oracolo
    printf("Prima dell'applicazione dell'oracolo:\n");
    printState(state);
    oracle(state);
    printf("Dopo l'applicazione dell'oracolo:\n");
    printState(state);

    // Applica Hadamard al primo qubit
    applyHadamard(state, 0);
    printf("Dopo Hadamard sul primo qubit:\n");
    printState(state);

    // Misura il primo qubit per determinare il tipo di funzione (costante o bilanciata)
    int result = measure(state, 0);

    // Stampa il risultato
    if (result <= .001) {
      printf("La funzione è costante %d.\n",result);
    } else {
      printf("La funzione è bilanciata %d.\n",result);
    }
}


// Funzione principale del circuito
void circuit() {
    int numQubits = 2;
    QubitState *state = initializeState(numQubits);

    printf("Verifica dell'oracolo costante f(x) = 0:\n");
    
    deutsch_algorithm(state, oracle_constant_zero);
    
    freeState(state);
    state = initializeState(numQubits);
    printf("\nVerifica dell'oracolo costante f(x) = 1:\n");
    
    deutsch_algorithm(state, oracle_constant_one);

    freeState(state);
    state = initializeState(numQubits);
    printf("\nVerifica dell'oracolo bilanciato f(x) = x:\n");
    
    deutsch_algorithm(state, oracle_balanced_identity);

    freeState(state);
    state = initializeState(numQubits);
    printf("\nVerifica dell'oracolo bilanciato f(x) = NOT(x):\n");
    
    deutsch_algorithm(state, oracle_balanced_not);

    // Libera la memoria allocata per lo stato
    freeState(state);
}

