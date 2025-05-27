'file: buzzer.bas

'define pins
symbol led = 1
symbol buzzer = 2

' main program loop
main: 	
	high led
	low buzzer
	pause 1000
	low led
	high buzzer
	pause 1000
	goto main
	end

'eof

