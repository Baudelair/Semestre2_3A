; ce programme est pour l'assembleur RealView (Keil)
	include Lib\etat.inc
	thumb

	area  maram, data, readwrite
	import TabSin
	import TabCos
	import LeSignal
	import Somme
	
	
RAM
	dcd	0x20004000	; stack en fin de la zone de 20k de RAM
	
	area  moncode, code, readonly	
	export M2
		
M2 proc 
	;r0 = adresse du signal
	;r1 = valeur de i 
	push {lr}
	ldr r2, TabCos
	push {r1}
	bl Somme
	mov r3, #0	
	MLA r4,r0,r0,r3 ; carre de COS (MLA => r4 = r0*r0 +r3
	ldr r2, TabSin
	pop {r1}
	push {r1}
	bl Somme
	MLA r5,r0,r0,r3 ; carre de SIN (MLA => r4 = r0*r0 +r3
	pop {r1}
	add r0, r4, r5
	
	pop {pc}
	bx lr
	endp
	end