; ce programme est pour l'assembleur RealView (Keil)
	include Lib\etat.inc
	;include bruitverre.asm
	thumb

	area  maram, data, readwrite
	import TabSin
	import TabCos
	import LeSignal
	
RAM
	dcd	0x20004000	; stack en fin de la zone de 20k de RAM
	
	area  moncode, code, readonly	
	export test
	export reelle
		
test proc 

	ldr r1,=TabSin
	ldrsh r1,[r1,r0,lsl #1]
	ldr r2,=TabCos
	ldrsh r2,[r2,r0,lsl #1]
	mov r3, #0	
	MLA r1,r1,r1,r3
	MLA r0,r2,r2,r1
		
	bx lr	
	endp
	

	
reelle proc
	
	;r0 = l'adresse du signal
	;r1 = la valeur de i
	;r2 = l'adresse de la tab de COS/SIN
	push {lr}
	mov r4,#0; notre k, on parcourt a l envers  F
	mov r3,#0; ;r3 est la somme F
	mov r7, r1
	;r5 sert a stocker sig, r6 cos
	
	
debut	
	
	

	ldrsh r5,[r0,r4, lsl #1];chargement signal F
	mul r6,r4,r7; multiplie i par k F
	and r6,r6,#0x3F;modulo 64 (#63)de r6 F
	ldrsh r6,[r2,r6, lsl #1];chargement cos/sin F
	mul r5,r5,r6; multiplie cos/sin et signal 
	add r3,r3,r5; ajoute au total
	
	
	add r4,#1;
	cmp r4,#64 
	IT NE ;if not equal then...
	BNE debut; on va au debut
	
	mov r4, r7 ; restaurer la valeur de i
	mov r0,r3; on met resultat en r0 pour envoi
	pop {pc}
	
	bx lr
	endp
	end
	
	
	
		
	
	
	

	
	
	
	
	
	
	; if signal 1 = 0, passe a 1 et envoie a GPIO_BSRR, sinon 0 et envoie
	
	;ldr r1, =signal1 	; r1 adresse de signal1
	;ldr r2, [r1]		; r5 valeur de signal1
	
	
		;CBZ r2 , misea1
		
			;push {r1,r2}
			;; mise a zero de PB1
			;ldr	r3, =GPIOB_BSRR
			;movs	r1, #0x00020000
			;str	r1, [r3]
			
			;pop {r1,r2}
			;mov	r2 , #0		;signal a 0
			;str r2, [r1]
			;b lafin
;misea1
			;push {r1,r2}
			;; mise a 1 de PB1
			;ldr	r3, =GPIOB_BSRR
			;movs	r1, #0x00000002
			;str	r1, [r3]	

			;pop {r1,r2}
			;mov	r2 , #1		;signal a 1
			;str r2, [r1]

;lafin
	;bx lr
	;endp
	;end
;; mise a 1 de PB1
;;	ldr	r3, =GPIOB_BSRR
;;	movs	r1, #0x00000002
;;	str	r1, [r3]
;; mise a zero de PB1
;;	ldr	r3, =GPIOB_BSRR
;;	movs	r1, #0x00020000
;;	str	r1, [r3]
;;	end 			
				

	
