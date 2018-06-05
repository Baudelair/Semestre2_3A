; ce programme est pour l'assembleur RealView (Keil)
	thumb
	area  moncode, code, readonly
	export NextValue
	;export PwmTick
	import etat
	include etat.inc
;
GPIOB_BSRR	equ	0x40010C10	; Bit Set/Reset register
TIM3_CCR3	equ	0x4000043C	; adresse registre PWM
	
NextValue	proc
	push	{r4-r8}
	ldr	r0, =etat		;on lit etat
	ldr	r1, [r0, #E_POS]	;on lit l'index du tableau
	ldr	r2, [r0, #E_TAI]
	cmp	r2, r1			;on vérifie qu'on est pas à la fin du son
	beq	Exit
	ldr	r3, [r0, #E_SON]	;on lit l'adresse du Son
	ldr	r4, [r0, #E_RES]
	ldrsh	r6, [r3, r1, lsl #1]	;on lit la valeur du tableau
	add	r6, #32768		;ajoute 2*15
	mul	r7, r6, r4		; * res	
	lsr	r7, #16			; /2**16
	ldr	r8, =TIM3_CCR3		;on envoie la valeur
	str	r7, [r8]
	add	r1, r1, #1		;incrémente l'index
	str	r1, [r0, #E_POS]
;			
Exit
	pop	{r4-r8}
	bx	lr
;	
	endp
;
	end
