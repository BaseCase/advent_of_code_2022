.SILENT:

main:
	echo "To run a specific day, type 'make dayXX' where XX is a two-digit number."

.PHONY: day day01 day02 day03 day04 day05 day06 day07 day08 day09 day10 day11 day12 day13 day14 day15 day16 day17 day18 day19 day20 day21 day22 day23 day24 day25

day:
	g++ $(DAY).cpp -o output/$(DAY) --std=c++17
	output/$(DAY)

day01: DAY = day01
day01: day

day02: DAY = day02
day02: day

day03: DAY = day03
day03: day
