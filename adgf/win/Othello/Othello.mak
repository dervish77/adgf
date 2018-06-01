#------------------------
# OTHELLO.MAK make file
#------------------------

othello.exe : main.obj count.obj flip.obj scan.obj stub.obj othello.obj othello.res
     $(LINKER) $(GUIFLAGS) -OUT:othello.exe main.obj count.obj flip.obj \
     othello.obj scan.obj stub.obj othello.res $(GUILIBS)

main.obj : main.c main.h othello.h multi.h vecmath.h
     $(CC) $(CFLAGS) main.c

count.obj : count.c main.h othello.h multi.h vecmath.h
     $(CC) $(CFLAGS) count.c

flip.obj : flip.c main.h othello.h multi.h vecmath.h
     $(CC) $(CFLAGS) flip.c

multi.obj : multi.c main.h othello.h multi.h vecmath.h tcplib.h
     $(CC) $(CFLAGS) multi.c

othello.obj : othello.c main.h othello.h multi.h vecmath.h
     $(CC) $(CFLAGS) othello.c

scan.obj : scan.c main.h othello.h multi.h vecmath.h
     $(CC) $(CFLAGS) scan.c

stub.obj : stub.c main.h othello.h multi.h vecmath.h
     $(CC) $(CFLAGS) stub.c

tcplib.obj : tcplib.c tcplib.h
     $(CC) $(CFLAGS) tcplib.c

othello.res : othello.rc main.h
     $(RC) $(RCVARS) othello.rc

