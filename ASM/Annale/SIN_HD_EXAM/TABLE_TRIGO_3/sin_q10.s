; ce programme est pour l'assembleur RealView (Keil)
        thumb
        area  moncode, code, readonly
;
        import  sin_2pi
        export  sin_q10

pix2    equ     (1<<10)

; cette fonction rend le sinus d'un angle arbitraire, positif ou negatif
; ----- format d'entree -----
; l'angle est exprime par un nombre t.q. 2pi <==> 1<<10
; En prenant le tour comme unite d'angle, on peut dire que l'angle
; est exprime en format virgule fixe Q10 ou 22.10  
; ----- format de sortie -----
; le sinus est rendu en virgule fixe sur 32 bits signes
; en format virgule fixe Q23 ou 9.23 

sin_q10 proc
        push    {lr}
        mov     r1, #(pix2-1)
        ???     ???
        bl      sin_2pi
fin     pop     {pc}
        endp
        end