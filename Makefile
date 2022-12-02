.SILENT:

main:
	echo "To run a specific day, type 'make dayXX' where XX is a two-digit number."

day01:
	g++ day01.cpp -o output/day01
	output/day01
