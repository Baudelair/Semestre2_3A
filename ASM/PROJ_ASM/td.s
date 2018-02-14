	thumb
	area	reset, data, readonly	;déclaration zone mémoire (RAM/ROM) /readonly -> stockage dans la ROM
	export __Vectors
__Vectors
	dcd	0x20004000	; stack en fin de la zone de 20k de RAM
	dcd	Reset_Handler	; point d'entree de notre programme / réservation de donnée en mémoire
;
	area	moncode, code, readonly
;
; procedure principale
;
	export	Reset_Handler
Reset_Handler proc

boo     mov 	r1, #1
	mov 	r2, #100
	add	r2, r1
	b       boo
	endp ; indique la fin de procédure pour le débuggueur, aucun effet sur le programme
;
	end ; fin du texte (aucun effet sur le code)