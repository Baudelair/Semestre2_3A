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
	;r1 = valeur de k
	push{lr}
	push {r4-r6}
	ldr r2, =TabCos		;on récupére l'adresse de cos
	push {r1,r0}		;on empile la valeur de k et l'adresse du signal, afin de les sauvegarder
	bl Somme			;on calcul la partie réelle et l'addresse du signal	
	SMULL r3,r4,r0,r0 	; carre de COS (MLA => r3,r4 = r0*r0 
	ldr r2, =TabSin		;on récupére l'adresse de sin
	pop {r0, r1}		;on récupére la valeur de k et l'adresse du signal, k modifié dans Somme et r0 modifié par le res de somme
	push {r1, r3, r4}		;on empile la valeur de k 
	bl Somme
	SMULL r5,r6,r0,r0 	; carre de SIN (MLA => r4 = r0*r0
	pop {r1,r3,r4}		;on récupére la valeur de k 
	add r0, r4, r6		; on fait la somme des deux carrés
	pop {r4-r6}			;on récupére l'adresse de pc afin de retourner dans la boucle de principal.c
	pop{pc}
	endp
	end