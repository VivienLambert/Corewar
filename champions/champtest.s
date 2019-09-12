.name	"Better than zork"

.comment "Zork is my nemesis"

begin:
		lfirst:	sti r1, %:lf, %1
		lf:		live	%1
		l1:		sti r1, %:live, %1
		fork	%:zork
		add		r8, r8, r8
		zjmp	%:load
		zjmp	%500
zork:
		lzork:		sti r1, %:live2, %1
		live2:		live	%1
		live		%1
		live		%1
		live		%1
		live		%1
		live		%1
		add			r7, r7, r7
		st			r3, r9
		zjmp		%:live2
load:
		ld		%190055173, r2
		ld		%1048039719057, r3
		ld		%154, r5
		fork	%:secondpart
		live	%1
live:	live	%1
		sti		r3, %157, r4
		ld		%150, r4

secondpart:
			sti		r2, %140, r4
			add		r6, r6,r6
			zjmp	%129
