#!/bin/bash

#ALGORITHMS="1 3 7 8"
ALGORITHMS="4"
INSTANCES=`ls ./problems/*.atsp`
for ALG in $ALGORITHMS; do
  for INSTANCE in $INSTANCES; do
    echo ${INSTANCE##*/} $ALG
    RESULT=$(./TSP <<< "1 $INSTANCE $ALG 0.9")
    SIZE=`echo "$RESULT" | grep "SIZE:" | sed 's/SIZE: //g'`
    echo $SIZE
    TIMES=`echo "$RESULT" | grep "TIMES:" | sed 's/TIMES: //g'`
    echo $TIMES
    SCORES=`echo "$RESULT" | grep "BEST SCORES:" | sed 's/BEST SCORES: //g'`
    echo $SCORES
  done
done

