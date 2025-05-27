
hexout:    stxd
           shr
           shr
           shr
           shr
           plo      re
           smi      10
           lbnf     digit1
           glo      re
           adi      55
           lbr      digit1a
digit1:    glo      re
           adi      030h
digit1a:   sep      scall
           dw       f_type
           irx
           ldx
           ani      0fh
           plo      re
           smi      10
           lbnf     digit2
           glo      re
           adi      55
           lbr      digit2a
digit2:    glo      re
           adi      030h
digit2a:   sep      scall
           dw       f_type
           sep      sret

debug:     lda      r6
           lbz      debugdn
           sep      scall
           dw       f_type
           lbr      debug
debugdn:   ldi      '2'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      r2
           sep      scall
           dw       hexout
           glo      r2
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      '7'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      r7
           sep      scall
           dw       hexout
           glo      r7
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      '8'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      r8
           sep      scall
           dw       hexout
           glo      r8
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      '9'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      r9
           sep      scall
           dw       hexout
           glo      r9
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      'A'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      ra
           sep      scall
           dw       hexout
           glo      ra
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      'B'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      rb
           sep      scall
           dw       hexout
           glo      rb
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      'C'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      rc
           sep      scall
           dw       hexout
           glo      rc
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      'D'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      rd
           sep      scall
           dw       hexout
           glo      rd
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      'E'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      re
           sep      scall
           dw       hexout
           glo      re
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type
           ldi      'F'
           sep      scall
           dw       f_type
           ldi      ':'
           sep      scall
           dw       f_type
           ghi      rf
           sep      scall
           dw       hexout
           glo      rf
           sep      scall
           dw       hexout
           ldi      32
           sep      scall
           dw       f_type



           ldi      10
           sep      scall
           dw       f_type
           ldi      13
           sep      scall
           dw       f_type
           sep      sret
           
fildes:    lda      rd                 ; show current offset
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           ldi      ' '
           sep      scall
           dw       f_type
           lda      rd                 ; show dta
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           ldi      ' '
           sep      scall
           dw       f_type
           lda      rd                 ; show eof
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           ldi      ' '
           sep      scall
           dw       f_type
           lda      rd                 ; show flags
           sep      scall
           dw       hexout
           ldi      ' '
           sep      scall
           dw       f_type
           lda      rd                 ; show dir sector
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           ldi      ' '
           sep      scall
           dw       f_type
           lda      rd                 ; show dir offset
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           ldi      ' '
           sep      scall
           dw       f_type
           lda      rd                 ; show current sector
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           lda      rd
           sep      scall
           dw       hexout
           ldi      ' '
           sep      scall
           dw       f_type
           glo      rd
           smi      19
           plo      rd
           ghi      rd
           smbi     0
           phi      rd
           ldi      10
           sep      scall
           dw       f_type
           ldi      13
           sep      scall
           dw       f_type
           sep      sret

wait:      ldi      '>'
           sep      scall
           dw       f_type
           sep      scall
           dw       f_read
           ldi      10
           sep      scall
           dw       f_type
           ldi      13
           sep      scall
           dw       f_type
           sep      sret
