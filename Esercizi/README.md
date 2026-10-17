# Esercizi di QuantumSim

Questa cartella raccoglie gli esercizi del libro **«Esercizi di informatica quantistica: Guida pratica con l’uso del simulatore QuantumSim»** di **Valentina Sisini**. I programmi sono scritti in C e accompagnano un percorso di apprendimento: dai primi stati quantistici e dalle porte logiche fino all’entanglement e agli algoritmi di Deutsch e Grover.

📘 [Il libro su Amazon](https://amzn.eu/d/04nWroyW)

## Come compilare ed eseguire gli esercizi

Apri il terminale **nella cartella principale del repository `QuantumSim`** (dove si trova il `Makefile`), con `make` e un compilatore C disponibili. Per compilare un esercizio, usa `make -B CIRCUIT_FILE=Esercizi/<nome_file>.c`. 
Poi avvia il circuito compilato con `./QuantumSim`.

Ad esempio, per il primo esercizio:

```bash
make -B CIRCUIT_FILE=Esercizi/es_1_initialize_qubit_state.c
./QuantumSim
```

## Esercizi guidati

### 1. Inizializzazione di un qubit

**File:** [`es_1_initialize_qubit_state.c`](./es_1_initialize_qubit_state.c)

Inizializza un singolo qubit nello stato base `|0⟩` usando le funzioni di QuantumSim. Introduce la rappresentazione dello stato nel codice, senza produrre output a schermo.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_1_initialize_qubit_state.c`

### 2. Stampa dello stato `|0⟩`

**File:** [`es_2_print_qubit_state_0.c`](./es_2_print_qubit_state_0.c)

Prepara un qubit nello stato `|0⟩` e ne stampa le ampiezze complesse. Mostra come osservare uno stato nel simulatore senza effettuare una misura.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_2_print_qubit_state_0.c`

### 3. Stampa dello stato `|1⟩`

**File:** [`es_3_print_qubit_state_1.c`](./es_3_print_qubit_state_1.c)

Prepara un qubit nello stato `|1⟩` e ne stampa le ampiezze complessse.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_3_print_qubit_state_1.c`

### 4. Porta Hadamard sullo stato `|0⟩`

**File:** [`es_4_apply_hadamard_to_state_0.c`](./es_4_apply_hadamard_to_state_0.c)

Applica Hadamard a `|0⟩`, creando una sovrapposizione di `|0⟩` e `|1⟩`. Stampa lo stato e lo misura, mostrando le probabilità e il risultato ottenuto.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_4_apply_hadamard_to_state_0.c`

### 5. Porta Hadamard sullo stato `|1⟩`

**File:** [`es_5_apply_hadamard_to_state_1.c`](./es_5_apply_hadamard_to_state_1.c)

Applica Hadamard a `|1⟩`, ottenendo una sovrapposizione con una diversa fase relativa rispetto all’esercizio 4. Stampa le ampiezze ed esegue una misura del qubit.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_5_apply_hadamard_to_state_1.c`

### 6. Porte di Pauli X, Y, Z sullo stato `|0⟩`

**File:** [`es_6_apply_pauli_xyz_to_state_0.c`](./es_6_apply_pauli_xyz_to_state_0.c)

Applica separatamente le porte X, Y e Z a un qubit inizializzato in `|0⟩`. Confronta i risultati evidenziando cambiamenti di stato e di fase.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_6_apply_pauli_xyz_to_state_0.c`

### 7. Porte di Pauli X, Y, Z sullo stato `|1⟩`

**File:** [`es_7_apply_pauli_xyz_to_state_1.c`](./es_7_apply_pauli_xyz_to_state_1.c)

Ripete le trasformazioni X, Y e Z partendo da `|1⟩`, reinizializzando il qubit prima di ogni prova. Permette di osservare come l’effetto delle porte dipenda dallo stato iniziale.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_7_apply_pauli_xyz_to_state_1.c`

### 8. Porte di fase S, T, T† sullo stato `|0⟩`

**File:** [`es_8_apply_s_t_tdag_to_state_0.c`](./es_8_apply_s_t_tdag_to_state_0.c)

Applica separatamente le porte S, T e T† allo stato `|0⟩`. Mostra che queste trasformazioni di fase lasciano invariato tale stato.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_8_apply_s_t_tdag_to_state_0.c`

### 9. Porte di fase S, T, T† sullo stato `|1⟩`

**File:** [`es_9_apply_s_t_tdag_to_state_1.c`](./es_9_apply_s_t_tdag_to_state_1.c)

Applica separatamente S, T e T† allo stato `|1⟩`. Osserva le diverse fasi introdotte dalle tre porte nelle ampiezze complesse.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_9_apply_s_t_tdag_to_state_1.c`

### 10. Inizializzazione di due qubit

**File:** [`es_10_initialize_two_qubits_state.c`](./es_10_initialize_two_qubits_state.c)

Inizializza un sistema di due qubit nei quattro stati base `|00⟩`, `|01⟩`, `|10⟩` e `|11⟩`. Stampa ciascuno stato per esplorare la rappresentazione del registro quantistico.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_10_initialize_two_qubits_state.c`

### 11. Porta CNOT sugli stati base

**File:** [`es_11_apply_cnot_to_base_states.c`](./es_11_apply_cnot_to_base_states.c)

Applica CNOT a tutti e quattro gli stati base di due qubit. Mostra che il qubit target viene invertito soltanto quando il qubit di controllo vale `1`.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_11_apply_cnot_to_base_states.c`

### 12. Il primo stato di Bell

**File:** [`es_12_first_bell_state.c`](./es_12_first_bell_state.c)

Costruisce lo stato di Bell `( |00⟩ + |11⟩ ) / √2` applicando Hadamard e CNOT. Introduce l’entanglement attraverso la stampa dello stato risultante.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_12_first_bell_state.c`

### 13. Misura del primo stato di Bell

**File:** [`es_13_measure_first_bell_state.c`](./es_13_measure_first_bell_state.c)

Prepara e misura uno stato di Bell per dieci esecuzioni consecutive. Evidenzia la correlazione tra i due risultati di misura, che coincidono in ogni prova ideale.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_13_measure_first_bell_state.c`

### 14. Porta CZ sugli stati base

**File:** [`es_14_apply_cz_to_base_states.c`](./es_14_apply_cz_to_base_states.c)

Applica CZ a tutti gli stati base di un sistema di due qubit. Evidenzia l’inversione di fase della componente `|11⟩`, mentre le altre rimangono invariate.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_14_apply_cz_to_base_states.c`

### 15. Porta CZ su una sovrapposizione

**File:** [`es_15_apply_cz_to_superposition_state.c`](./es_15_apply_cz_to_superposition_state.c)

Crea una sovrapposizione uniforme di due qubit con Hadamard e poi applica CZ. Mostra la variazione della fase di `|11⟩` senza cambiare le probabilità di misura nella base computazionale.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_15_apply_cz_to_superposition_state.c`

### 16. Effetto osservabile della fase relativa

**File:** [`es_16_cz_phase_inference.c`](./es_16_cz_phase_inference.c)

Applica la sequenza Hadamard–CZ–Hadamard a un registro inizializzato in `|10⟩`. Dimostra come una differenza di fase possa diventare osservabile tramite interferenza, ottenendo `|11⟩`.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_16_cz_phase_inference.c`

### 17. Porta CCZ su una sovrapposizione

**File:** [`es_17_apply_ccz_to_superposition_state.c`](./es_17_apply_ccz_to_superposition_state.c)

Crea una sovrapposizione uniforme di tre qubit e applica la porta CCZ. Osserva che cambia solo il segno dell’ampiezza di `|111⟩`.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_17_apply_ccz_to_superposition_state.c`

### 18. Porta Toffoli sugli stati base

**File:** [`es_18_apply_toffoli_to_base_states.c`](./es_18_apply_toffoli_to_base_states.c)

Applica la porta Toffoli ai due stati iniziali `|010⟩` e `|111⟩`. Mostra che il primo resta invariato, mentre il secondo viene trasformato in `|110⟩`.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/es_18_apply_toffoli_to_base_states.c`

## Algoritmi quantistici

### Algoritmo di Deutsch

**File:** [`algo_1_deutsch.c`](./algo_1_deutsch.c)

Implementa l’algoritmo di Deutsch per distinguere una funzione booleana costante da una bilanciata. Chiede di selezionare una delle quattro funzioni disponibili e interpreta la misura finale.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/algo_1_deutsch.c`

### Algoritmo di Grover

**File:** [`algo_2_grover.c`](./algo_2_grover.c)

Simula una iterazione di Grover su tre qubit per individuare gli stati target `|110⟩` e `|111⟩`. L’oracolo ne inverte la fase, l’operatore di diffusione ne amplifica le probabilità e infine viene eseguita la misura.

**Compila:** `make -B CIRCUIT_FILE=Esercizi/algo_2_grover.c`

## Per approfondire

Le spiegazioni teoriche, lo svolgimento guidato e la discussione dei risultati si trovano nel libro: **capitolo 5** per gli esercizi da 1 a 18, **capitolo 6** per Deutsch e **capitolo 7** per Grover. Per informazioni sul simulatore consulta anche il [README principale](../README.md).
