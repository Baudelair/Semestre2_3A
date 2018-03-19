; ce programme est pour l'assembleur RealView (Keil)
	thumb

	area  maram, data, readwrite
	export compteur4

; On a mis la variable en RAM car en ROM c'est du read only memory

compteur4	dcd	0



	area  moncode, code, readonly
	export t4_callback
;
t4_callback	proc
	ldr	r1, =compteur4  ; on effectue un adressage dans la ROM
	ldr	r0, [r1]
	add	r0, #1
	str	r0, [r1]
	bx	lr	; dernière instruction de la fonction
	endp
;
	end