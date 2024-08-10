# Applicazione dei Quantum Gates nel Progetto QuantumSim

## Introduzione

QuantumSim è un simulatore di calcolo quantistico che consente di manipolare e misurare stati quantistici attraverso l'applicazione di un insieme universale di quantum gates.
In questo documento, esploreremo come i quantum gates vengono applicati agli stati quantistici all'interno del progetto.

## Quantum Gates Supportati

Nel progetto QuantumSim, i principali quantum gates implementati e supportati sono:

- Hadamard (H)
- Pauli-X (X)
- Pauli-Z (Z)
- Controlled-NOT (CNOT)

Questi gates sono utilizzati per manipolare gli stati dei qubits all'interno di un sistema quantistico.

## Rappresentazione degli Stati Quantistici

Gli stati quantistici in QuantumSim sono rappresentati da una struttura chiamata QubitState. Questa struttura include:
```
    numQubits: Numero di qubits nel sistema.
    amplitudes: Un array di numeri complessi che rappresenta le ampiezze di probabilità degli stati base del sistema quantistico.
```
L'array amplitudes ha dimensione 2numQubits2numQubits e ogni elemento corrisponde all'ampiezza di probabilità di uno degli stati base.
Applicazione dei Quantum Gates
1. Porta Hadamard (H)

La porta Hadamard crea una sovrapposizione tra gli stati ∣0⟩∣0⟩ e ∣1⟩∣1⟩. La sua matrice è:
H=12(111−1)
H=2
​1​(11​1−1​)

Implementazione in QuantumSim:
