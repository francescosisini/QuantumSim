
#include "quantum_sim.h"
#include <stdio.h>


void grover_algorithm(QubitState *state) {
  //-passo 1
  applyX(state,1);
  applyX(state,2);
  applyX(state,3);
  applyHadamard(state,4);
  applyHadamard(state,5);
  applyHadamard(state,6);
  applyX(state,7);
  //-passo 2
  applyCNOT(state,2,4);
  applyHadamard(state,7);
  //-passo 3
  applyTdag(state,4);
  //-passo 4
  applyCNOT(state,1,4);
  //-passo 5
  applyT(state,4);
  //-passo 6
  applyCNOT(state,2,4);
  //-passo 7
  applyT(state,2);
  applyTdag(state,4);
  //-passo 8
  applyCNOT(state,1,4);
  //-passo 9
  applyCNOT(state,1,2);
  applyT(state,4);
  //-passo 10
  applyT(state,1);
  applyTdag(state,2);
  applyHadamard(state,4);
  //-passo 11
  applyCNOT(state,1,2);
  applyCNOT(state,4,5);
  //-passo 12
  applyX(state,1);
  applyX(state,2);
  applyTdag(state,5);
  //-passo 13
  applyCNOT(state,3,5);
  //-passo 14
  applyT(state,5);
  //-passo 15
  applyCNOT(state,4,5);
  //-passo 16
  applyT(state,4);
  applyTdag(state,5);
  //-passo 17
  applyCNOT(state,3,5);
  //-passo 18
  applyCNOT(state,3,4);
  applyT(state,5);
  //-passo 19
  applyT(state,3);
  applyTdag(state,4);
  applyHadamard(state,5);
  //-passo 20
  applyCNOT(state,3,4);
  applyCNOT(state,5,6);
  //-passo 21
  applyX(state,3);
  applyTdag(state,6);
  //-passo 22
  applyCNOT(state,0,6);
  //-passo 23
  applyT(state,6);
  //-passo 24
  applyCNOT(state,5,6);
  //-passo 35
  applyT(state,5);
  applyTdag(state,6);
  //-passo 36
  applyCNOT(state,0,6);
  //-passo 37
  applyCNOT(state,0,5);
  applyT(state,6);
  //-passo 38
  applyT(state,0);
  applyTdag(state,5);
  applyHadamard(state,6);
  //-passo 39
  applyCNOT(state,0,5);
  applyCNOT(state,6,7);
  
  

  
  

}

void circuit() {

  QubitState* state =  initializeState(8);

  grover_algorithm(state);
   QubitAmplitudes m_b = getQubitAmplitudes(state,7);

  state =  initializeState(8);
  applyX(state,0);
  grover_algorithm(state);
  QubitAmplitudes m_a = getQubitAmplitudes(state,7);
  printQubitAmplitudes(m_b);
  printf("\n0->|1>\n");
  printQubitAmplitudes(m_a);
 

  
  
  freeState(state);
    
}
