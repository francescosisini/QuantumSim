
# QuantumSim

![Build Status](https://github.com/your-username/QuantumSim/actions/workflows/ci.yml/badge.svg)
[![codecov](https://codecov.io/gh/your-username/QuantumSim/branch/main/graph/badge.svg)](https://codecov.io/gh/your-username/QuantumSim)

## Introduzione

QuantumSim è un simulatore di circuiti quantistici progettato per aiutare a comprendere e visualizzare l'esecuzione di vari algoritmi quantistici. Supporta la conversione tra diversi formati di descrizione del circuito e offre strumenti per analizzare i risultati dei test.

## Caratteristiche

- **Simulazione dei Circuiti Quantistici**: Simula vari circuiti quantistici e supporta molteplici algoritmi noti.
- **Parser QASM**: Converte file QASM (Quantum Assembly Language) in rappresentazioni eseguibili.
- **Parser C a QASM**: Converte descrizioni di circuiti scritte in C in file QASM.
- **Analisi della Code Coverage**: Integrata nel processo di Continuous Integration per garantire la qualità del codice.

## Come Compilare

Per compilare il progetto, assicurati di avere `gcc` installato e poi esegui:

```bash
make
```

Questo comando creerà i seguenti eseguibili:
- `QuantumSim`: Il simulatore principale dei circuiti quantistici.
- `QasmParser`: Parser per file QASM.
- `CtoQasm`: Parser per convertire codice C in file QASM.

## Eseguire i Test

Abbiamo configurato una serie di test per garantire che ogni parte del progetto funzioni correttamente. Per eseguire i test, usa:

```bash
make test
```
Oppure puoi eseguire direttamente lo script di test:

```bash
./run_tests.sh
```

### Generare Report di Code Coverage

Per generare un report di copertura del codice e visualizzare quali parti del codice sono coperte dai test, usa:

```bash
make coverage
```

I risultati saranno salvati in un file `coverage.info` e puoi visualizzarli direttamente nel terminale.

## Continuous Integration

Questo progetto utilizza GitHub Actions per Continuous Integration. Ogni commit e ogni pull request attiva automaticamente la compilazione del codice, l'esecuzione dei test e la generazione di report di code coverage. Gli stati della build e della copertura sono visibili direttamente in questo README tramite i badge sopra.

## QuantumSim - Simulatore Quantistico in C

QuantumSim è un simulatore di calcolo quantistico che supporta gate universali a 2 qubits e la funzionalità di misurazione. 
Questo simulatore consente di inizializzare stati quantistici, applicare gate quantistici e misurare gli stati quantistici risultanti.

[![Scarica ora](https://img.shields.io/badge/Download-Scarica_ora-blue?style=for-the-badge&logo=github)](https://github.com/francescosisini/QuantumSim/archive/refs/heads/master.zip)

![QuantumSim - Scopri di più e scaricalo](images/youandmequbit.jpeg)

## Introduzione al Progetto: Esplora il mondo della computazione quantistica con il simulatore open-source

QuantumSim è un simulatore di computazione quantistica progettato per programmatori C che desiderano esplorare il mondo della programmazione quantistica senza dover necessariamente avere una profonda conoscenza della meccanica quantistica. 

Per una descrizione dettagliata del progetto, consulta la [Introduzione completa](INTRODUCTION.md).

## Caratteristiche

- Inizializzazione di stati quantistici con qualsiasi numero di qubits.
- Applicazione di gate quantistici a 1, 2 e 3 qubit, tra cui Hadamard, Pauli-X, Pauli-Z, CNOT, e gate a 3 qubit come Toffoli (CCNOT), Fredkin, CCZ e CCY.
- **Decomposizione dei gate a 3 qubit**: Come in un vero hardware quantistico, i gate a 3 qubit vengono decomposti in operazioni elementari, utilizzando gate a 1 e 2 qubit (vedi Khaneja Glaser Decomposition (KGD)), garantendo una simulazione accurata e realistica.
- Misurazione dello stato quantistico e collasso in uno stato base.
- Stampa di debug per tracciare il flusso di esecuzione e visualizzare lo stato quantistico in ogni momento.

## Documentazione di Supporto

Per una spiegazione dettagliata su come vengono rappresentati e inizializzati gli stati quantistici nel simulatore, consulta la [Documentazione sugli Stati Quantistici](QUANTUM_STATES.md).

Questo documento copre:

- La base teorica degli stati quantistici.
- La rappresentazione matematica degli stati con \( n \) qubit.
- La relazione tra concetti fisici e implementazione nel codice.

## Documentazione Aggiuntiva

- [Applicazione dei Quantum Gates](./QUANTUM_GATES.md): Scopri come vengono applicati i quantum gates agli stati quantistici in questo progetto.

## Struttura del Progetto

```
QuantumSim/
├── src/                           # Directory principale dei file sorgente
│   ├── quantum_sim.c              # Implementazione del simulatore quantistico
│   ├── circuit.c                  # Implementazione del circuito quantistico
│   ├── main.c                     # Punto di ingresso principale del simulatore
│   ├── qasm_to_c/                 # Directory contenente il parser da QASM a C
│   │   └── qasm_parser.c          # Codice sorgente per il parser QASM-to-C
│   └── c_to_qasm/                 # Directory contenente il parser da C a QASM
│       └── c_to_qasm.c            # Codice sorgente per il parser C-to-QASM
├── Makefile                       # Makefile per la compilazione del progetto
├── README.md                      # Documentazione del progetto
└── LICENSE                        # Licenza del progetto
```

## Requisiti

- GCC (GNU Compiler Collection)
- Make

## Installazione

Clona il repository e naviga nella directory del progetto:

```sh
git clone https://github.com/francescosisini/QuantumSim.git
cd QuantumSim
```

## Compilazione

### Utilizzo del Makefile per QuantumSim

Il Makefile di `QuantumSim` è stato aggiornato per facilitare la compilazione e l'esecuzione di circuiti quantistici definiti in file C. Ora è possibile specificare un file di circuito personalizzato da compilare direttamente tramite il Makefile.

#### Opzioni Disponibili

- `CIRCUIT_FILE`: Nome del file contenente il circuito quantistico in C che si desidera compilare. Se non viene specificato, verrà utilizzato il file predefinito `src/circuit.c`.

##### Comandi del Makefile

Compilare QuantumSim con un circuito predefinito:

```bash
make
```

Compilare QuantumSim con un file di circuito personalizzato:

```bash
make CIRCUIT_FILE=src/my_custom_circuit.c
```

Pulire gli eseguibili compilati:

```bash
make clean
```

##### Esempio

Supponiamo di avere un circuito personalizzato definito nel file `src/custom_circuit.c`. Per compilare e eseguire QuantumSim con questo circuito, eseguire:

```bash
make CIRCUIT_FILE=src/custom_circuit.c
./QuantumSim
```

## Uso

```sh
./QuantumSim
```

## Disclaimer

Questo progetto è stato creato con finalità didattiche e divulgative. Sebbene sia stato sviluppato con cura, potrebbero esserci errori o imprecisioni. Per maggiori dettagli, consulta il [Disclaimer completo](DISCLAIMER.md).

## Note Legali

QuantumSim è rilasciato sotto la licenza GNU General Public License v3. Per maggiori informazioni, leggi il file `LICENSE`.

## Contatti

Per qualsiasi domanda, suggerimento o per segnalare bug, sentiti libero di aprire una issue o di contattarmi direttamente.

Grazie per il tuo interesse nel contribuire a QuantumSim!
