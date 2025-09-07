-- fibo.lua - fibonacci program
--

-- defines a fibonacci function
function fibo(count)
	previous2 = 0
	previous1 = 1
	current = 1
	
	print(previous2)
	if count > 1 then
		print(previous1)
		
		if count > 2 then
			local i = 3
			while i <= count do
				current = previous2 + previous1
				print(current)
				previous2 = previous1
				previous1 = current
				i = i + 1
			end
		end
	end
end

print("Enter number of results: ")
results = io.read("*n")
print("Fibonacci of (n) is ")
print(fibo(results))

