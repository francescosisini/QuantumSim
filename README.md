# QuantumSim - Simulatore Quantistico in C

QuantumSim è un simulatore di calcolo quantistico che supporta gate universali a 2 qubits e la funzionalità di misurazione. 
Questo simulatore consente di inizializzare stati quantistici, applicare gate quantistici e misurare gli stati quantistici risultanti.

[![Scarica ora](https://img.shields.io/badge/Download-Scarica_ora-blue?style=for-the-badge&logo=github)](https://github.com/tuo-progetto/archive/main.zip)





![QuantumSim - Scopri di più e scaricalo](images/youandmequbit.jpeg)


## Introduzione al Progetto: Esplora il mondo della computazione quantistica con il simulatore open-source

QuantumSim è un simulatore di computazione quantistica progettato per programmatori C che desiderano esplorare il mondo della programmazione quantistica senza dover necessariamente avere una profonda conoscenza della meccanica quantistica. 

Per una descrizione dettagliata del progetto, consulta la [Introduzione completa](INTRODUCTION.md).


## Caratteristiche

- Inizializzazione di stati quantistici con qualsiasi numero di qubits.
- Applicazione di gate quantistici a 1, 2 e 3 qubit, tra cui Hadamard, Pauli-X, Pauli-Z, CNOT, e gate a 3 qubit come Toffoli (CCNOT), Fredkin, CCZ e CCY.
- **Decomposizione dei gate a 3 qubit**: Come in un vero hardware quantistico, i gate a 3 qubit vengono decomposti in operazioni elementari, utilizzando gate a 1 e 2 qubit (vedi Khaneja Glaser Decomposition (KGD)), garantendo una simulazione accurata e realistica.
- Misurazione dello stato quantistico e collasso in uno stato base.
- Stampa di debug per tracciare il flusso di esecuzione e visualizzare lo stato quantistico in ogni momento.


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
├── src/                           # Directory principale dei file sorgente
│   ├── quantum_sim.c              # Implementazione del simulatore quantistico
│   ├── circuit.c                  # Implementazione del circuito quantistico
│   ├── main.c                     # Punto di ingresso principale del simulatore
│   ├── qasm_to_c/                 # Directory contenente il parser da QASM a C
│   │   └── qasm_parser.c          # Codice sorgente per il parser QASM-to-C
│   └── c_to_qasm/                 # Directory contenente il parser da C a QASM
│       └── c_to_qasm.c            # Codice sorgente per il parser C-to-QASM
├── Makefile                       # Makefile per la compilazione del progetto
├── README.md                      # Documentazione del progetto
└── LICENSE                        # Licenza del progetto

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

### Utilizzo del Makefile per QuantumSim

Il Makefile di ```QuantumSim``` è stato aggiornato per facilitare la compilazione e l'esecuzione di circuiti quantistici definiti in file C.
Ora è possibile specificare un file di circuito personalizzato da compilare direttamente tramite il Makefile.

#### Opzioni Disponibili

- CIRCUIT_FILE: Nome del file contenente il circuito quantistico in C che si desidera compilare. Se non viene specificato, verrà utilizzato il file predefinito src/circuit.c.

##### Comandi del Makefile

    Compilare QuantumSim con un circuito predefinito:

```
make
```
Questo comando utilizzerà il file src/circuit.c come circuito predefinito e compilerà l'eseguibile QuantumSim.

##### Compilare QuantumSim con un file di circuito personalizzato:
```
make CIRCUIT_FILE=src/my_custom_circuit.c
```

##### Questo comando compila QuantumSim utilizzando il file src/my_custom_circuit.c come sorgente per il circuito.

Pulire gli eseguibili compilati:
```
    make clean
```
    Questo comando rimuove gli eseguibili generati (QuantumSim, QasmParser, CtoQasm).

##### Esempio

Supponiamo di avere un circuito personalizzato definito nel file src/custom_circuit.c. Per compilare e eseguire QuantumSim con questo circuito, eseguire:
```
make CIRCUIT_FILE=src/custom_circuit.c
./QuantumSim
```
## Uso

Utilizzo
```sh

./QuantumSim
```
## Esempio

Ecco un esempio di come viene definito ed eseguito il circuito quantistico:

### circuit.c
```
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

```
## Disclaimer

Questo progetto è stato creato con finalità didattiche e divulgative. Sebbene sia stato sviluppato con cura, potrebbero esserci errori o imprecisioni. Per maggiori dettagli, consulta il [Disclaimer completo](DISCLAIMER.md).
