#!/bin/bash

ALGORITHMS="3 7 8"
INSTANCES=`ls ../cpp/problems/br*.atsp`
for ALG in $ALGORITHMS; do
  for INSTANCE in $INSTANCES; do
    echo $INSTANCE $ALG
    RESULT=$(./TSP <<< "1 $INSTANCE $ALG")
    TIMES=`echo "$RESULT" | grep "TIMES:" | sed 's/TIMES: //g'`
    echo $TIMES
    SCORES=`echo "$RESULT" | grep "BEST SCORES:" | sed 's/BEST SCORES: //g'`
    echo $SCORES
  done
done

