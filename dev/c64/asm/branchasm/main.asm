; branchasm in assembly
; 
; set border color based on result of compare calculation
;

red := 2
green := 13

;doit := 1						; define for doing red vs green


loop:
.ifdef doit
		sec
		lda #red					
		sbc #red				; check if color is red
		beq dored
.else
		sec
		lda #green
		sbc #green				; check if color is green
		beq dogreen
.endif

dored:
		lda #red
		jmp setborder			; jump to set border
		
dogreen:
		lda #green
		jmp setborder			; jump to set border

setborder:
        sta border              ; store color to BORDER
        jmp loop


border := $d020


