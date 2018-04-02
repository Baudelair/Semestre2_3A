; ce programme est pour l'assembleur RealView (Keil)
	thumb
	area  moncode, code, readonly
	export Temporisation
;
Temporisation	proc
	mov	r2, #0	; 1ere instruction de la fonction (exemple)

	bx	lr	; dernière instruction de la fonction
	endp
;
	end

GPIOB_BSRR	equ	0x40010C10	; Bit Set/Reset register
; mise a 1 de PB1
	ldr	r3, =GPIOB_BSRR
	movs	r1, #0x00000002
	str	r1, [r3]
; mise a zero de PB1
	ldr	r3, =GPIOB_BSRR
	movs	r1, #0x00020000
	str	r1, [r3]