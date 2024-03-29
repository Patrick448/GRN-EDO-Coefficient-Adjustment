#!/bin/bash

BUDGET=1050000
INPUT_FILE="Dados_abcd_TRAIN.txt"
MODEL="abcd"
EXE_PATH="./build/ES"
DIFF="norm_v3"
EXP_NAME="$MODEL-$BUDGET-$DIFF"
SET_DIV=""
TEST_SET="-ts Dados_abcd_TEST.txt"

mkdir $EXP_NAME
./batch_run.sh 4 30 "$EXE_PATH -i $INPUT_FILE $TEST_SET -m $MODEL -e lsoda -a cmaes -n $BUDGET -s \$i $SET_DIV -ro $EXP_NAME/output-$MODEL-cmaes.csv -po $EXP_NAME/progress-$MODEL-cmaes.csv"
./batch_run.sh 4 30 "$EXE_PATH -i $INPUT_FILE $TEST_SET -m $MODEL -e lsoda -a de -n $BUDGET -s \$i $SET_DIV -ro $EXP_NAME/output-$MODEL-de.csv -po $EXP_NAME/progress-$MODEL-de.csv"
./batch_run.sh 4 30 "$EXE_PATH -i $INPUT_FILE $TEST_SET -m $MODEL -e lsoda -a sade -n $BUDGET -s \$i $SET_DIV -ro $EXP_NAME/output-$MODEL-sade.csv -po $EXP_NAME/progress-$MODEL-sade.csv"
./batch_run.sh 4 30 "$EXE_PATH -i $INPUT_FILE $TEST_SET -m $MODEL -e lsoda -a es-i -n $BUDGET -s \$i $SET_DIV -ro $EXP_NAME/output-$MODEL-es-i.csv -po $EXP_NAME/progress-$MODEL-es-i.csv"
./batch_run.sh 4 30 "$EXE_PATH -i $INPUT_FILE $TEST_SET -m $MODEL -e lsoda -a es-ni -n $BUDGET -s \$i $SET_DIV -ro $EXP_NAME/output-$MODEL-es-ni.csv -po $EXP_NAME/progress-$MODEL-es-ni.csv"