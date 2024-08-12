#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateQASMFile(const char *outputFilename, int numQubits) {
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Errore nella creazione del file QASM");
        exit(EXIT_FAILURE);
    }

    // Scrive l'intestazione QASM
    fprintf(outputFile, "OPENQASM 2.0;\n");
    fprintf(outputFile, "include \"qelib1.inc\";\n");
    fprintf(outputFile, "qreg q[%d];\n", numQubits);
    fprintf(outputFile, "creg c[%d];\n", numQubits);

    fclose(outputFile);
}

void parseCFile(const char *filename, const char *outputFilename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file C");
        exit(EXIT_FAILURE);
    }

    int numQubits = 0;
    char line[256];
    FILE *outputFile = fopen(outputFilename, "a"); // Apre in modalità append

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "initializeState(")) {
            sscanf(line, "    QubitState *state = initializeState(%d);", &numQubits);
            generateQASMFile(outputFilename, numQubits);
        } else if (strstr(line, "applyHadamard(")) {
            int qubit;
            sscanf(line, "    applyHadamard(state, %d);", &qubit);
            fprintf(outputFile, "h q[%d];\n", qubit);
        } else if (strstr(line, "applyCNOT(")) {
            int control, target;
            sscanf(line, "    applyCNOT(state, %d, %d);", &control, &target);
            fprintf(outputFile, "cx q[%d],q[%d];\n", control, target);
        } else if (strstr(line, "applyX(")) {
            int qubit;
            sscanf(line, "    applyX(state, %d);", &qubit);
            fprintf(outputFile, "x q[%d];\n", qubit);
        } else if (strstr(line, "measure(")) {
            int qubit, creg;
            sscanf(line, "    measure(state, %d, %d);", &qubit, &creg);
            fprintf(outputFile, "measure q[%d] -> c[%d];\n", qubit, creg);
        } else {
            fprintf(outputFile, "// Istruzione non riconosciuta: %s", line);
        }
    }

    fclose(file);
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Utilizzo: %s <file.c> <output.qasm>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parseCFile(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
