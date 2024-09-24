CC=gcc
CFLAGS=-w -Wall -Wextra -std=c99

# Directory dei file sorgente
SRC_DIR=src
QASM_TO_C_DIR=$(SRC_DIR)/qasm_to_c
C_TO_QASM_DIR=$(SRC_DIR)/c_to_qasm

# Nome del file del circuito (puoi specificare un file diverso chiamando `make CIRCUIT_FILE=nomefile.c`)
CIRCUIT_FILE ?= $(SRC_DIR)/circuit.c

# File sorgente per il simulatore
SRC=$(SRC_DIR)/quantum_sim.c $(CIRCUIT_FILE) $(SRC_DIR)/main.c 

# Nome dell'eseguibile del simulatore
TARGET=QuantumSim

# File sorgente per il parser QASM
PARSER_SRC=$(QASM_TO_C_DIR)/qasm_parser.c

# Nome dell'eseguibile del parser QASM
PARSER_TARGET=QasmParser

# File sorgente per il parser da C a QASM
C_TO_QASM_SRC=$(C_TO_QASM_DIR)/c_to_qasm.c

# Nome dell'eseguibile per il parser da C a QASM
C_TO_QASM_TARGET=CtoQasm

all: $(TARGET) $(PARSER_TARGET) $(C_TO_QASM_TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

$(PARSER_TARGET): $(PARSER_SRC)
	$(CC) $(CFLAGS) -o $(PARSER_TARGET) $(PARSER_SRC) -lm

$(C_TO_QASM_TARGET): $(C_TO_QASM_SRC)
	$(CC) $(CFLAGS) -o $(C_TO_QASM_TARGET) $(C_TO_QASM_SRC) -lm

clean:
	rm -f $(TARGET) $(PARSER_TARGET) $(C_TO_QASM_TARGET)
