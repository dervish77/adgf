10 REM Calculate the first digits of pi
20 REM in Commodore 64 BASIC
30 P = 3
40 D = 1
50 print "calculating pi"
60 FOR N = 2 TO 1000 STEP 2
70 A = 4 / (2 * (N + 1) * (N + 2))
80 if D = 1 then P = P + A : D = 0 : goto 100
90 if D = 0 then P = P - A : D = 1 : goto 100
100 NEXT N
110 PRINT "result pi = ";P
