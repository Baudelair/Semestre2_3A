; ce programme est pour l'assembleur RealView (Keil)
        thumb
        area  moncode, code, readonly
;
        import  TabSin
        export sin_pi

pisur2  equ     (1<<8)
pi      equ     (1<<9)

; cette fonction rend le sinus d'un angle compris entre 0 et pi (inclus)
; en utilisant une table construite pour les angles de 0 a pi/2 (inclus)
; ----- format d'entree -----
; l'angle est exprime par un nombre t.q. 2pi <==> 1<<10
; En prenant le tour comme unite d'angle, on peut dire que l'angle
; est exprime en format virgule fixe Q10 ou 22.10  
; ----- format de sortie -----
; le sinus est rendu en virgule fixe sur 32 bits signes
; en format virgule fixe Q23 ou 9.23 

sin_pi  proc
        cmp     r0, #pisur2
        bls     quad1
        rsb     r0, r0, #pi     ; soustraction inversee : r0 = pi - r0
quad1   ldr     r1, =TabSin
        ldr     ???
        bx      lr
        endp

        end