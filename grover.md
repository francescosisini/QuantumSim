# Implementazione dell'Algoritmo di Grover con QuantumSim

In questa pagina viene descritta l'implementazione dell'algoritmo di Grover utilizzando la libreria **QuantumSim**, presente nel repository [QuantumSim](https://github.com/francescosisini/QuantumSim). Questa implementazione è specifica per un sistema quantistico con 3 qubit, dove vengono marcati gli stati target \(|110\rangle\) e \(|111\rangle\).

---

## Descrizione dell'algoritmo

L'algoritmo di Grover è un metodo quantistico per la ricerca in database non strutturati che offre un'accelerazione quadratica rispetto agli approcci classici. In questa implementazione:

1. **Hadamard-Walsh** viene applicato per creare una sovrapposizione uniforme di tutti gli stati.
2. **L'oracolo** inverte il segno degli stati target \(|110\rangle\) e \(|111\rangle\).
3. **L'operatore di diffusione** amplifica le ampiezze degli stati target.
4. Alla fine, viene eseguita una **misurazione** per ottenere il risultato.

---

## Implementazione

### 1. Funzione `applyHadamardWalsh`
Questa funzione applica l'operatore Hadamard-Walsh a tutti i qubit per creare una sovrapposizione uniforme degli stati:

```c
void applyHadamardWalsh(QubitState *state) {
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }
    printf("Applicato Hadamard-Walsh su tutti i qubit per creare la sovrapposizione uniforme\n");
    printState(state);
}
```

### 2. Funzione `applyOracle`
L'oracolo marca gli stati target \(|110\rangle\) e \(|111\rangle\) utilizzando il gate CCZ e un'operazione X:

```c
void applyOracle(QubitState *state) {
    printf("Applicazione dell'oracolo per marcare gli stati target\n");
    
    // Marca lo stato |110⟩ e |111⟩ usando i gate CCZ
    applyX(state, 0);
    applyCCZ(state, 1, 2, 0);
    applyX(state, 0);
    applyCCZ(state, 1, 2, 0);

    printf("Stato marcato: |110⟩ e |111⟩ \n");
    printState(state);
}
```

### 3. Funzione `applyDiffusion`
L'operatore di diffusione amplifica le ampiezze degli stati target utilizzando una combinazione di gate Hadamard, X e CCZ:

```c
void applyDiffusion(QubitState *state) {
    printf("Applicazione dell'operatore di diffusione per amplificare gli stati target\n");

    // Step 1: Applica Hadamard su tutti i qubit
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }

    // Step 2: Inverte il segno di tutti gli stati (applica gate X)
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
    }

    // Step 3: Applica un gate CCZ per la riflessione rispetto a |000⟩
    applyCCZ(state, 1, 2, 0);

    // Step 4: Ripristina i qubit applicando di nuovo X
    for (int i = 0; i < state->numQubits; i++) {
        applyX(state, i);
    }

    // Step 5: Applica Hadamard su tutti i qubit per completare la riflessione
    for (int i = 0; i < state->numQubits; i++) {
        applyHadamard(state, i);
    }

    printf("Operatore di diffusione applicato con successo\n");
    printState(state);
}
```

### 4. Funzione principale `circuit`
La funzione principale coordina l'esecuzione dei vari passi dell'algoritmo:

```c
void circuit() {
    printf("Avvio dell'algoritmo di Grover\n");

    // Inizializza lo stato con 3 qubit
    QubitState *state = initializeState(3);
    printf("Stato iniziale con 3 qubit (|000⟩)\n");
    printState(state);

    // Step 1: Applica Hadamard-Walsh per creare la sovrapposizione uniforme
    applyHadamardWalsh(state);

    // Step 2: Applica l'oracolo per marcare gli stati target
    applyOracle(state);

    // Step 3: Applica l'operatore di diffusione per amplificare gli stati target
    applyDiffusion(state);

    // Misura i qubit
    printf("Misurazione dello stato finale\n");
    for (int i = 0; i < state->numQubits; i++) {
        MeasurementResult result = measure(state, i);
        printf("Misura del qubit %d: %d\n", i, result.result);
    }

    printf("Stato finale dopo la misurazione\n");
    printState(state);
}
```

---

## Risultati attesi
Dopo l'applicazione dell'algoritmo di Grover:
1. Gli stati target \(|110\rangle\) e \(|111\rangle\) avranno probabilità amplificate.
2. La misurazione finale restituirà uno di questi stati con probabilità significativamente maggiore rispetto agli altri.

---

## Esecuzione
Compila ed esegui il codice per osservare i risultati:

```bash
gcc -o grover_example quantum_sim.c -lm
./grover_example
```

---

## Contributi
Se desideri contribuire al progetto o segnalare problemi, visita il repository [QuantumSim](https://github.com/francescosisini/QuantumSim).
