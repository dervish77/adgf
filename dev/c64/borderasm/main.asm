; borderasm in assembly
; 
; set border color to selected color from a table
;

		black = 0
		white = 1
		red = 2
		purple = 3
		orange = 4
		
		color = purple

loop:
		ldy #color				; set table index
		ldx colortab,y			; load indexed color from table
        stx border              ; store color to BORDER
        jmp loop


border := $d020

colortab:
		.byte	0				; black
		.byte	1				; white
		.byte	2				; red
		.byte	4				; purple
		.byte	8				; orange

