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
- ### Porta Hadamard (H)

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
- ### Porta Pauli-X (X)

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

- ### Porta Pauli-Z (Z)

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

- ### Controlled-NOT (CNOT)

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


```
Questa funzione verifica se il qubit di controllo è nello stato ∣1⟩ (mediante la condizione if ((i >> control) & 1)). Se sì, inverte lo stato del qubit target, scambiando le ampiezze degli stati base corrispondenti.
Funzione applySingleQubitGate

Le porte Hadamard, X e Z sono tutte implementate usando una funzione generica applySingleQubitGate, che si occupa di applicare un qualsiasi gate a un singolo qubit. La funzione scorre tutti gli stati del sistema, determina quali stati devono essere modificati, e applica la matrice di trasformazione corrispondente.

### Implementazione di applySingleQubitGate:

```
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

```
