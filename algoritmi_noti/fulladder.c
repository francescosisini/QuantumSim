#include <stdio.h>
#include "../src/quantum_sim.h"

void circuit(void) {
    int a, b, cin;

    // Chiedi all'utente di inserire i valori di A, B e C_in
    printf("Inserisci il valore dell'operando A (0 o 1): ");
    scanf("%d", &a);
    printf("Inserisci il valore dell'operando B (0 o 1): ");
    scanf("%d", &b);
    printf("Inserisci il valore del carry-in (C_in) (0 o 1): ");
    scanf("%d", &cin);
    

    // Crea uno stato quantistico a 5 qubit (C_in, A, B, Sum, C_out)
    QubitState* state = initializeState(5);

    // Inizializza lo stato del sistema a |00000>
    initializeStateTo(state, 0); 

    
    // Applica le porte X in base ai valori inseriti dall'utente
    if (cin == 1) applyX(state, 0);  // Imposta C_in a 1
    if (a == 1) applyX(state, 1);    // Imposta A a 1
    if (b == 1) applyX(state, 2);    // Imposta B a 1

    printf("\nStato iniziale\n");
    printState(state);
    

    printf("\nComputazione...\n");
    
    // Logica del full adder
    applyCNOT(state, 1, 3);       // Sum temporanea = A XOR B
    applyCNOT(state, 2, 3);       // Sum temporanea = A XOR B XOR C_in
    applyToffoli(state, 1, 2, 4); // Carry out = AB (Toffoli)
    applyCNOT(state, 0, 3);       // Sum finale = A XOR B XOR C_in
    applyToffoli(state, 0, 3, 4); // Carry out finale = C_in AND (A XOR B)

    // Stampa lo stato finale
    printf("\nStato finale\n");
    printState(state);

    // Misura i qubit per ottenere i risultati
    MeasurementResult sum_result = measure(state, 3);   // Somma (qubit 3)
    MeasurementResult cout_result = measure(state, 4);  // Carry out (qubit 4)

    // Stampa il risultato finale
    printf("Risultato della somma (Sum): %d\n", sum_result.result);
    printf("Carry out (C_out): %d\n", cout_result.result);

    // Libera la memoria
    freeState(state);
}
