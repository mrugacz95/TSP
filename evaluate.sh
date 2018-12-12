#!/bin/bash

#ALGORITHMS="1 3 7 8"
ALGORITHMS="9"
INSTANCES=`ls ./data/*.atsp`
for ALG in $ALGORITHMS; do
  for INSTANCE in $INSTANCES; do
    echo ${INSTANCE##*/} $ALG
    RESULT=$(./cmake-build-release/TSP <<< "1 $INSTANCE ./output 0 $ALG 100 5")
    SIZE=`echo "$RESULT" | grep "SIZE:" | sed 's/SIZE: //g'`
    echo $SIZE
    TIMES=`echo "$RESULT" | grep "TIMES:" | sed 's/TIMES: //g'`
    echo $TIMES
    SCORES=`echo "$RESULT" | grep "BEST SCORES:" | sed 's/BEST SCORES: //g'`
    echo $SCORES
  done
done

