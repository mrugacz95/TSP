#!/bin/bash

ALGORITHMS="7"
INSTANCES=`ls ./problems/*.atsp`
#INSTANCES="br17.atsp ftv33.atsp ftv35.atsp ftv38.atsp ftv44.atsp ftv47.atsp ftv55.atsp ftv64.atsp ftv70.atsp ft53.atsp p43.atsp ry48p.atsp"
#INSTANCES="p43.atsp ry48p.atsp" # ciekawe
for ALG in $ALGORITHMS; do
  for INSTANCE in $INSTANCES; do
    echo ${INSTANCE##*/} $ALG
    RESULT=$(./TSP <<< "1 $INSTANCE $ALG")
    #RESULT=$(./TSP <<< "1 ./problems/$INSTANCE $ALG")
    SIZE=`echo "$RESULT" | grep "SIZE:" | sed 's/SIZE: //g'`
    echo $SIZE
    FS=`echo "$RESULT" | grep "FIRST SCORES:" | sed 's/FIRST SCORES: //g'`
    echo $FS
    BS=`echo "$RESULT" | grep "BEST SCORES:" | sed 's/BEST SCORES: //g'`
    echo $BS
  done
done

