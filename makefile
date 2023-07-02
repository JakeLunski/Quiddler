# Jake Lunski
# CPSC 1071-002
# Binary Beasts
# 4/22/2023

compile:
	gcc -Wall -fcommon -o Project-4.out Project-4.c Quiddler.c 
run:
	./Project-4.out

compile-x:
	gcc -Wall -fcommon -o Project-4.out Project-4.c Quiddler-x.c
run-x:
	./Project-4.out
	
clean:
	rm -f Project-4.out