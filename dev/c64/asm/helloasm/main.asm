; hello world in assembly
;

        ldx #0                  ; initialize x register with value 0
loop:                           ; named label
        lda text,x              ; load acumulator from
        ;;         memory location "text" (which is a label) indexed by x 
        beq done                ; branch if equal "0" to "done"
        jsr $ffd2               ; print character routine. 
        inx                     ; increment x
        bne loop                ; branch if not eq 0 to "loop".

done:   rts                     ; return to whatever called this program

text:   .asciiz "hello c64 in asm"   ; string literal
