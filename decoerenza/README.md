# Algoritmo di Deutsch con Decoerenza: Catena di Ragionamenti

Questo documento descrive, a livello concettuale, i miei ragionaenti embrionali  per analizzare l'algoritmo di Deutsch utilizzando il formalismo della matrice di densità (ρ) in presenza di decoerenza (dephasing).

## 1. Stato Iniziale
- **Inizializzazione:**  
  I due qubit sono preparati nello stato \( |0\rangle \otimes |1\rangle \).  
  La matrice densità iniziale \(\rho_{\text{in}}\) è costruita come \( \rho_{\text{in}} = |0,1\rangle\langle0,1| \).

## 2. Applicazione del Primo Hadamard (H⊗H)
- **Trasformazione:**  
  Si applica il gate di Hadamard a ciascun qubit.  
  Il risultato è uno stato in sovrapposizione:  
  ```math
  |\psi_1\rangle = \frac{1}{2}\Bigl(|00\rangle - |01\rangle + |10\rangle - |11\rangle\Bigr).
  ```
- **Matrice densità:**  
  La matrice densità \(\rho_1\) derivante da questo stato è ricca di termini fuori diagonale, i quali sono essenziali per l'interferenza.

## 3. Introduzione della Decoerenza (Dephasing sul Primo Qubit)
- **Modello di Dephasing:**  
  Utilizziamo un canale di dephasing con operatori di Kraus per il primo qubit, estesi al sistema a due qubit.  
  Gli operatori sono:
  - \(K_0 = \sqrt{1-p}\, I\),
  - \(K_1 = \sqrt{p}\, Z\), dove \(Z\) è l'operatore di Pauli-Z.
- **Effetto sullo Stato:**  
  L'azione combinata \( \rho_{\text{dephased}} = (1-p)\,\rho_1 + p\,(Z\otimes I)\,\rho_1\,(Z\otimes I) \)
  attenua gli elementi fuori diagonale che collegano stati con diverso valore del primo qubit.  
  Nel caso \(p=\frac{1}{2}\) (massima decoerenza) tali elementi vengono completamente azzerati, riducendo lo stato a due blocchi indipendenti.

## 4. Applicazione del Gate \(H \otimes I\)
- **Secondo Hadamard:**  
  Viene applicato il gate di Hadamard solo sul primo qubit, trasformando le informazioni di fase accumulate.
- **Effetto sulla Misurazione:**  
  Dopo il secondo Hadamard, si calcola il ridotto del primo qubit.  
  Se il dephasing ha eliminato le correlazioni (quando \(p=\frac{1}{2}\)), il primo qubit risulterà in uno stato completamente misto:  
  \[
  \rho^{(1)}_{\text{final}} = \frac{I}{2}.
  \]
  Ciò implica una probabilità del 50% di misurare 0 e 50% di misurare 1, compromettendo il vantaggio computazionale dell'algoritmo.

## Conclusione
- **Sintesi:**  
  L'interferenza, essenziale per distinguere in modo deterministico tra funzioni costanti e bilanciate, viene compromessa dalla decoerenza.  
  In presenza di dephasing massimizzato, l'algoritmo di Deutsch perde la sua capacità di produrre un risultato deterministico.
