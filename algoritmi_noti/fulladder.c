#include <stdio.h>
#include "../src/quantum_sim.h"

void circuit(void) {
    int a, b, cin;

    // Chiedi all'utente di inserire i valori di A, B e C_in
    printf("Somma binaria di due bit A e B con riporto\n\n ");
    printf("Inserisci il valore dell'operando A (0 o 1): ");
    scanf("%d", &a);
    printf("Inserisci il valore dell'operando B (0 o 1): ");
    scanf("%d", &b);
    printf("Inserisci il valore del carry-in (C_in) (0 o 1): ");
    scanf("%d", &cin);
    

    // Crea uno stato quantistico a 5 qubit (A, B, C_in, C_out)
    QubitState* state = initializeState(4);

    // Inizializza lo stato del sistema a |0000>
    initializeStateTo(state, 0); 

    
    // Applica le porte X in base ai valori inseriti dall'utente
    if (a == 1) applyX(state, 0);    // Imposta A a 1
    if (b == 1) applyX(state, 1);    // Imposta B a 1
    if (cin == 1) applyX(state, 2);  // Imposta C_in a 1
    
    printf("\nStato iniziale\n");
    printState(state);
    
    printf("\nComputazione...\n");
    
    // Logica del full adder
    applyToffoli(state,0,1,3);
    applyCNOT(state,0,1);
    applyToffoli(state,1,2,3);
    applyCNOT(state,1,2);
    applyCNOT(state,0,1);
    
    // Stampa lo stato finale
    printf("\nStato finale\n");
    printState(state);

    // Misura i qubit per ottenere i risultati
    MeasurementResult sum_result = measure(state, 2);   // Somma (qubit 2)
    MeasurementResult cout_result = measure(state, 3);  // Carry out (qubit 3)

    // Stampa il risultato finale
    printf("Risultato della somma (Sum): %d\n", sum_result.result);
    printf("Carry out (C_out): %d\n", cout_result.result);

    // Libera la memoria
    freeState(state);
}
