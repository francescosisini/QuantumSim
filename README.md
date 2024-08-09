# QuantumSim

QuantumSim is a quantum computing simulator that supports universal 2-qubit gates and measurement functionality. 
This simulator allows you to initialize quantum states, apply quantum gates, and measure the resulting quantum states.

## Features

- Initialize quantum states with any number of qubits.
- Apply Hadamard, Pauli-X, Pauli-Z, and CNOT gates.
- Measure the quantum state and collapse it to a basis state.
- Debugging print statements to trace the execution flow.
- Proper memory management to avoid memory leaks.

# Esempio: Grover's Algorithm, scopo e funzionamento
A Cosa Serve l'Algoritmo di Grover?

L'algoritmo di Grover è un algoritmo di ricerca quantistica che consente di trovare una voce in un database non ordinato con una velocità quadratica rispetto ai migliori algoritmi classici. 
Mentre un algoritmo classico richiede O(N)O(N) operazioni per trovare un elemento in un database di NN voci, l'algoritmo di Grover può farlo in O(N)O(N) operazioni.
Passaggi dell'Algoritmo di Grover

    - Inizializzazione:
        Preparare lo stato quantistico iniziale applicando il gate Hadamard a tutti i qubits per creare una sovrapposizione uniforme di tutti gli stati possibili.

    - Oracolo di Grover:
        Applicare una funzione oracolo che inverte la fase dell'elemento target (marcato) del database. Questo oracolo è una funzione specifica del problema che si vuole risolvere.

    - Diffusione di Grover:
        Applicare una trasformazione di inversione e diffusione per amplificare la probabilità dell'elemento target.

    - Ripetizione:
        Ripetere l'oracolo di Grover e la diffusione di Grover un numero ottimale di volte (circa NN

        ​ iterazioni).

    - Misurazione:
        Misurare il sistema quantistico per ottenere l'elemento target con alta probabilità.

## Circuito di Grover

Il circuito di Grover implementato è costituito dai seguenti passaggi:

    Inizializzazione con Hadamard Gate:
        Applica un gate Hadamard su entrambi i qubits per creare una sovrapposizione uniforme.

    Oracolo di Grover:
        Applica una porta CNOT con il primo qubit come controllo e il secondo come target.
        Applica una porta Pauli-X (NOT) sul primo qubit.
        Applica un'altra porta CNOT con il primo qubit come controllo e il secondo come target.
        Applica un'altra porta Pauli-X (NOT) sul primo qubit.

    Diffusione di Grover:
        Applica un gate Hadamard su entrambi i qubits.
        Applica una porta Pauli-X su entrambi i qubits.
        Applica una porta CNOT con il primo qubit come controllo e il secondo come target.
        Applica una porta Pauli-Z (Z) sul secondo qubit.
        Applica un'altra porta CNOT con il primo qubit come controllo e il secondo come target.
        Applica una porta Pauli-X su entrambi i qubits.
        Applica un gate Hadamard su entrambi i qubits.

    Misurazione:
        Misura entrambi i qubits.

Grafico a Caratteri del Circuito di Grover
```
Qubit 0: |0> ----[H]----●----[X]----●----[X]----[H]----[X]----●----[Z]----●----[X]----[H]----
                        |           |                         |           |         
Qubit 1: |0> ----[H]----○----[ ]----○----[ ]----[H]----[X]----○----[ ]----○----[X]----[H]----
```
Descrizione dello Schema

    [H]: Porta Hadamard (H) – crea una sovrapposizione tra ∣0⟩∣0⟩ e ∣1⟩∣1⟩.
    [X]: Porta NOT (X) – inverte lo stato del qubit (∣0⟩∣0⟩ diventa ∣1⟩∣1⟩ e viceversa).
    [Z]: Porta Z (Z) – applica una fase di −1−1 allo stato ∣1⟩∣1⟩.
    [●]: Controllo della porta CNOT – l'operazione viene eseguita se il qubit di controllo è ∣1⟩∣1⟩.
    [○]: Target della porta CNOT – il qubit viene invertito se il qubit di controllo è ∣1⟩∣1⟩.

Passaggi del Circuito

    Inizializzazione con Hadamard (H): Entrambi i qubits sono inizialmente nello stato ∣0⟩∣0⟩. Dopo l'applicazione delle porte Hadamard, i qubits sono in una sovrapposizione di tutti gli stati ∣00⟩∣00⟩, ∣01⟩∣01⟩, ∣10⟩∣10⟩, ∣11⟩∣11⟩.

    Oracolo di Grover:
        CNOT con controllo su Qubit 0 e target su Qubit 1: Questo oracolo inverte l'ampiezza del solo stato ∣11⟩∣11⟩ (dipende dall'elemento marcato).
        Applicazione delle porte X e CNOT per l'oracolo: Le porte X invertono i qubits prima e dopo la CNOT, per creare la condizione necessaria per l'oracolo.

    Diffusione di Grover:
        Porte Hadamard (H): Riapplicate su entrambi i qubits.
        Porte X: Riapplicate su entrambi i qubits.
        CNOT con controllo su Qubit 0 e target su Qubit 1: Applica la porta Z al qubit target come parte del diffusore di Grover.
        Porte X e Hadamard (H): Finali, per completare la diffusione.

## Project Structure

```

QuantumSim/
├── quantum_sim.h         # Header file containing function declarations and data structures
├── quantum_sim.c         # Implementation of quantum state initialization, gates, and measurement
├── circuit.c             # Example quantum circuit using the simulator
├── main.c                # Main file to run the quantum circuit
├── Makefile              # Makefile for building the project
└── README.md             # Project documentation
```
## Requirements

- GCC (GNU Compiler Collection)
- Make

## Installation

Clone the repository and navigate to the project directory:

```sh
git clone https://github.com/francescosisini/QuantumSim.git
cd QuantumSim
```

## Compilation

Use the provided Makefile to compile the project:

```sh
make
```
This will generate an executable named QuantumSim.
## Usage

Run the simulator using:

```sh

./QuantumSim
```
## Example

Here is an example of how the quantum circuit is defined and executed:
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
