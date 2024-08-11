#include "quantum_sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>


void circuit() {
    int numQubits = 3;
    int qb = 0;
    // Testare X con input |00>
    QubitState *state = initializeState(numQubits);
    long long dim = 1LL << state->numQubits;
    for(int i=0;i<dim;i++)
      {
	initializeStateTo(state, i);
	printf("Indice: %d \n", i);
	printState(state);
	printf("Applico X al qubit %d \n",qb);
	applyX(state,qb);
	printState(state);
      }

    printf("\n TEST CNOT \n");
    if(numQubits<2) exit(0);
    for(int i=0;i<dim;i++)
      {
	initializeStateTo(state, i);
	printf("Indice: %d \n", i);
	printState(state);
	printf("Applico CNOT: control 1, target %d \n",qb);
	applyCNOT(state,1,qb);
	printState(state);
      }
    
    }
