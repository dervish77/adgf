; use hex to output add result in assembly
;

.import outhex
.import outbcd

; main program
start:  jsr outstr1				; output hex text string
		lda #10					; add two numbers 
		clc
		adc #12
		jsr outhex				; output result of sum as hex
;
		lda #$0a				; output CR
		jsr $ffd2
		lda #$0d				; output LF
		jsr $ffd2
;
		jsr outstr2				; output bcd text string
		sed
		lda #10					; add two numbers 
		clc
		adc #12
		jsr outbcd				; output result of sum as hex
;
		lda #$0a				; output CR
		jsr $ffd2
		lda #$0d				; output LF
		jsr $ffd2
;
end:	rts                     ; return to whatever called this program


; subroutine - output text string
outstr1: ldx #0                  ; initialize x register with value 0
loop1:                           ; named label
        lda text1,x              ; load acumulator from
        ;;         memory location "text" (which is a label) indexed by x 
        beq done1                ; branch if equal "0" to "done"
        jsr $ffd2                ; print character routine. 
        inx                      ; increment x
        bne loop1                ; branch if not eq 0 to "loop".
done1:	rts

; subroutine - output text string
outstr2: ldx #0                  ; initialize x register with value 0
loop2:                           ; named label
        lda text2,x              ; load acumulator from
        ;;         memory location "text" (which is a label) indexed by x 
        beq done2                ; branch if equal "0" to "done"
        jsr $ffd2                ; print character routine. 
        inx                      ; increment x
        bne loop2                ; branch if not eq 0 to "loop".
done2:	rts

text1:   .asciiz "hex: answer is "   ; string literal

text2:   .asciiz "bcd: answer is "   ; string literal
