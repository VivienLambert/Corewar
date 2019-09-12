.name	"Corruption"

.comment "Pour la horde"

live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1
live	%1

fork %:secondattack
begin:
	lfirst:	sti r1, %:lf, %1
	lf:		live %1
	l1:		sti r1, %:live, %1

firstattack:
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	live	%1
	ld	%190055683, r2
	ld	%269025285, r3
	ld %72617232, r8
	ld %269025280, r9
	ld	%500, r5
	loop:
		sti r8, %0, %-217
		sti r9, %0, %-220
		live: live %1
		sti	r2, %2, r5
		sti r3, %0, r5
		add r5, r5, r5
		add	r15, r15, r15
		zjmp %:loop

secondattack:
		here:	sti r1, %:bouh, %1
		live	%1
		live	%1
		live	%1
		bouh:	live	%1
		fork	%:load
		ld		%190055683, r5
		ld		%0, r3
		ld		%10, r16
		add	r15, r15, r15
		live	%1
		zjmp	%416
	load:
		ld		%268500992, r5
		ld		%0, r3
		ld		%14, r16
		add	r15, r15, r15
		live %1
		zjmp	%382
