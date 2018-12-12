#!/bin/bash

ALGORITHMS="4"
INSTANCES=`ls ./data/*.atsp`
for ALG in $ALGORITHMS; do
  for INSTANCE in $INSTANCES; do
    echo ${INSTANCE##*/} $ALG
    RESULT=$(./cmake-build-release/TSP <<< "1 $INSTANCE ./output 422 $ALG 0.94")
    SIZE=`echo "$RESULT" | grep "SIZE:" | sed 's/SIZE: //g'`
    echo $SIZE
    DELTAS=`echo "$RESULT" | grep "DELTAS:" | sed 's/DELTAS: //g'`
    echo $DELTAS
    JUMPS=`echo "$RESULT" | grep "JUMPS:" | sed 's/JUMPS: //g'`
    echo $JUMPS
  done
done

