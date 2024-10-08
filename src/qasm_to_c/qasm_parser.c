/*
 * QuantumSim: A Quantum Circuit Simulator for C Programmers
 * Copyright (C) 2024 Francesco Sisini
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateCFile(const char *outputFilename, int numQubits, int numCbits) {
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Errore nella creazione del file C");
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "#include \"quantum_sim.h\"\n");
    fprintf(outputFile, "#include <stdio.h>\n\n");
    fprintf(outputFile, "void circuit() {\n");
    fprintf(outputFile, "    int numQubits = %d;\n", numQubits); // Definisce il numero di qubits
    fprintf(outputFile, "    QubitState *state = initializeState(numQubits);\n");
    fprintf(outputFile, "    int q[%d]; // Array dei qubits\n", numQubits);
    fprintf(outputFile, "    int c[%d]; // Array dei bit classici\n\n", numCbits);

    fclose(outputFile);
}

void finalizeCFile(const char *outputFilename) {
    FILE *outputFile = fopen(outputFilename, "a");
    if (outputFile == NULL) {
        perror("Errore nella creazione del file C");
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "    printState(state);\n");
    fprintf(outputFile, "    freeState(state);\n");
    fprintf(outputFile, "}\n");

    fclose(outputFile);
}

void parseQASM(const char *filename, const char *outputFilename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file QASM");
        exit(EXIT_FAILURE);
    }

    int numQubits = 0, numCbits = 0;
    char line[256];

    // Prima passata: Trova il numero di qubit e bit classici
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "qreg")) {
            sscanf(line, "qreg q[%d];", &numQubits);
        } else if (strstr(line, "creg")) {
            sscanf(line, "creg c[%d];", &numCbits);
        }
    }

    if (numQubits == 0) {
        fprintf(stderr, "Errore: qreg non trovato o numero di qubits non valido.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (numCbits == 0) {
        fprintf(stderr, "Errore: creg non trovato o numero di bit classici non valido.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Crea il file C con il numero di qubits e bit classici trovato
    generateCFile(outputFilename, numQubits, numCbits);

    // Seconda passata: Analizza le istruzioni e le aggiunge al file C
    rewind(file); // Riavvolge il file per la seconda passata
    FILE *outputFile = fopen(outputFilename, "a"); // Apre in modalità append

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "qreg") || strstr(line, "creg")) {
            // Ignora la definizione del registro quantistico e classico
            continue;
        } else if (strstr(line, "h ")) {
            int qubit;
            sscanf(line, "h q[%d];", &qubit);
            fprintf(outputFile, "    applyHadamard(state, %d);\n", qubit);
        } else if (strstr(line, "cx ")) {
            int control, target;
            sscanf(line, "cx q%d,q%d;", &control, &target);
            fprintf(outputFile, "    applyCNOT(state, %d, %d);\n", control, target);
        } else if (strstr(line, "x ")) {
            int qubit;
            sscanf(line, "x q[%d];", &qubit);
            fprintf(outputFile, "    applyX(state, %d);\n", qubit);
        } else if (strstr(line, "measure ")) {
            int qubit, cbit;
            sscanf(line, "measure q[%d] -> c[%d];", &qubit, &cbit);
            fprintf(outputFile, "    int result = measure(state, %d);\n", qubit);
            fprintf(outputFile, "    c[%d] = result;\n", cbit);
	    fprintf(outputFile, "    printf(\"c[%d]=%%d\\n\",result);\n", cbit);
        } else {
            fprintf(outputFile, "    // Istruzione non riconosciuta: %s", line);
        }
    }

    fclose(file);
    fclose(outputFile);

    // Finalizza il file C
    finalizeCFile(outputFilename);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Utilizzo: %s <file.qasm> <output.c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parseQASM(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
