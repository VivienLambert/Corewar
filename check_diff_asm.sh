PROJ_ASM="resources/asm"
PROJ_ASM_LOG="proj_asm.log"
MY_ASM="asm"
MY_ASM_LOG="my_asm.log"
if [[ -e $MY_ASM && -e $PROJ_ASM && -e $1 ]];
then
	target="$1"
	target_cor="${target/%.s/.cor}"
	./$PROJ_ASM $target
	hexdump $target_cor > $PROJ_ASM_LOG
	./$MY_ASM $target
	hexdump $target_cor > $MY_ASM_LOG
	diff $PROJ_ASM_LOG $MY_ASM_LOG
fi
