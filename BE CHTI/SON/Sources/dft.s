; ce programme est pour l'assembleur RealView (Keil)
	thumb
	area  moncode, code, readonly
	export DFT
	import TabCos
	import TabSin
	import dma_buf
		
DFT	proc
	; on a k dans r0
	push	{r4-r11}
	
	ldr	r2, =TabCos
	ldr	r3, =TabSin
	ldr	r4, =dma_buf
	mov	r5, #0			; som re_k
	mov	r6, #0			; som im_k
	mov	r7, #0			; index dft à 0 (i)
som_i	ldrsh	r8, [r4, r7, lsl #1]	; valeur du signal 1.12
	mov	r9, r7			; copie la valeur de i
	mul	r9, r0			; k * i
	and	r9, r9, #0x3F		; modulo 64 -> index cos/sin
	
re_k	ldrsh	r10, [r2, r9, lsl #1]	; cos(ik..) 1.15
	mul	r10, r8			; cos() * x(i) 2.27
	asr	r10, #11		; 2.16
im_k	ldrsh	r11, [r3, r9, lsl #1]	; sin(ik..) 1.15
	mul	r11, r8			; sin() * x(i) 2.27
	asr	r11, #11		; 2.16
	
	add	r5, r10			; 7.16 -> re_k
	add	r6, r11			; 7.16 -> -im_k
	
	add	r7, r7, #1		; on incrémente i
	cmp	r7, #63			; on boucle -> 63 (64 valeurs sig)
	bls	som_i

m2_k	smull	r1, r0, r5, r5		; r0:r1 14.32
	smlal	r1, r0, r6, r6		; r0:r1 15.32 -> r0 15.0
		
	pop	{r4-r11}
	
	bx	lr
	endp
		
	end