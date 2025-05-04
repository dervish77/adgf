; acid prog in assembly
; 
; effectively toggles border color between 0 and 1
;

BW := 1						; define for B&W vs color

        ldx startColor          ; load 0 to X
loop:
.ifdef BW
        stx border              ; store X to BORDER
.endif
        inc border              ; increase BORDER
        jmp loop

startColor := 0

border := $d020
