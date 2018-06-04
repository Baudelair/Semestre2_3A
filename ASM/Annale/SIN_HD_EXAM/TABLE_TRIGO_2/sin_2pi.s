; ce programme est pour l'assembleur RealView (Keil)
        thumb
        area  moncode, code, readonly
;
        import  sin_pi
        export  sin_2pi

pi      equ     (1<<9)

; cette fonction rend le sin d'un angle compris entre 0 et 2pi (inclus) 
; ----- format d'entree -----
; l'angle est exprime par un nombre t.q. 2pi <==> 1<<10
; En prenant le tour comme unite d'angle, on peut dire que l'angle
; est exprime en format virgule fixe Q10 ou 22.10  
; ----- format de sortie -----
; le sinus est rendu en virgule fixe sur 32 bits signes
; en format virgule fixe Q23 ou 9.23 

sin_2pi proc
        push    {lr}
        cmp     r0, #pi
        ???     quad34
        bl      sin_pi
        b       fin
;
quad34  sub     r0, #pi
        bl      sin_pi
        rsb     r0, r0, #0
fin     pop     {pc}
        endp
        end