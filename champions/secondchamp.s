.name		"You fork my tralala"
.comment	"I'm your father"


zjmp			%470
fork			%:secondattack
live			%1
live			%1
#live			%1
live			%1
live			%1
live			%1
live			%1
begin:
		lfirst:	sti r1, %:lf, %1
		lf:		live %1
		l1:		sti r1, %:live, %1
		fork	%:load2
load1:
		ld		%190055683, r2
		ld		%396, r4
		ld		%0, r3
		ld		%190055683, r5
		ld		%376, r7
		live	%1
		add		r10,r10, r10
		zjmp	%:attack
load2:
		ld		%118030707, r2
		ld		%413, r4
		ld		%0, r3
		ld		%118030707, r5
		ld		%380, r7
live:	live	%:live
		live	%1
		sti		r2, r3, r4
		add		r10,r10, r10
		zjmp	%399
attack:
		sti		r2, r3, r4
		add		r10, r10, r10
		zjmp	%386
secondattack:
	store:
		sti1:	sti		r1, %:live1, %1
		sti2:	sti		r1, %:live2, %1
		sti3:	sti		r1, %:live3, %1
				sti		r2, %:sti1, %0 #del1
				sti		r2, %:sti2, %0 #del2
				ldi		%:live1, %0, r2
				ldi		%:live1, %4, r3
	load:
			ld		%30, r4
			ld		%100, r5
			live1:	live	%1
			fork:	fork	%:store1
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
			add		r15, r15, r15
			loop:	sti		r2, r5, %2
			store1:	sti	r3, r5, %0
			live2:	live	%1
			add		r5, r4, r5
			add		r7, r7, r7
			live3:	live	%1
			zjmp	%:loop
