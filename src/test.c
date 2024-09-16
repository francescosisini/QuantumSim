
#include "quantum_sim.h"
#include <stdio.h>

void circuit() {

  QubitState* state =  initializeState(2);
  applyX(state,1);
  QubitAmplitudes x_b = getQubitAmplitudes(state,0);
  applyHadamard(state,1);
  QubitAmplitudes h_b = getQubitAmplitudes(state,0);
  
  
  QubitAmplitudes m_b = getQubitAmplitudes(state,0);

  state =  initializeState(2);
  applyX(state,0);
 
  QubitAmplitudes m_a = getQubitAmplitudes(state,0);
  printQubitAmplitudes(x_b);
  printQubitAmplitudes(h_b);
  printQubitAmplitudes(m_b);
  printf("\n0->|1>\n");
  printQubitAmplitudes(m_a);
   
  freeState(state);
 }
