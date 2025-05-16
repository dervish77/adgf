
10 REM Calculate the first 10 digits of pi in Commodore 64 BASIC
20 PI = 3
30 FOR N = 1 TO 10
40 PI = PI + 4 / (2 * N - 1) - 4 / (2 * N + 1)
50 NEXT N
60 PRINT PI


