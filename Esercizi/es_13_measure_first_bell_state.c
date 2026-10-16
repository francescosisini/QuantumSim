#include <stdio.h>
#include "../src/quantum_sim.h"

int circuit(void) {

  const int num_runs = 10;
    for (int i = 0; i < num_runs; i++) {
        QubitState* state2 = initializeState(2);
        MeasurementResult result;
        initializeStateTo(state2, 0);
        applyHadamard(state2, 1);
        applyCNOT(state2, 1, 0);

        MeasurementResult q0 = measure(state2, 0);
        MeasurementResult q1 = measure(state2, 1);
        int res_q0 = q0.result;
        int res_q1 = q1.result;

        printf("Misura %2d: q0 = %d, q1 = %d => %s\n",
               i+1, res_q0, res_q1, (res_q0 == res_q1) ? "correlati" : "non correlati");

        freeState(state2);
    }
    return 0;
}

