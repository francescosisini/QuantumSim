#include "quantum_sim.h"
#include <stdlib.h>
#include <time.h>

void circuit();

int main() {
    srand(time(NULL)); // Inizializza il generatore di numeri casuali
    circuit();
    return 0;
}
