; use hex to output add result in assembly
;

.export outhex
.export outbcd


; subroutine - display number to screen
.proc outhex: near
		tax					; save sum to X
		lsr A				; right shift hi nibble to low
		lsr A
		lsr A
		lsr A
		jsr digith			; display digit
		txa					; restore sum to A
		and #$0F			; mask out high nibble
		jsr digith			; display digit
		rts
.endproc

; subroutine - convert nibble to ascii and display
digith:	cmp #$0A			; compare Acc to $0A
		bcc skip			; if less than $0A, skip the add
		adc #$66 			; Add $67 (the carry is set), convert $0A to $0F --> $71 to $76
skip: 	eor #$30 			; Convert $00 to $09, $71 to $76 --> $30 to $39, $41 to $46
		jsr $ffd2			; put character on screen
		rts


; subroutine - display number to screen
.proc outbcd: near
		tax					; save sum to X
		lsr A				; right shift hi nibble to low
		lsr A
		lsr A
		lsr A
		jsr digitb			; display digit
		txa					; restore sum to A
		and #$0F			; mask out high nibble
		jsr digitb			; display digit
		rts
.endproc

; subroutine - convert nibble to ascii and display
digitb:	sed
		cmp #$0A
		adc #$30
		cld
		jsr $ffd2			; put character on screen
		rts

