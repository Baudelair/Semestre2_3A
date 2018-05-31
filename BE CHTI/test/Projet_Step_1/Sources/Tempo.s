; ce programme est pour l'assembleur RealView (Keil)
	include Lib\etat.inc
	;include bruitverre.asm
	thumb

	area  maram, data, readwrite
	import TabSin
	import TabCos

	

	
	area  moncode, code, readonly	
	export test

		
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
				

	
