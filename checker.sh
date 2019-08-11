#!/bin/sh
#
# Script checking differences between user created asm and vm
# against project's provided asm and vm
#

# COLORS :

readonly GREEN="\e[92m"
readonly RED="\e[31m"
readonly CLR="\e[0;m"

# GLOBAL VARIABLES :

RESOURCES_DIR="resources"
CHAMPS_DIR="$RESOURCES_DIR/champs"
ASM_NAME="asm"
ASM_EXT="s"
VM_NAME="corewar"
VM_EXT="cor"
OUT_DIR="checker_output"
ASM_LOG_FILE="$OUT_DIR/asm_diff.log"
HEX_OUT_DIR="$OUT_DIR/hex_out"

# Cleanup temporary files if CTRL-C is pressed
trap trap_ctrl_c INT
function trap_ctrl_c()
{
	rm -f $OUT_DIR/$target_output $OUT_DIR/$my_target_output && exit

}

function process_target()
{
	# Run asm, return if error
	`./$my_asm $CHAMPS_DIR/$target_input > /dev/null`
	if [[ "$?" != "0" ]]; then printf "${RED}%s\n${CLR}" "ERROR"; return; fi
	mv $CHAMPS_DIR/$target_output $OUT_DIR/$my_target_output # move output file

	# Run provided asm, return if error
	`./$provided_asm $CHAMPS_DIR/$target_input > /dev/null`
	if [[ "$?" != "0" ]]; then printf "${RED}%s\n${CLR}" "ERROR"; return; fi
	mv $CHAMPS_DIR/$target_output $OUT_DIR/$target_output # move output file


	if [[ ! -d $HEX_OUT_DIR ]]; then mkdir $HEX_OUT_DIR; fi

	xxd $OUT_DIR/$target_output > $asm_hex_out
	xxd $OUT_DIR/$my_target_output > $my_asm_hex_out

	if [[ $(diff $asm_hex_out $my_asm_hex_out) != "" ]]; then
		printf "${RED}%s\n${CLR}" "DIFFERS"
	else
		printf "${GREEN}OK\n${CLR}"
	fi
}

if [[ ! -d $OUT_DIR ]]; then
	mkdir $OUT_DIR
fi

if [[ ! -e $ASM_NAME ]]; then
	make
fi

if [[ -e $HEX_OUT_DIR ]]; then
	rm -rf $HEX_OUT_DIR # Remove previous tests
fi

mkdir $HEX_OUT_DIR
printf "" > $ASM_LOG_FILE # Clear previous logs from file

my_asm="$ASM_NAME"
provided_asm="$RESOURCES_DIR/$ASM_NAME"

for f in $CHAMPS_DIR/*.s;
do
	target=$(basename $f | sed 's/\.s//') # Strip filename of its path and .s
	target_input="$target.$ASM_EXT"
	target_output="$target.$VM_EXT"
	my_target_output="$target_output.mine"
	asm_hex_out="$HEX_OUT_DIR/$target_output.hex"
	my_asm_hex_out="$HEX_OUT_DIR/$my_target_output.hex"

	result="`process_target`"

	printf "%-30s: %s" "$target_output" "$result" | tee -a $ASM_LOG_FILE

	rm -f $OUT_DIR/$target_output $OUT_DIR/$my_target_output # Remove tmp files
done

