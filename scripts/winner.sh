#!/bin/bash

#
# Test provided champion (cli arg) against all champions in $CHAMPS_DIR
#

COREWAR_EXE="../corewar"
CHAMPS_DIR="../resources/champs"
LOG_FILE="win.log"

if [ ! -e $COREWAR_EXE ]; then
	make corewar -C ..
fi

if [ -e $LOG_FILE ]; then
	printf "" > $LOG_FILE
fi

CHAMPION_TO_TEST="$1"

if [ "$CHAMPION_TO_TEST" == "" ]; then
	echo "Usage : ./winner.sh [CHAMPION.cor]"; exit 1
elif [ ! -f "$CHAMPION_TO_TEST" ]; then
	echo "'$CHAMPION_TO_TEST' not found"; exit 1
fi

for champ in $CHAMPS_DIR/*.cor ; do
	echo $(basename $champ) >> $LOG_FILE
	$COREWAR_EXE $1 $champ >> $LOG_FILE
	echo "\n==================================\n" >> log
done
