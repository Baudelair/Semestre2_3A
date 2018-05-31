; ce programme est pour l'assembleur RealView (Keil)
	include Lib\etat.inc
	thumb

	area  maram, data, readwrite
	import TabSin
	import TabCos
	import LeSignal
	
RAM
	dcd	0x20004000	; stack en fin de la zone de 20k de RAM
	
	area  moncode, code, readonly	
	export Somme
		
	
Somme proc
	
	;r0 = l'adresse du signal
	;r1 = la valeur de i
	;r2 = l'adresse de la tab de COS/SIN
	push {lr}
	mov r4,#0; notre i, on parcourt a l envers  
	mov r3,#0; ;r3 est la somme 
	mov r7, r1
	;r5 sert a stocker sig, r6 cos/sin
	
	
debut	
	
	

	ldrsh r5,[r0,r4, lsl #1];chargement signal 
	mul r6,r4,r7; multiplie i par k 
	and r6,r6,#0x3F;modulo 64 (#63)de r6 
	ldrsh r6,[r2,r6, lsl #1];chargement cos/sin 
	mul r5,r5,r6; multiplie cos/sin et signal 
	add r3,r3,r5; ajoute au total
	
	
	add r4,#1;
	cmp r4,#64 
	IT NE ;if not equal then...
	BNE debut; on va au debut
	
	mov r4, r7 ; restaurer la valeur de k
	mov r0,r3; on met resultat en r0 pour envoi
	pop {pc}
	
	bx lr
	endp
	end
	
	
	
		
	
	
	

	
	
