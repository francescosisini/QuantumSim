// Esempio di file QASM
OPENQASM 2.0;
include "qelib1.inc";

// Dichiarazione del registro quantistico
qreg q[3];

// Applicazione della porta Hadamard al qubit 0
h q[0];

// Applicazione della porta CNOT con qubit 0 come controllo e qubit 1 come target
cx q[0],q[1];

// Applicazione della porta X al qubit 2
x q[2];

// Fine del circuito
