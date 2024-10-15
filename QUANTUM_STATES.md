# Stato Computazionale di un Sistema di n Qubit

In un sistema quantistico, un qubit può trovarsi in uno stato ∣0⟩,∣1⟩, o in una sovrapposizione di questi due stati. 
Quando si considera un sistema composto da nn qubit, lo stato dell'intero sistema può essere descritto come una combinazione lineare di tutti gli stati possibili dei singoli qubit.

Nella libreria, uno stato quantistico è rappresentato come un oggetto ```QubitState```. Questo oggetto contiene informazioni sul numero di qubit e sulle loro ampiezze complesse, che rappresentano lo stato del sistema quantistico.

## Dimensione dello Spazio di Stato

Ogni qubit ha due stati base, ∣0⟩ e ∣1⟩. Quindi, per nn qubit, il numero totale di combinazioni di stati base è $2^n$. 
Queste combinazioni rappresentano tutti i possibili stati computazionali del sistema, che possono essere scritti come ∣00…0⟩ fino a ∣11…1⟩.

Ad esempio, per un sistema di 3 qubit, i possibili stati sono:
∣000⟩,∣001⟩,∣010⟩,∣011⟩,∣100⟩,∣101⟩,∣110⟩,∣111⟩

Questo produce un totale di $2^3=8$ stati.

## Ordinamento dei Qubit e delle Ampiezze

il qubit $q_0$ corrisponde al bit meno significativo (LSB, coefficiente di $2^0$), mentre il qubit $q_{N-1}$ corrisponde al bit più significativo (MSB, coefficiente di $2^{N−1}$). Questo significa che quando si rappresenta lo stato di un sistema quantistico, il qubit $q_0$ influenza il bit più a destra nella rappresentazione binaria degli stati.
## Rappresentazione Matematica

Questi stati possono essere rappresentati come vettori in uno spazio di Hilbert di dimensione $2^n$. 
Ogni stato del sistema è un vettore con $2^n$ componenti, dove ciascuna componente è un numero complesso che rappresenta l'ampiezza di probabilità per uno specifico stato base.

Ad esempio, per n=2 qubit, il vettore di stato generale è:

∣ψ⟩=α0∣00⟩+α1∣01⟩+α2∣10⟩+α3∣11⟩

dove α0,α1,α2,α3 sono numeri complessi.
## Implicazioni nella Simulazione

Nella simulazione, questo significa che per rappresentare lo stato di nn qubit, è necessario un array di dimensione $2^n$.
Ogni elemento di questo array rappresenta l'ampiezza di probabilità per uno degli $2^n$ stati base. 
Questo spiega perché, nel codice, la dimensione dell'array amplitudes è calcolata come 1<<numQubits, ovvero $2^numQubits$.

## Creazione di uno Stato nella Libreria

In C, la struttura QubitState è definita come segue:

```

typedef struct {
    int numQubits;
    double complex *amplitudes;
} QubitState;
```
    ```numQubits``` rappresenta il numero di qubit nel sistema.
    ```amplitudes``` è un array di numeri complessi che contiene le ampiezze per ogni stato base.

## Inizializzazione di uno Stato

La funzione initializeState è responsabile della creazione e inizializzazione dello stato quantistico nel nostro simulatore:

```

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
```
Allocazione della Memoria: Viene allocata memoria per l'oggetto QubitState e per l'array di ampiezze complesse.
Dimensione dello Spazio di Hilbert: La dimensione dello spazio di Hilbert è calcolata come 2numQubits2numQubits.
Inizializzazione dello Stato: L'array di ampiezze viene inizializzato con zeri, eccetto la componente corrispondente allo stato ∣00…0⟩ che viene impostata a 1.0 (cioè, lo stato ∣00…0⟩ è lo stato iniziale del sistema).

Questo corrisponde a mettere il sistema in un singolo stato base iniziale (generalmente ∣00…0⟩∣00…0⟩), che rappresenta lo stato fondamentale del sistema quantistico.
## Esempio Pratico: Stato di un Singolo Qubit

Per un singolo qubit, lo stato quantistico può essere rappresentato da un vettore a due componenti, ad esempio ∣ψ⟩=α0∣0⟩+α1∣1⟩. Dopo l'inizializzazione con ```initializeState(1)```, il sistema si troverà nello stato ∣0⟩ con α0=1.0 e α1=0.0.
## Concetto di Misura e Collasso dello Stato

Quando misuriamo un qubit, il suo stato collassa in uno degli stati base con una probabilità proporzionale al quadrato del modulo dell'ampiezza corrispondente.
Nella libreria, la funzione measure_all simula questo collasso per tutti i qubit.


