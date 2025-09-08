-- genwords.lua - generate wordle word list code file from text file
--
-- Usage: genwords.lua [infile outfile]
--

version = "0.2"

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

-- define default file names
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
		local word = string.sub(line, 1, 5)   -- extract word from current line
		of:write(string.format("%d, \"%s\",", count, word), "\n")
		count = count + 1
	end
	
	of:write(footer)
end

-- main program
print(string.format("============ genwords.lua %s ============", version))
if #arg == 2 then
	inputfile = arg[1]
	outputfile = arg[2]
end
print("Generating", outputfile, "from", inputfile)
processlist(inputfile, outputfile)
print("... done")
