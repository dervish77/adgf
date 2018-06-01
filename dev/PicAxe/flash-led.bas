'file: flash-led.bas

'define pins
symbol led = 1

' main program loop
main: 	
	high led
	pause 200
	low led
	pause 200
	goto main
	end

'eof




