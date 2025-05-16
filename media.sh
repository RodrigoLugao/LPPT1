#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Uso: $0 <num_repeticoes> <nome_do_programa> [argumentos_do_programa]"
    exit 1
fi

N=$1
shift
PROGRAMA=$1
shift
ARGUMENTOS="$@"

SUM=0

for i in $(seq 1 $N); do
    TIME=$(mpirun -np 4 ./$PROGRAMA $ARGUMENTOS | tail -1 | awk '{print $NF}')
    echo "Run $i: $TIME segundos"
    SUM=$(awk "BEGIN {print $SUM + $TIME}")
done

AVG=$(awk "BEGIN {print $SUM / $N}")
echo "Tempo médio em $N execuções: $AVG segundos"
