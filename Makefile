CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# Directory dei file sorgente
SRC_DIR=src
PARSER_DIR=qasm_to_c

# File sorgente per il simulatore
SRC=$(SRC_DIR)/quantum_sim.c $(SRC_DIR)/circuit.c $(SRC_DIR)/main.c

# Nome dell'eseguibile del simulatore
TARGET=QuantumSim

# File sorgente per il parser QASM
PARSER_SRC=$(PARSER_DIR)/qasm_parser.c

# Nome dell'eseguibile del parser QASM
PARSER_TARGET=QasmParser

all: $(TARGET) $(PARSER_TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

$(PARSER_TARGET): $(PARSER_SRC)
	$(CC) $(CFLAGS) -o $(PARSER_TARGET) $(PARSER_SRC) -lm

clean:
	rm -f $(TARGET) $(PARSER_TARGET)
