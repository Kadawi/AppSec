default: prog

get-deps:
	# Assuming Debian or Ubuntu here
	sudo apt-get install -y build-essential check

dictionary.o: dictionary.c
	gcc -Wall -c dictionary.c dictionary.h

spell.o: spell.c
	gcc -Wall -c spell.c

test.o: test_main.c
	gcc -Wall -c test_main.c

main.o: main.c
	gcc -Wall -c main.c

test: dictionary.o spell.o test.o
	gcc -Wall -o test_main test_main.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main

prog: dictionary.o spell.o main.o
	gcc -Wall -g -o spell_check dictionary.o spell.o main.o

debug: dictionary.o spell.o test.o
	gcc --enable-checking -Wall -g -O0 -Q -o debug_spell_test test_main.o dictionary.o spell.o -lcheck -lm -lrt -lpthread -lsubunit
	./debug_spell_test

clean:
	rm dictionary.o spell.o main.o test_main.o check_spell.o spell_check debug_spell debug_spell_test dictionary.h.gch test_main

cleanall:clean
	rm spell_check debug_spell debug_spell_test
	
