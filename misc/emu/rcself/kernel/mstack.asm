mpush:     plo     re                  ; save mask
           irx                         ; get return address 
           ldxa
           plo     r4                  ; store here for now
           ldx
           phi     r4
           glo     re                  ; get mask
           shr                         ; shift
           plo     re                  ; and put back
           lbz     mpushn7             ; jump if 7 not saved
           glo     r7                  ; save R7
           stxd
           ghi     r7
           stxd
mpushn7:   glo     re                  ; get mask
           shr                         ; check for R8
           plo     re
           lbz     mpushn8             ; jump if 8 not saved
           glo     r8                  ; save R8
           stxd
           ghi     r8
           stxd
mpushn8:   glo     re                  ; get mask
           shr                         ; check for R9
           plo     re
           lbz     mpushn9             ; jump if 9 not saved
           glo     r9                  ; save R9
           stxd
           ghi     r9
           stxd
mpushn9:   glo     re                  ; get mask
           shr                         ; check for Ra
           plo     re
           lbz     mpushna             ; jump if a not saved
           glo     ra                  ; save Ra
           stxd
           ghi     ra
           stxd
mpushna:   glo     re                  ; get mask
           shr                         ; check for Rb
           plo     re
           lbz     mpushnb             ; jump if b not saved
           glo     rb                  ; save Rb
           stxd
           ghi     rb
           stxd
mpushnb:   glo     re                  ; get mask
           shr                         ; check for Rc
           plo     re
           lbz     mpushnc             ; jump if c not saved
           glo     rc                  ; save Rc
           stxd
           ghi     rc
           stxd
mpushnc:   glo     re                  ; get mask
           shr                         ; check for Rd
           plo     re
           lbz     mpushnd             ; jump if d not saved
           glo     rd                  ; save Rd
           stxd
           ghi     rd
           stxd
mpushnd:   glo     re                  ; get mask
           shr                         ; check for Rf
           plo     re
           lbz     mpushnf             ; jump if f not saved
           glo     rf                  ; save Rf
           stxd
           ghi     rf
           stxd
mpushnf:   ghi     r4                  ; put return address back on stack
           stxd
           glo     r4
           stxd
           ldi     high call          ; restore scall register
           phi     r4
           ldi     low call 
           plo     r4
           sep     sret               ; return to caller

mpop:      plo     re                 ; save mask
           irx                        ; get return address
           ldxa
           plo     r4                 ; save it here
           ldxa
           phi     r4
           glo     re                 ; get mask
           shl                        ; check for rf
           plo     re
           lbz     mpopnf             ; jump if not
           ldxa                       ; load Rf
           phi     rf
           ldxa
           plo     rf
mpopnf:    glo     re                 ; get mask 
           shl                        ; check for rd
           plo     re
           lbz     mpopnd             ; jump if not
           ldxa                       ; load Rd
           phi     rd
           ldxa
           plo     rd
mpopnd:    glo     re                 ; get mask 
           shl                        ; check for rc
           plo     re
           lbz     mpopnc             ; jump if not
           ldxa                       ; load Rc
           phi     rc
           ldxa
           plo     rc
mpopnc:    glo     re                 ; get mask 
           shl                        ; check for rb
           plo     re
           lbz     mpopnb             ; jump if not
           ldxa                       ; load Rb
           phi     rb
           ldxa
           plo     rb
mpopnb:    glo     re                 ; get mask 
           shl                        ; check for ra
           plo     re
           lbz     mpopna             ; jump if not
           ldxa                       ; load Ra
           phi     ra
           ldxa
           plo     ra
mpopna:    glo     re                 ; get mask 
           shl                        ; check for r9
           plo     re
           lbz     mpopn9             ; jump if not
           ldxa                       ; load R9
           phi     r9
           ldxa
           plo     r9
mpopn9:    glo     re                 ; get mask 
           shl                        ; check for r8
           plo     re
           lbz     mpopn8             ; jump if not
           ldxa                       ; load R8
           phi     r8
           ldxa
           plo     r8
mpopn8:    glo     re                 ; get mask 
           shl                        ; check for r7
           plo     re
           lbz     mpopn7             ; jump if not
           ldxa                       ; load R7
           phi     r7
           ldxa
           plo     r7
mpopn7:    dec     r2                 ; move stack back into free space
           lbr     mpushnf            ; clean up and return

