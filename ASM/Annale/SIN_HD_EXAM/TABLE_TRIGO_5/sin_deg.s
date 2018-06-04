; ce programme est pour l'assembleur RealView (Keil)
        thumb
        area  moncode, code, readonly
;
        import  sin_q24
        export  sin_deg

; cette fonction rend le sin d'un angle exprime en milliemes de degre
; ----- format d'entree -----
; l'angle est exprime par un nombre signe t.q. 2pi <==> 360000
; ----- format de sortie -----
; le sinus est rendu en virgule fixe sur 32 bits signes
; en format virgule fixe Q23 ou 9.23

sin_deg proc
        push    {lr}
        lsl     r0, ???
        ldr     r1, =1563749871
        smull   r1, r0, r1, r0
        bl      sin_q24
fin     pop     {pc}
        endp
        end
