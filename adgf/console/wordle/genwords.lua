-- genwords.lua - generate wordle word list code file from text file
--

-- define file header
header = [[
/************************************************************************
 * File: words.c
 ************************************************************************/
 
#include "game.h"

WORD_S_T words[] = {
]]

-- define file footer
footer = [[
-1, " "
};
]]

-- define temp file names
inputfile = "test.txt"
outputfile = "test.c"


-- defines read/write word list function
function processlist(infile, outfile)
	local inf = assert(io.open(infile, "r"))
	local of = assert(io.open(outfile, "w"))
	
	local count = 1;
	
	of:write(header)
	
	while true do
		local line = inf:read("*line")
		if line == nil then break end
		local temp = string.sub(line, 1, 5)
		--of:write(string.format("%d, ", count), string.format("\"%s\",", temp), "\n")
		of:write(string.format("%d, \"%s\",", count, temp), "\n")
		count = count + 1
	end
	
	of:write(footer)
end

-- main program
print("Generating", outputfile, "from", inputfile)
processlist(inputfile, outputfile)
print("... done")
