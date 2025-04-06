# Algoritmo di Deutsch con Formalismo delle Matrici Densità

Questo documento descrive i miei ragionamenti preliminari e calcoli eseguiti per analizzare l'algoritmo di Deutsch utilizzando il formalismo della matrice di densità (ρ) per un sistema a due qubit (matrice 4×4). In particolare, viene evidenziato l'effetto della decoerenza (dephasing) applicata al primo qubit e il suo impatto sul meccanismo di interferenza dell'algoritmo.

---

## 1. Stato Iniziale

I due qubit sono inizializzati nello stato:

```math
|\psi_{\text{in}}\rangle = |0\rangle \otimes |1\rangle = |0,1\rangle.
```

La matrice densità associata è:

```math
\rho_{\text{in}} = |\psi_{\text{in}}\rangle\langle\psi_{\text{in}}| =
\begin{pmatrix}
0 & 0 & 0 & 0\\[0.3em]
0 & 1 & 0 & 0\\[0.3em]
0 & 0 & 0 & 0\\[0.3em]
0 & 0 & 0 & 0
\end{pmatrix}.
```

---

## 2. Applicazione del Primo Hadamard su Entrambi i Qubit

Il gate di Hadamard per un singolo qubit è dato da:

```math
H = \frac{1}{\sqrt{2}}
\begin{pmatrix}
1 & 1\\[0.3em]
1 & -1
\end{pmatrix}.
```

Applicando $`H`$ a ciascun qubit, l'operatore totale è $` H \otimes H.`$ Sui singoli qubit:
```math
 H|0\rangle = \frac{1}{\sqrt{2}}(|0\rangle+|1\rangle),
```
```math
 H|1\rangle = \frac{1}{\sqrt{2}}(|0\rangle-|1\rangle).
```
Quindi lo stato diventa:

```math
|\psi_1\rangle = (H\otimes H)\,|0,1\rangle = \frac{1}{2}\Bigl(|00\rangle - |01\rangle + |10\rangle - |11\rangle\Bigr).
```

La matrice densità associata è:

```math
\rho_1 = |\psi_1\rangle\langle\psi_1| = \frac{1}{4}
\begin{pmatrix}
1 & -1 & 1 & -1\\[0.3em]
-1 & 1 & -1 & 1\\[0.3em]
1 & -1 & 1 & -1\\[0.3em]
-1 & 1 & -1 & 1
\end{pmatrix}.
```

---

## 3. Applicazione del Canale di Dephasing sul Primo Qubit

Per modellare la decoerenza (dephasing) sul primo qubit usiamo gli operatori di Kraus per un singolo qubit:

```math
K_0 = \sqrt{1-p}\, I, \quad K_1 = \sqrt{p}\, Z,
```
con

```math
Z = \begin{pmatrix}1 & 0\\[0.3em] 0 & -1\end{pmatrix}.
```

Estendiamo questi operatori al sistema a due qubit (in cui il canale agisce solo sul primo qubit):

```math
K_0^{(2)} = K_0 \otimes I = \sqrt{1-p}\,(I\otimes I), \quad K_1^{(2)} = K_1 \otimes I = \sqrt{p}\,(Z\otimes I).
```

L'azione complessiva sullo stato è:

```math
\rho_{\text{dephased}} = K_0^{(2)}\,\rho_1\,\left(K_0^{(2)}\right)^\dagger + K_1^{(2)}\,\rho_1\,\left(K_1^{(2)}\right)^\dagger.
```

Poiché $`K_0^{(2)}`$ e $`K_1^{(2)}`$ sono rispettivamente $`\sqrt{1-p}(I\otimes I)`$ e $`\sqrt{p}(Z\otimes I)`$, possiamo scrivere:

```math

\rho_{\text{dephased}} = (1-p)\,\rho_1 + p\,(Z\otimes I)\,\rho_1\,(Z\otimes I).
```

**Azione di $`Z \otimes I`$:**

Nel sistema a due qubit, l'operatore $`Z \otimes I`$ si presenta come:

```math
Z \otimes I = diagonale(1,\,1,\,-1,\,-1),
```
ordinando la base come $`|00\rangle,\, |01\rangle,\, |10\rangle,\, |11\rangle`$. L'azione di $`Z\otimes I`$ moltiplica per:
- $`+1`$ le componenti con primo qubit $`0`$ (stati $`|00\rangle`$ e $`|01\rangle`$),
- $`-1`$ le componenti con primo qubit $`1`$ (stati $`|10\rangle`$ e $`|11\rangle`$).

Pertanto, ogni elemento $`\rho_1(i,j)`$ si trasforma come:

```math
\rho_{\text{dephased}}(i,j) = \Bigl[(1-p) + p\,d_i\,d_j\Bigr]\,\rho_1(i,j),
```
dove $`d = [1,\,1,\,-1,\,-1]`$.

- Se $`d_i\,d_j = 1`$, l'elemento rimane invariato.
- Se $`d_i\,d_j = -1`$, l'elemento viene moltiplicato per $`(1-p) - p = 1-2p`$.

Quindi, la matrice $`\rho_{\text{dephased}}`$ diventa:

```math
\rho_{\text{dephased}} = \frac{1}{4}\begin{pmatrix}
1 & -1 & (1-2p) & -(1-2p)\\[0.3em]
-1 & 1 & -(1-2p) & (1-2p)\\[0.3em]
(1-2p) & -(1-2p) & 1 & -1\\[0.3em]
-(1-2p) & (1-2p) & -1 & 1
\end{pmatrix}.
```

**Caso particolare: $`p=\frac{1}{2}`$**

Per $`p=\frac{1}{2}`$ si ha $`1-2p = 0`$. Quindi:

```math
\rho_{\text{dephased}} = \frac{1}{4}\begin{pmatrix}
1 & -1 & 0 & 0\\[0.3em]
-1 & 1 & 0 & 0\\[0.3em]
0 & 0 & 1 & -1\\[0.3em]
0 & 0 & -1 & 1
\end{pmatrix}.
```

Questo significa che le correlazioni (gli elementi fuori diagonale) tra stati con diverso valore del primo qubit vengono azzerate.

---

## 4. Applicazione del Gate $`H \otimes I`$

Successivamente, si applica un gate di Hadamard solo sul primo qubit, cioè l'operatore $`H \otimes I`$. Il gate $`H`$ è:

```math
H = \frac{1}{\sqrt{2}}\begin{pmatrix}1 & 1\\[0.3em]1 & -1\end{pmatrix}.
```

L'operazione totale è:

```math
\rho_{\text{final}} = (H\otimes I)\,\rho_{\text{dephased}}\,(H\otimes I)^\dagger.
```

### Riduzione al Primo Qubit

Per comprendere l'effetto sul primo qubit si calcola il ridotto, tracciando sul secondo qubit:

```math
\rho^{(1)}_{\text{final}} = \mathrm{Tr}_2\{\rho_{\text{final}}\}.
```

Nel nostro caso, prima dell'applicazione di $`H\otimes I`$, il ridotto del primo qubit derivato da $`\rho_{\text{dephased}}`$ risulta:

```math
\rho^{(1)}_{\text{dephased}} = \begin{pmatrix}\frac{1}{2} & 0 \\[0.3em] 0 & \frac{1}{2}\end{pmatrix}.
```

Essendo già uno stato completamente misto, l'azione di $`H`$ sul primo qubit non modifica la forma, e pertanto:

```math
\rho^{(1)}_{\text{final}} = H\,\rho^{(1)}_{\text{dephased}}\,H^\dagger = \frac{I}{2} = \begin{pmatrix}\frac{1}{2} & 0 \\[0.3em] 0 & \frac{1}{2}\end{pmatrix}.
```

---

## 5. Conclusione

In condizioni ideali (senza decoerenza), il secondo Hadamard trasforma le informazioni di fase introdotte dall'oracolo in un risultato deterministico. Tuttavia, se il dephasing sul primo qubit è massimizzato ($`p=\frac{1}{2}`$), gli elementi fuori diagonale essenziali per l'interferenza vengono completamente annullati. Di conseguenza, dopo l'applicazione di $`H\otimes I`$, il primo qubit risulta in uno stato completamente misto:

```math
\rho^{(1)}_{\text{final}} = \frac{I}{2},
```

che implica una probabilità del 50% di misurare $`0`$ e 50% di misurare $`1`$. In altre parole, la decoerenza compromette il meccanismo interferometrico dell'algoritmo di Deutsch, eliminando il vantaggio computazionale.

---

## Riepilogo della Catena di Ragionamenti

1. **Stato Iniziale:**

```math
   \rho_{\text{in}} = |0,1\rangle\langle0,1|
```

2. **Applicazione del Primo Hadamard (H⊗H):**

   ```math
   |\psi_1\rangle = \frac{1}{2}\Bigl(|00\rangle - |01\rangle + |10\rangle - |11\rangle\Bigr)
   ```
   
   ```math
   \rho_1 = \frac{1}{4}
   \begin{pmatrix}
   1 & -1 & 1 & -1\\[0.3em]
   -1 & 1 & -1 & 1\\[0.3em]
   1 & -1 & 1 & -1\\[0.3em]
   -1 & 1 & -1 & 1
   \end{pmatrix}
   ```

3. **Applicazione della Decoerenza (Dephasing sul Primo Qubit):**

   ```math
   \rho_{\text{dephased}} = (1-p)\,\rho_1 + p\,(Z\otimes I)\,\rho_1\,(Z\otimes I)
   ```
   
   Con $`p=\frac{1}{2}`$ (massima decoerenza), si ottiene:

   ```math
   \rho_{\text{dephased}} = \frac{1}{4}
   \begin{pmatrix}
   1 & -1 & 0 & 0\\[0.3em]
   -1 & 1 & 0 & 0\\[0.3em]
   0 & 0 & 1 & -1\\[0.3em]
   0 & 0 & -1 & 1
   \end{pmatrix}
   ```

4. **Applicazione del Gate $`H \otimes I`$ e Riduzione:**

   ```math
   \rho_{\text{final}} = (H\otimes I)\,\rho_{\text{dephased}}\,(H\otimes I)^\dagger,
   ```
   che porta a:
   
   ```math
   \rho^{(1)}_{\text{final}} = \frac{I}{2} = \begin{pmatrix}\frac{1}{2} & 0\\[0.3em]0 & \frac{1}{2}\end{pmatrix}.
   ```

5. **Effetto sulla Misurazione:**

   Il primo qubit, essendo in uno stato completamente misto, darà $`0`$ o $`1`$ con probabilità pari, eliminando il vantaggio interferometrico dell'algoritmo.

---

Questo documento fornisce una panoramica completa e formale della catena di calcoli e ragionamenti relativi all'algoritmo di Deutsch in presenza di decoerenza.  
