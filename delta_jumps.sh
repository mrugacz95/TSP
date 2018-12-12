#!/bin/bash

ALGORITHMS="9"
INSTANCES=`ls ./data/*.atsp`
for ALG in $ALGORITHMS; do
  for INSTANCE in $INSTANCES; do
    echo ${INSTANCE##*/} $ALG
    RESULT=$(./cmake-build-release/TSP <<< "1 $INSTANCE ./output $RANDOM $ALG 1000 ")
    SIZE=`echo "$RESULT" | grep "SIZE:" | sed 's/SIZE: //g'`
    echo $SIZE
    DELTAS=`echo "$RESULT" | grep "DELTAS:" | sed 's/DELTAS: //g'`
    echo $DELTAS
    JUMPS=`echo "$RESULT" | grep "JUMPS:" | sed 's/JUMPS: //g'`
    echo $JUMPS
  done
done

