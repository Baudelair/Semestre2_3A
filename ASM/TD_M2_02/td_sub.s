; ce programme est pour l'assembleur RealView (Keil)
	thumb
	area  moncode, code, readonly
	export subtest
;
subtest	proc
	push	{lr}
	bl	subtest2
	;j'ai le cube de i dans r0 et l'adresse de j dans r1
	ldr	r2, [r1]
	;add de r0 qui a la valeur du cube
	add	r2, r0 
	;
	str 	r2, [r1]
	pop	{pc}
	endp
;

; rend le cube sur 32 bits
subtest2	proc
	mul	r3, r0, r0
	mul	r0, r3, r0
	bx	lr
	endp
	end