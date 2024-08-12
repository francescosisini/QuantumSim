OPENQASM 2.0;
include "qelib1.inc";
gate nG0 ( param ) q1, q2  {
//***f(q1) ccostante***
//id q1;
//x q2;
//***f(q1) NON-ccostante***
cx q1,q2;
}

qreg q[2];
creg c[1];

id q[0];
x q[1];
h q[0];
h q[1];
//oracolo
cx q1,q2;

h q[0];
measure q[0] -> c[0];