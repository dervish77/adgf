'file: sound-ramp.bas

'define pins
symbol led = 1
symbol buzzer = 2

'define loop index
symbol counter = b0

'define sound parameters
symbol duration  = 1
symbol freqstart = 80
symbol freqstop  = 120


' main program loop
main: 	
	high led
	gosub soundup
	low led
	gosub sounddown
	goto main
	end

'procedure: ramp sound up
soundup:
	for counter = freqstart to freqstop
	  sound buzzer, (counter, duration)
	next counter
	return

'procedure: ramp sound down
sounddown:
 	for counter = freqstop to freqstart step -1
	  sound buzzer, (counter, duration)
	next counter
	return

'eof



