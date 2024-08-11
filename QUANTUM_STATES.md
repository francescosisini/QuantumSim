# Stato Computazionale di un Sistema di nn Qubit

In un sistema quantistico, un qubit può trovarsi in uno stato ∣0⟩,∣1⟩, o in una sovrapposizione di questi due stati. 
Quando si considera un sistema composto da nn qubit, lo stato dell'intero sistema può essere descritto come una combinazione lineare di tutti gli stati possibili dei singoli qubit.

## Dimensione dello Spazio di Stato

Ogni qubit ha due stati base, ∣0⟩ e ∣1⟩. Quindi, per nn qubit, il numero totale di combinazioni di stati base è $2^n$. 
Queste combinazioni rappresentano tutti i possibili stati computazionali del sistema, che possono essere scritti come ∣00…0⟩ fino a ∣11…1⟩.

Ad esempio, per un sistema di 3 qubit, i possibili stati sono:
∣000⟩,∣001⟩,∣010⟩,∣011⟩,∣100⟩,∣101⟩,∣110⟩,∣111⟩

Questo produce un totale di $2^3=8$ stati.

## Rappresentazione Matematica

Questi stati possono essere rappresentati come vettori in uno spazio di Hilbert di dimensione $2^n$. 
Ogni stato del sistema è un vettore con $2^n$ componenti, dove ciascuna componente è un numero complesso che rappresenta l'ampiezza di probabilità per uno specifico stato base.

Ad esempio, per n=2 qubit, il vettore di stato generale è:

∣ψ⟩=α0∣00⟩+α1∣01⟩+α2∣10⟩+α3∣11⟩
∣ψ⟩=α0​∣00⟩+α1​∣01⟩+α2​∣10⟩+α3​∣11⟩

dove α0,α1,α2,α3 sono numeri complessi.
## Implicazioni nella Simulazione

Nella simulazione, questo significa che per rappresentare lo stato di nn qubit, è necessario un array di dimensione $2^n$.
Ogni elemento di questo array rappresenta l'ampiezza di probabilità per uno degli $2^n$ stati base. 
Questo spiega perché, nel codice, la dimensione dell'array amplitudes è calcolata come 1<<numQubits, ovvero $2^numQubits$.
