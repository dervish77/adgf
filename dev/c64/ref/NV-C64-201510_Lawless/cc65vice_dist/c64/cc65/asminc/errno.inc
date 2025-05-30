;
; Ullrich von Bassewitz, 16.05.2000
;

; Variables and functions

        .global         __errno, __oserror
        .global         __maperrno, __osmaperrno
        .global         __seterrno
        .global         oserrcheck, setoserror
        .global         seterrnofromoserror

; Error codes, must match the values in the C headers
.enum
        EOK                     ; No error
        ENOENT 	       	        ; No such file or directory
        ENOMEM 	       	        ; Out of memory
        EACCES 	       	        ; Permission denied
        ENODEV 	       	        ; No such device
        EMFILE 	       	        ; Too many open files
        EBUSY  	       	        ; Device or resource busy
        EINVAL 	       	        ; Invalid argument
        ENOSPC 	       	        ; No space left on device
        EEXIST 	       	        ; File exists
        EAGAIN 	       	        ; Try again
        EIO    	       	        ; I/O error
        EINTR  	       	        ; Interrupted system call
        ENOSYS 	       	        ; Function not implemented
        ESPIPE 	       	        ; Illegal seek
        ERANGE                  ; Range error
        EUNKNOWN       	        ; Unknown OS specific error - must be last!

        EMAX    = EUNKNOWN      ; Highest error code
.endenum


