# Decoerenza e Qubit in una buca infinita

## 1. Ipotesi ideale di buca infinita
Consideriamo un modello teorico in cui una particella quantistica (es. un elettrone) è confinata in una **buca di potenziale infinita** unidimensionale di lunghezza L. In questo scenario:
- Le pareti della buca sono impenetrabili, cioè il potenziale è infinito fuori dalla buca.
- La funzione d'onda della particella deve annullarsi ai bordi.
- Gli **autostati del sistema** sono soluzioni dell'equazione di Schrödinger indipendente dal tempo con condizioni al contorno rigide.

## 2. Stati sinusoidali
Le soluzioni sono **onde stazionarie sinusoidali**:

`$
\psi_n(x) = \sqrt{\frac{2}{L}} \sin\left(\frac{n\pi x}{L}\right), \quad n = 1, 2, 3, ...
`$

I corrispondenti **livelli energetici** sono:

$
E_n = \frac{n^2 \pi^2 \hbar^2}{2mL^2}
$

Questi stati sono **ortogonali e completi**, e la differenza tra due livelli può essere usata per definire un qubit.

## 3. Codifica di un qubit
Consideriamo di codificare un **qubit** usando i due stati più bassi:
- $|0\rangle = \psi_1$ (frequenza associata $\omega_1$)
- \(|1\rangle = \psi_2\) (frequenza associata \(\omega_2\))

La differenza energetica tra i due livelli definisce la **frequenza di transizione del qubit**:

\[
\hbar \omega_0 = E_2 - E_1
\]

## 4. Hamiltoniana libera del sistema
Nel rotating frame (risonante) e centrando l'energia attorno allo zero, l'Hamiltoniana del qubit è:

\[
H_0 = \frac{\hbar \omega_0}{2} \sigma_z
\]

Dove:
- \(\omega_0\) è la frequenza di transizione tra |0\rangle e |1\rangle.
- \(\sigma_z\) è la matrice di Pauli z.

## 5. Interazione con un campo esterno (H_int)
Per applicare trasformazioni al qubit, introduciamo un campo oscillante (laser, microonde):

\[
H_{\text{int}} = \hbar \Omega \cos(\omega t + \phi)\, \sigma_x
\]

Dove:
- \(\Omega\) è la frequenza di Rabi (intensità dell'interazione)
- \(\omega\) è la frequenza del campo
- \(\phi\) è la fase
- \(\sigma_x\) induce transizioni tra |0\rangle e |1\rangle

## 6. Modellazione dei gate quantistici
Nel **rotating frame** e sotto la **rotating wave approximation (RWA)**, l'interazione si semplifica in una rotazione sullo sferoide di Bloch:

\[
H_{\text{eff}} = \frac{\hbar \Omega}{2} (\cos \phi\, \sigma_x + \sin \phi\, \sigma_y)
\]

Variando \(\phi\), \(\Omega\) e \(\Delta t\), si ottengono diversi **quantum gate**:
- Gate X (NOT): rotazione di \(\pi\) attorno all'asse X
- Gate H (Hadamard): combinazione di rotazioni
- Rotazioni arbitrarie: controllando tempo e fase

## 7. Applicazione della decoerenza
In un sistema reale, la **decoerenza** degrada la coerenza quantistica. Possiamo modellarla con una **matrice densità** del tipo:

\[
\rho(t) = \begin{pmatrix} \rho_{00} & \rho_{01} e^{-\gamma t} \\ \rho_{10} e^{-\gamma t} & \rho_{11} \end{pmatrix}
\]

Dove:
- \(\gamma\) è il tasso di decoerenza
- I termini fuori diagonale (\(\rho_{01}, \rho_{10}\)) decadono esponenzialmente, riducendo l'interferenza quantistica

Questo modello permette di studiare **l'effetto della decoerenza** su fenomeni di sovrapposizione e interferenza, sia analiticamente che sperimentalmente (es. con forme d'onda audio modulate come nel progetto).

---

Questa descrizione collega la teoria quantistica astratta a una possibile realizzazione fisica e visiva, e getta le basi per un'esplorazione creativa come la sfera di Bloch meccanica interattiva.

