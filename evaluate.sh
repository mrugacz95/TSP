#!/bin/bash

ALGORITHMS="1 7 8"
INSTANCES=`ls ../cpp/selected_problems/*.atsp`
for ALG in $ALGORITHMS; do
  for INSTANCE in $INSTANCES; do
    echo ${INSTANCE##*/} $ALG
    RESULT=$(./TSP <<< "1 $INSTANCE $ALG")
    SIZE=`echo "$RESULT" | grep "SIZE:" | sed 's/SIZE: //g'`
    echo $SIZE
    TIMES=`echo "$RESULT" | grep "TIMES:" | sed 's/TIMES: //g'`
    echo $TIMES
    SCORES=`echo "$RESULT" | grep "BEST SCORES:" | sed 's/BEST SCORES: //g'`
    echo $SCORES
  done
done

