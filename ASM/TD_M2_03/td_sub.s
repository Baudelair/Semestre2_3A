; ce programme est pour l'assembleur RealView (Keil)
	thumb
	area  moncode, code, readonly
	export subtest
;
subtest	proc
	push	{lr}
	push	{r0}
	ldr	r0, [r0]
	bl	subtest2
	pop	{r2}
	; jai le cube de i dans r0
	; ladr de la struct dans r2
	; je dois récupérer j
	ldr r1, [r2, #4]
	add	r1, r0
	str	r1, [r2, #4]
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