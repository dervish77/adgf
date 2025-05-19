; addsub in assembly
; 
; set border color based on result of add or sub calculation
;

doadd := 1						; define for add, or undefine for sub


loop:
.ifdef doadd
		lda #1					
		clc
		adc #12					; compute color via add
.else
		lda #13
		sec
		sbc #5					; compute color via sub
.endif
        sta border              ; store color to BORDER
        jmp loop


border := $d020


