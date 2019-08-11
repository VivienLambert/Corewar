.name "Write on instruction"
.comment "Test vm behavior if an instruction opcode is overwritten while process is waiting"

	live %0
	ld %200, r1
	fork %:test
write_on_fork:
	fork %:write_on_fork
	zjmp %:write_on_fork

test:
	sti r1,%:write_on_fork,%0
