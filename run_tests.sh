#!/bin/bash

# Imposta un flag per verificare se qualche test fallisce
TEST_FAILED=0

# Funzione per eseguire un singolo test e mostrare i risultati
run_test() {
    local executable=$1
    echo "Eseguendo test per $executable..."
    
    if ./$executable; then
        echo "✅ Test per $executable completati con successo."
    else
        echo "❌ Test per $executable falliti."
        TEST_FAILED=1
    fi
}

# Esegui i test per QuantumSim
run_test "QuantumSim"

# Esegui i test per QasmParser
run_test "QasmParser"

# Esegui i test per CtoQasm
run_test "CtoQasm"

# Mostra un riepilogo finale
if [ $TEST_FAILED -eq 0 ]; then
    echo "✅ Tutti i test sono stati eseguiti con successo!"
    exit 0
else
    echo "❌ Alcuni test sono falliti. Verificare i dettagli sopra."
    exit 1
fi
