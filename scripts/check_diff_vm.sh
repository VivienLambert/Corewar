#!/bin/bash

readonly GREEN="\e[92m"
readonly RED="\e[31m"
readonly CLR="\e[0;m"

ZAZ_VM="../resources/corewar"
MY_VM="../corewar"
ZAZ_ASM="../resources/asm"
CYCLE_TO_CHECK=""
DIFFS_FILE="vm_diffs.log"
NBR_OF_CHAMPS=1
CHAMPS_DIR="../resources/test_champs"

function record_diff
{
	printf "#################################################################\n" >> $DIFFS_FILE
	printf "%s\nCYCLE %d\n" "$champs_names" $dump_cycle >> $DIFFS_FILE
	diff <(echo "$zaz_out") <(echo "$my_out") >> $DIFFS_FILE
}

function get_last_cycle
{
	dump_cycle="$($ZAZ_VM -v 2 $champs_to_run 2> /dev/null | tail -n 3 | grep 'It is now cycle' | awk 'NF>1{print $NF}' | tail -1)"
	((dump_cycle-=1))
}

function check_diff_for_dump
{
	champs_names="$p1_name $p2_name $p3_name $p4_name"
	champs_to_run="$PLAYER_1 $PLAYER_2 $PLAYER_3 $PLAYER_4"
	if [ "$CYCLE_TO_CHECK" == "" ]; then
		get_last_cycle
	fi
	my_out="$($MY_VM -dump $dump_cycle $champs_to_run 2> /dev/null | awk '$1 ~ /^0x/')"
	zaz_out="$($ZAZ_VM -d $dump_cycle $champs_to_run 2> /dev/null | awk '$1 ~ /^0x/')"
	printf "%-100s : [%d] " "$champs_names" $dump_cycle
	if [ "$zaz_out" != "" ] && [ "$zaz_out" != "$my_out" ]; then
		printf "${RED}%s\n${CLR}" "DIFFERS"
		record_diff
	elif [ "$zaz_out" == "" ]; then
		printf "${RED}%s\n${CLR}" "CYCLE TOO HIGH"
	else
		printf "${GREEN}%s\n${CLR}" "OK"
	fi;
}

function compile_champs
{
	if [ ! -d $CHAMPS_DIR ]; then
		mkdir $CHAMPS_DIR
	fi
	echo "Compiling champions..."
	for champ in $CHAMPS_DIR/*.s; do
		if [ "$(basename $champ)" != "Car.s" ] && [ "$(basename $champ)" != "mandragore.s" ]; then
			compiled_champ="${champ/%.s/.cor}"
			$ZAZ_ASM $champ > /dev/null 2>&1
		fi
	done
	echo "Champions compiled !"
}

function set_target_champ
{
	target_champ=$1
	if [ "$target_champ" == "1" ]; then
		PLAYER_1="$champ"
		p1_name="$(basename $PLAYER_1)"
	elif [ "$target_champ" == "2" ]; then
		PLAYER_2="$champ"
		p2_name="$(basename $PLAYER_2)"
	elif [ "$target_champ" == "3" ]; then
		PLAYER_3="$champ"
		p3_name="$(basename $PLAYER_3)"
	elif [ "$target_champ" == "4" ]; then
		PLAYER_4="$champ"
		p4_name="$(basename $PLAYER_4)"
	fi
}

function loop_over_champions
{
	loop=$((loop+1))
	for champ in $CHAMPS_DIR/*.cor; do
		set_target_champ $loop
		if [[ $loop -lt $NBR_OF_CHAMPS ]]; then
			loop_over_champions
		else
			check_diff_for_dump
		fi
	done
	loop=$((loop-1))
}

function print_usage
{
	echo "USAGE : ./vm_checker [ -c CYCLE_TO_CHECK ] [ -n NBR_OF_CHAMPIONS]
	NBR_OF_CHAMPIONS is set to 1 by default
	CYCLE_TO_CHECK is set to MAX by default"
}

function get_options
{
	while getopts ":c:n:" opt; do
		case ${opt} in
			c) # Set cycle to be checked
				CYCLE_TO_CHECK=$OPTARG
				printf "Cycle to check set to : %d\n" $CYCLE_TO_CHECK
				;;
			n) # Set number of champions to check (n >= 1 && n <= 4)
				NBR_OF_CHAMPS=$OPTARG
				if (( $NBR_OF_CHAMPS >= 1 )) && (( $NBR_OF_CHAMPS <= 4 )); then
					printf "Number of champions set to : %d\n" $NBR_OF_CHAMPS
				else
					echo "Invalid number of champs"
					exit 1
				fi
				;;
			\?)
				echo "Invalid option"
				print_usage
				exit 1
		esac
	done
}

# Clean up the log file before running the script
printf "" > $DIFFS_FILE

# Parse command line options (-n, -c)
get_options $@

dump_cycle=$CYCLE_TO_CHECK

# Use provided asm to compile champions (.s -> .cor)
compile_champs

# Run the checker
loop_over_champions 1
