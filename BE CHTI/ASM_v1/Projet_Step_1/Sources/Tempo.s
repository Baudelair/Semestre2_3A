; ce programme est pour l'assembleur RealView (Keil)
	include Lib\etat.inc
	;include bruitverre.asm
	thumb

	area  maram, data, readwrite
signal1 dcd 0
	

	export	Temporisation
	export	timer_callback
	import	etat
	import	LongueurSon 
	import	PeriodeSonMicroSec
	import	Son
	
	area  moncode, code, readonly	
	
	ldr	r0,=etat
	ldr r1,=LongueurSon
	str	r1 , [r0, #E_TAI]
	ldr r1,=Son
	str	r1,[r0, #E_SON]
	
DECALAGE	equ 32768;	
GPIOB_BSRR	equ	0x40010C10	; Bit Set/Reset register
TIM3_CCR3	equ	0x4000043C	; adresse registre PWM

	
Temporisation	proc
	mov	r2, #0	; 1ere instruction de la fonction (exemple)

	bx	lr	; dernière instruction de la fonction
	endp
	
	
timer_callback proc
	
	ldr	r0,=etat	
	;///RECUPERATION SON
	ldr r2, [r0,#E_POS] ; chargement de ce qu'il y a a adresse pos dans r2// r2=etat.pos
	ldr r3,[r0,#E_SON]; adresse de *son = etat.son
	;ldr r3,[r3];adresse de son[0]
	ldrsh r1,[r3,r2]; chargement du son a la pos son[0] + r2 (pos)
	
	;///DECALAGE

	add r1,#32768; decalage du son 
	
	;///multiplication par res
	
	ldr r3, [r0,#E_RES];
	mul r1, r3
	
	;///on divise par 65536 = 2^16
	mov r1,r1 ,LSL #16
	
	ldr r3,=TIM3_CCR3
	str r1, [r3]
	; reste a BALANCER DANS PWM
	;A CHAQUE INTERRUPTION ON PASSE A LA LIGNE SUIVANTE DU FICHIER AUDIO
	
	ldr r2, [r0,#E_POS] ; chargement de ce qu'il y a a adresse pos dans r2// r2=etat.pos
	add r2, #2
	str r2, [r0,#E_POS]; renvoie dans la structure pos + 2
	
	bx lr 
	endp
	
	//TRAITER CAS FIN
	
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
				

	
