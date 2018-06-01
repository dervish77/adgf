'file: sound-toggle.bas

'define pins
symbol led = 1
symbol buzzer = 2

'define sound parameters
symbol duration = 30
symbol freqlow = 80
symbol freqhigh = 100

' main program loop
main: 	
	high led
	sound buzzer, (freqhigh, duration)
	pause 300
	low led
	sound buzzer, (freqlow, duration)
	pause 300
	goto main
	end

'eof


