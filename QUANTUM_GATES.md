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

- numQubits: Numero di qubits nel sistema.
- amplitudes: Un array di numeri complessi che rappresenta le ampiezze di probabilità degli stati base del sistema quantistico.

L'array amplitudes ha dimensione 2numQubits2numQubits e ogni elemento corrisponde all'ampiezza di probabilità di uno degli stati base.

## Applicazione dei Quantum Gates
1. Porta Hadamard (H)

La porta Hadamard crea una sovrapposizione tra gli stati ∣0⟩ e ∣1⟩. La sua matrice è:
```
H = (1/sqrt(2)) *| 1  1 |
                 | 1 -1 |
    
```
Implementazione in QuantumSim:

```
void applyHadamard(QubitState *state, int target) {
    double complex H[2][2] = {
        {1.0 / sqrt(2.0), 1.0 / sqrt(2.0)},
        {1.0 / sqrt(2.0), -1.0 / sqrt(2.0)}
    };
    applySingleQubitGate(state, target, H);
}
```
2. Porta Pauli-X (X)

La porta Pauli-X agisce come una NOT quantistica, invertendo lo stato del qubit:
X = | 0  1 |
    | 1  0 |

Implementazione in QuantumSim:

```
void applyX(QubitState *state, int target) {
    double complex X[2][2] = {
        {0, 1},
        {1, 0}
    };
    applySingleQubitGate(state, target, X);
}
```
Questa funzione scambia le ampiezze degli stati ∣0⟩∣0⟩ e ∣1⟩∣1⟩ per il qubit target, simulando l'inversione dello stato.

3. Porta Pauli-Z (Z)

La porta Pauli-Z applica una fase di −1−1 allo stato ∣1⟩∣1⟩ del qubit:
Z = | 1  0 |
    | 0 -1 |

Implementazione in QuantumSim:
```

void applyZ(QubitState *state, int target) {
    double complex Z[2][2] = {
        {1, 0},
        {0, -1}
    };
    applySingleQubitGate(state, target, Z);
}
```
Questa funzione modifica la fase dello stato ∣1⟩∣1⟩ del qubit target senza alterare le ampiezze degli altri stati.

4. Controlled-NOT (CNOT)

La porta CNOT (Controlled-NOT) agisce su due qubits: un qubit di controllo e un qubit target. 
Inverte il qubit target solo se il qubit di controllo è nello stato ∣1⟩.
```
Cnot = | 1  0  0  0|
       | 0  1  0  0|
       | 0  0  0  1|
       | 0  0  1  0|
```
Implementazione in QuantumSim:

```

void applyCNOT(QubitState *state, int control, int target) {
    long long dim = 1LL << state->numQubits;
    for (long long i = 0; i < dim; i++) {
        if ((i >> control) & 1) {
            long long j = i ^ (1LL << target);
            double complex temp = state->amplitudes[i];
            state->amplitudes[i] = state->amplitudes[j];
            state->amplitudes[j] = temp;
        }
    }
}
```
Questa funzione verifica se il qubit di controllo è nello stato ∣1⟩∣1⟩ (mediante la condizione if ((i >> control) & 1)). Se sì, inverte lo stato del qubit target, scambiando le ampiezze degli stati base corrispondenti.
