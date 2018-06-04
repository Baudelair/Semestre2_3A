; ce programme est pour l'assembleur RealView (Keil)
        thumb
        area  moncode, code, readonly
;
        import  sin_q10
        export  sin_q24

; cette fonction rend le sinus d'un angle arbitraire, positif ou negatif,
; en effectuant une interpolation lineaire entre deux valeurs consecutives
; fournies par la fonction sin_q10
; ----- format d'entree -----
; l'angle est exprime par un nombre t.q. 2pi <==> 1<<24
; En prenant le tour comme unite d'angle, on peut dire que l'angle
; est exprime en format virgule fixe Q24 ou 8.24 
; ----- format de sortie -----
; le sinus est rendu en virgule fixe sur 32 bits signes
; en format virgule fixe Q23 ou 9.23 
 
sin_q24 proc
        push    {lr}
        ldr     r1, =0x03FFF
        and     r1, r0, r1
        push    {r1}            ; sauver les 14 LSBs
        asr     r0, #14
        push    {r0}            ; sauver angle Q10
        add     r0, #1
        bl      sin_q10         ; chercher le second sinus
        mov     r2, r0
        pop     ???
        push    ???
        bl      sin_q10         ; chercher le premier sinus
        pop     {r2}            ; recuperer le second sinus
        sub     r2, r2, r0      ; la difference
        pop     {r1}            ; recuperer les 14 LSBs
        mul     r1, r1, r2      ; multiplier par la diff des sinus
        asr     r1, #14         ; diviser
        add     r0, r1          ; ajouter au premier sinus
fin     pop     {pc}
        endp
        end