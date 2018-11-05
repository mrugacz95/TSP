#!/bin/bash

ALGORITHMS="7 8"
INSTANCES=`ls ./problems/*.atsp`
for ALG in $ALGORITHMS; do
  for INSTANCE in $INSTANCES; do
    echo ${INSTANCE##*/} $ALG
    RESULT=$(./TSP <<< "1 $INSTANCE $ALG")
    SIZE=`echo "$RESULT" | grep "SIZE:" | sed 's/SIZE: //g'`
    echo $SIZE
    DELTAS=`echo "$RESULT" | grep "DELTAS:" | sed 's/DELTAS: //g'`
    echo $DELTAS
    JUMPS=`echo "$RESULT" | grep "JUMPS:" | sed 's/JUMPS: //g'`
    echo $JUMPS
  done
done

