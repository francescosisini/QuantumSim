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
#include <regex.h>

void parseCtoQASM(const char *inputFilename, const char *outputFilename) {
    FILE *file = fopen(inputFilename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file C");
        exit(EXIT_FAILURE);
    }

    int numQubits = 0;
    char line[256];
    char qubitVar[50] = ""; // Variabile per conservare il nome della variabile che contiene il numero di qubits

    regex_t regex;
    regcomp(&regex, "initializeState\\s*\\(\\s*([0-9]+|[a-zA-Z_][a-zA-Z0-9_]*)\\s*\\);", REG_EXTENDED);

    // Prima passata: Trova l'inizializzazione dello stato quantistico e ottieni il numero di qubits
    while (fgets(line, sizeof(line), file)) {
        regmatch_t matches[2];
        if (regexec(&regex, line, 2, matches, 0) == 0) {
            char match[256];
            snprintf(match, matches[1].rm_eo - matches[1].rm_so + 1, "%s", line + matches[1].rm_so);
            if (sscanf(match, "%d", &numQubits) == 1) {
                break; // Numero di qubits trovato direttamente
            } else {
                strncpy(qubitVar, match, sizeof(qubitVar) - 1);
                qubitVar[sizeof(qubitVar) - 1] = '\0'; // Assicurati che sia terminato correttamente
                break;
            }
        }
    }

    regfree(&regex);

    if (numQubits == 0 && qubitVar[0] != '\0') {
        // Cerca la variabile che contiene il numero di qubits
        rewind(file);
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, qubitVar)) {
                sscanf(line, "%*s %*s %d", &numQubits);
                break;
            }
        }
    }

    if (numQubits == 0) {
        fprintf(stderr, "Errore: initializeState non trovato o numero di qubits non valido.\n");
	fprintf(stderr, "Il numero di qubuts sarà impostato a 2.\n");
        numQubits = 2;
        
    }

    // Seconda passata: Genera il file QASM
    rewind(file);
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Errore nella creazione del file QASM");
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "qreg q[%d];\n", numQubits);

    // Analizza le istruzioni e convertili in QASM
    while (fgets(line, sizeof(line), file)) {
        int qubit;
        if (strstr(line, "applyX")) {
            sscanf(line, "applyX(state, %d);", &qubit);
            fprintf(outputFile, "x q[%d];\n", qubit);
        } else if (strstr(line, "applyHadamard")) {
            sscanf(line, "applyHadamard(state, %d);", &qubit);
            fprintf(outputFile, "h q[%d];\n", qubit);
        } else if (strstr(line, "applyCNOT")) {
            int control, target;
            sscanf(line, "applyCNOT(state, %d, %d);", &control, &target);
            fprintf(outputFile, "cx q[%d],q[%d];\n", control, target);
        }
    }

    fclose(file);
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Utilizzo: %s <input.c> <output.qasm>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parseCtoQASM(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
