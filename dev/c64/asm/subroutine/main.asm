; subroutine in assembly
; 
; set border color via subroutines
;

red := 2
green := 13

doit := 1						; define for doing red vs green


; main program 
loop:
		jsr set_color
		jsr set_border
		jmp loop


; subroutine to select color
set_color:
.ifdef doit
		lda #red				; use color as red	
.else
		lda #green				; use color as green
.endif
		rts


; subroutine to set border to selected color
set_border:
        sta border              ; store color to BORDER
        rts


border := $d020


