# QuantumSim

QuantumSim è un simulatore di calcolo quantistico che supporta gate universali a 2 qubits e la funzionalità di misurazione. 
Questo simulatore consente di inizializzare stati quantistici, applicare gate quantistici e misurare gli stati quantistici risultanti.

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

void circuit() {
    int numQubits = 2; // Definisci il numero di qubits
    QubitState *state = initializeState(numQubits); // Inizializza lo stato quantistico

    printf("Stato quantistico inizializzato.\n");

    // Applicare Hadamard a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("Hadamard applicato a tutti i qubits.\n");

    // Supponiamo che l'elemento marcato sia lo stato |11>
    // Applicare l'oracolo di Grover
    applyCNOT(state, 0, 1);  // Controllo il primo qubit, target il secondo qubit
    applyX(state, 0);  // Applico X gate al primo qubit
    applyCNOT(state, 0, 1);  // Controllo il primo qubit, target il secondo qubit
    applyX(state, 0);  // Applico X gate al primo qubit

    printf("Oracolo di Grover applicato.\n");

    // Applicare la diffusione di Grover
    // Applicare Hadamard a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyHadamard(state, i);
    }

    // Applicare X a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyX(state, i);
    }

    // Applicare una porta multi-controlled-Z (in questo caso, controllato su due qubits)
    applyCNOT(state, 0, 1);
    applyZ(state, 1);
    applyCNOT(state, 0, 1);

    // Applicare X a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyX(state, i);
    }

    // Applicare Hadamard a tutti i qubits
    for (int i = 0; i < numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("Diffusione di Grover applicata.\n");

    // Misurare lo stato finale
    int *results = measure_all(state);
    printf("Risultato della misura:\n");
    for (int i = 0; i < numQubits; i++) {
        printf("Qubit %d: %d\n", i, results[i]);
    }

    free(results);
    freeState(state); // Libera la memoria dello stato quantistico

    printf("Memoria liberata.\n");
}
```
