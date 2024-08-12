#include "quantum_sim.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <time.h>

/**
 * Inizializza lo stato quantistico a uno stato di base specifico.
 *
 * Questa funzione prende in input un puntatore a una struttura `QubitState`, che rappresenta
 * lo stato di un sistema quantistico, e un indice `index` che indica quale stato di base 
 * il sistema dovrebbe assumere. La funzione imposta tutte le ampiezze degli stati quantistici 
 * a zero, eccetto quella corrispondente all'indice specificato, che viene impostata a 1.0, 
 * rappresentando così lo stato di base desiderato.
 *
 * @param state Un puntatore a una struttura `QubitState` che contiene il numero di qubit 
 *              e il vettore delle ampiezze da inizializzare.
 * @param index L'indice dello stato di base desiderato, che va da 0 a 2^numQubits - 1.
 *
 * Dettagli:
 * - `dim` rappresenta la dimensione dello spazio di Hilbert, pari a 2^numQubits.
 * - Tutti gli elementi di `state->amplitudes` vengono inizializzati a 0.0.
 * - L'elemento corrispondente all'indice specificato viene impostato a 1.0 + 0.0 * I, 
 *   indicando che il sistema è nello stato di base associato a quell'indice.
 */
void initializeStateTo(QubitState *state, int index) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        state->amplitudes[i] = 0.0 + 0.0 * I;
    }
    state->amplitudes[index] = 1.0 + 0.0 * I;  // Imposta l'ampiezza dello stato indicato a 1
}

void printState(QubitState *state) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        printf("Stato %lld: %f + %fi\n", i, creal(state->amplitudes[i]), cimag(state->amplitudes[i]));
    }
}


QubitState* initializeState(int numQubits) {
    QubitState *state = (QubitState *)malloc(sizeof(QubitState));
    state->numQubits = numQubits;
    long long dim = 1LL << numQubits; // 2^numQubits
    state->amplitudes = (double complex *)calloc(dim, sizeof(double complex));

    // Verifica che tutte le ampiezze siano inizializzate a 0
    for (long long i = 0; i < dim; i++) {
        state->amplitudes[i] = 0.0 + 0.0 * I;
    }

    // Imposta lo stato |0>^N
    state->amplitudes[0] = 1.0 + 0.0 * I; 

    return state;
}


void freeState(QubitState *state) {
    free(state->amplitudes);
    free(state);
}

void applySingleQubitGate(QubitState *state, int target, double complex gate[2][2]) {
    long long dim = 1LL << state->numQubits;
    double complex new_amplitudes[dim];

    // Copia le ampiezze originali nel nuovo array
    for (long long i = 0; i < dim; i++) {
        new_amplitudes[i] = state->amplitudes[i];
    }

    // Applica il gate al qubit target numerato da sinistra
    for (long long i = 0; i < dim; i++) {
        int bitValue = (i >> (state->numQubits - 1 - target)) & 1; // Determina se il bit target è 0 o 1
        long long j = i ^ (1LL << (state->numQubits - 1 - target)); // Calcola l'indice con il bit target invertito

        // Scambia le ampiezze se necessario
        if (bitValue == 1) {
            new_amplitudes[i] = gate[1][0] * state->amplitudes[j] + gate[1][1] * state->amplitudes[i];
            new_amplitudes[j] = gate[0][0] * state->amplitudes[j] + gate[0][1] * state->amplitudes[i];
        }
    }

    // Aggiorna le ampiezze nello stato originale
    for (long long i = 0; i < dim; i++) {
        state->amplitudes[i] = new_amplitudes[i];
    }
}


void applyHadamard(QubitState *state, int target) {
    double complex H[2][2] = {
        {1.0 / sqrt(2.0), 1.0 / sqrt(2.0)},
        {1.0 / sqrt(2.0), -1.0 / sqrt(2.0)}
    };
    applySingleQubitGate(state, target, H);
}


void applyX(QubitState *state, int target) {
double complex X[2][2] = {
        {0, 1},
        {1, 0}
    };
    applySingleQubitGate(state, target, X);
}



void applyZ(QubitState *state, int target) {
    double complex Z[2][2] = {
        {1, 0},
        {0, -1}
    };
    applySingleQubitGate(state, target, Z);
}

void applyCNOT(QubitState *state, int control, int target) {
    long long dim = 1LL << state->numQubits;
    double complex new_amplitudes[dim];

    // Copia le ampiezze originali nel nuovo array
    for (long long i = 0; i < dim; i++) {
        new_amplitudes[i] = state->amplitudes[i];
    }

    // Applica il gate CNOT con il controllo e il target numerati da sinistra a destra
    for (long long i = 0; i < dim; i++) {
        // Calcola il bit di controllo e il bit target correttamente orientati
        int control_bit = (i >> (state->numQubits - 1 - control)) & 1;
        int target_bit = (i >> (state->numQubits - 1 - target)) & 1;

        if (control_bit == 1) {
            long long j = i ^ (1LL << (state->numQubits - 1 - target)); // Inverti solo il bit target
            new_amplitudes[i] = state->amplitudes[j];
            new_amplitudes[j] = state->amplitudes[i];
        }
    }

    // Aggiorna le ampiezze nello stato originale
    for (long long i = 0; i < dim; i++) {
        state->amplitudes[i] = new_amplitudes[i];
    }
}

#include <stdlib.h>
#include <math.h>
#include <complex.h>

int measure(QubitState *state, int qubit) {
    long long dim = 1LL << state->numQubits;
    double prob0 = 0.0;

    // Calcola la probabilità che il qubit sia nello stato |0>
    for (long long i = 0; i < dim; i++) {
        if (((i >> qubit) & 1) == 0) { // Verifica se il qubit specificato è 0
            prob0 += pow(cabs(state->amplitudes[i]), 2);
        }
    }

    // Genera un numero casuale per decidere l'outcome della misura
    double rand_val = (double)rand() / RAND_MAX;
    int result = (rand_val < prob0) ? 0 : 1;

    // Collassa lo stato in base al risultato della misura
    double scale_factor = 0.0;
    if (result == 0) {
        scale_factor = 1.0 / sqrt(prob0);
        for (long long i = 0; i < dim; i++) {
            if (((i >> qubit) & 1) == 1) {
                state->amplitudes[i] = 0.0 + 0.0 * I; // Annulla le ampiezze con qubit = 1
            } else {
                state->amplitudes[i] *= scale_factor; // Normalizza le ampiezze con qubit = 0
            }
        }
    } else {
        double prob1 = 1.0 - prob0;
        scale_factor = 1.0 / sqrt(prob1);
        for (long long i = 0; i < dim; i++) {
            if (((i >> qubit) & 1) == 0) {
                state->amplitudes[i] = 0.0 + 0.0 * I; // Annulla le ampiezze con qubit = 0
            } else {
                state->amplitudes[i] *= scale_factor; // Normalizza le ampiezze con qubit = 1
            }
        }
    }

    return result;
}


int* measure_all(QubitState *state) {
    long long dim = 1LL << state->numQubits;  // Dimensione dello spazio di Hilbert: 2^numQubits
    double cumulativeProb = 0.0;  // Probabilità cumulativa inizializzata a 0
    double randNum = (double)rand() / RAND_MAX;  // Numero casuale tra 0 e 1
    long long collapse_index = -1;  // Indice dello stato in cui il sistema collasserà

    // Calcolo della distribuzione cumulativa delle probabilità
    for (long long i = 0; i < dim; i++) {
        cumulativeProb += pow(cabs(state->amplitudes[i]), 2);  // Somma delle probabilità
        if (randNum < cumulativeProb) {  // Trova lo stato in cui il sistema collassa
            collapse_index = i;  // Imposta l'indice del collasso
            break;  // Esce dal ciclo una volta trovato lo stato corrispondente
        }
    }

    // Risultato della misura: array contenente i valori di ciascun qubit
    int* results = (int*)malloc(state->numQubits * sizeof(int));  // Alloca memoria per il risultato
    for (int i = 0; i < state->numQubits; i++) {
        results[i] = (collapse_index >> (state->numQubits - i - 1)) & 1;  // Estrae il valore di ciascun qubit
    }

    // Far collassare lo stato del sistema
    for (long long j = 0; j < dim; j++) {
        if (j == collapse_index) {
            state->amplitudes[j] = 1.0 + 0.0 * I;  // Lo stato collassa nello stato base corrispondente
        } else {
            state->amplitudes[j] = 0.0 + 0.0 * I;  // Tutti gli altri stati vengono azzerati
        }
    }

    return results;  // Restituisce l'array dei risultati della misura
}
