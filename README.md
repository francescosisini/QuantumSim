# QuantumSim

QuantumSim è un simulatore di calcolo quantistico che supporta gate universali a 2 qubits e la funzionalità di misurazione. 
Questo simulatore consente di inizializzare stati quantistici, applicare gate quantistici e misurare gli stati quantistici risultanti.

## Introduzione al Progetto

QuantumSim è un simulatore di computazione quantistica progettato per programmatori C che desiderano esplorare il mondo della programmazione quantistica senza dover necessariamente avere una profonda conoscenza della meccanica quantistica. 

Per una descrizione dettagliata del progetto, consulta la [Introduzione completa](INTRODUCTION.md).


## Caratteristiche

   - Inizializzazione di stati quantistici con qualsiasi numero di qubits.
   - Applicazione dei gate Hadamard, Pauli-X, Pauli-Z e CNOT.
   - Misurazione dello stato quantistico e collasso in uno stato base.
   - Print di debug per tracciare il flusso di esecuzione.

## Documentazione di Supporto

Per una spiegazione dettagliata su come vengono rappresentati e inizializzati gli stati quantistici nel simulatore, consulta la [Documentazione sugli Stati Quantistici](QUANTUM_STATES.md).

Questo documento copre:

- La base teorica degli stati quantistici.
- La rappresentazione matematica degli stati con \( n \) qubit.
- La relazione tra concetti fisici e implementazione nel codice.

  
## Documentazione Aggiuntiva

- [Applicazione dei Quantum Gates](./QUANTUM_GATES.md): Scopri come vengono applicati i quantum gates agli stati quantistici in questo progetto.



## Struttura del Progetto

```

QuantumSim/
├── quantum_sim.h         # File header contenente dichiarazioni di funzioni e strutture dati
├── quantum_sim.c         # Implementazione dell'inizializzazione dello stato quantistico, dei gate e della misurazione
├── circuit.c             # Esempio di circuito quantistico utilizzando il simulatore
├── main.c                # File principale per eseguire il circuito quantistico
├── Makefile              # Makefile per la compilazione del progetto
├── README.md             # Documentazione principale del progetto
└── QUANTUM_GATES.md      # Documentazione dettagliata sull'applicazione dei quantum gates
```
## Requisiti

- GCC (GNU Compiler Collection)
- Make

## Installazione

Clone the repository and navigate to the project directory:

```sh
git clone https://github.com/francescosisini/QuantumSim.git
cd QuantumSim
```

## Compilazione

usando il Makefile del progetto
```sh
make
```
Questo genererà un eseguibile chiamato QuantumSim.

## Uso

Utilizzo
```sh

./QuantumSim
```
## Esempio

Ecco un esempio di come viene definito ed eseguito il circuito quantistico:

### circuit.c
```
#include "quantum_sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>


void circuit() {
    // Test su 1 qubit
    printf("Test su 1 qubit:\n");
    int numQubits = 1;
    QubitState *state = initializeState(numQubits);

    // Caso 1: Stato iniziale |0>
    printf("\nCaso 1: Stato iniziale |0>\n");
    printState(state);

    // Caso 2: Applico X a |0>
    applyX(state, 0);
    printf("Caso 2: Stato dopo X:\n");
    printState(state);

    // Caso 3: Applico Hadamard a |0>
    applyHadamard(state, 0);
    printf("Caso 3: Stato dopo Hadamard:\n");
    printState(state);

    // Caso 4: Applico Z a |0>
    applyZ(state, 0);
    printf("Caso 4: Stato dopo Z:\n");
    printState(state);

    // Pulizia della memoria per 1 qubit
    freeState(state);

    // Test su 2 qubit
    printf("\nTest su 2 qubit:\n");
    numQubits = 2;
    state = initializeState(numQubits);

    // Caso 1: Stato iniziale |00>
    printf("\nCaso 1: Stato iniziale |00>\n");
    printState(state);

    // Caso 2: Applico X al primo qubit |10>
    applyX(state, 0);
    printf("Caso 2: Stato dopo X su qubit 0:\n");
    printState(state);

    // Caso 3: Applico X al secondo qubit |11>
    applyX(state, 1);
    printf("Caso 3: Stato dopo X su qubit 1:\n");
    printState(state);

    // Caso 4: Applico Hadamard al primo qubit
    applyHadamard(state, 0);
    printf("Caso 4: Stato dopo Hadamard su qubit 0:\n");
    printState(state);

    // Caso 5: Applico CNOT con il primo qubit come controllo e il secondo come target
    applyCNOT(state, 0, 1);
    printf("Caso 5: Stato dopo CNOT (qubit 0 come controllo e qubit 1 come target):\n");
    printState(state);

    // Pulizia della memoria per 2 qubit
    freeState(state);

    // Test su 3 qubit
    printf("\nTest su 3 qubit:\n");
    numQubits = 3;
    state = initializeState(numQubits);

    // Caso 1: Stato iniziale |000>
    printf("\nCaso 1: Stato iniziale |000>\n");
    printState(state);

    // Caso 2: Applico X al primo qubit |100>
    applyX(state, 0);
    printf("Caso 2: Stato dopo X su qubit 0:\n");
    printState(state);

    // Caso 3: Applico X al terzo qubit |101>
    applyX(state, 2);
    printf("Caso 3: Stato dopo X su qubit 2:\n");
    printState(state);

    // Caso 4: Stato di Bell |000> + |111>
    initializeStateTo(state, 0);
    applyHadamard(state, 0);
    applyCNOT(state, 0, 1);
    applyCNOT(state, 0, 2);
    printf("Caso 4: Stato di Bell |000> + |111>\n");
    printState(state);

    // Misura finale dello stato di Bell
    int* results = measure_all(state);
    printf("Risultato della misura dello stato di Bell:\n");
    for (int i = 0; i < numQubits; i++) {
        printf("Qubit %d: %d\n", i, results[i]);
    }

    // Pulizia della memoria per 3 qubit
    free(results);
    freeState(state);
}

```
## Disclaimer

Questo progetto è stato creato con finalità didattiche e divulgative. Sebbene sia stato sviluppato con cura, potrebbero esserci errori o imprecisioni. Per maggiori dettagli, consulta il [Disclaimer completo](DISCLAIMER.md).
