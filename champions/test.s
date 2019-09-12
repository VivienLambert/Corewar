.name "Test"

.comment "Zork is my nemesis"

store:
		sti1:	sti		r1, %:live1, %1
		sti2:	sti		r1, %:live2, %1
				sti		r2, %:sti1, %0 #del1
				sti		r2, %:sti2, %0 #del2
				ldi		%:live1, %0, r2
				ldi		%:live1, %4, r3
load:
		ld		%20, r4
		ld		%100, r5
live1:	live	%1
trap:	zjmp	%:live1

fork:	fork	%:store1
loop:	sti		r2, r5, %2
store1:	sti	r3, r5, %0
live2:	live	%1
add		r5, r4, r5
add		r7, r7, r7
zjmp	%:loop
