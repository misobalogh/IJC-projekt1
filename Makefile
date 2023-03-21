#/***************************************************************
#* File Name: Makefile
#* Description: riesnie IJC-DU1, makefile pre obidve casti uloh - a) aj b)
#* Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
#* Faculty: FIT VUT
#* Date: 21.3.2023
#
#* Comments: 
#***************************************************************/

CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
LDLIBS=-lm
IMG=du1-obrazek.ppm


all: steg-decode primes  primes-i
	ulimit -s 35000; ./primes; ./primes-i
	./steg-decode $(IMG)


error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

#***************************************************************#

#uloha A)

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o 

primes.o: primes.c eratosthenes.h bitset.h error.h 
	$(CC) $(CFLAGS) -c primes.c -o primes.o
	
primes-i.o: primes.c eratosthenes.h bitset.h error.h 
	$(CC) $(CFLAGS) -c -DUSE_INLINE primes.c -o primes-i.o

primes: primes.o eratosthenes.o error.o 
	$(CC) $(CFLAGS) primes.o eratosthenes.o error.o -o primes $(LDLIBS)

primes-i: primes-i.o eratosthenes.o error.o 
	$(CC) $(CFLAGS) -DUSE_INLINE primes-i.o eratosthenes.o error.o -o primes-i $(LDLIBS)

# rozsiri zasobnik a spusti ulohu a), najprv s makrami a potom s inline funkciami 
run: primes primes-i
	ulimit -s 35000; ./primes; ./primes-i

runprimes: primes
	ulimit -s 35000; ./primes

runprimes-i: primes-i
	ulimit -s 35000; ./primes-i

#***************************************************************#

#uloha B)

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

steg-decode.o: steg-decode.c ppm.h eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o

steg-decode: ppm.o eratosthenes.o error.o steg-decode.o
	$(CC) $(CFLAGS) ppm.o eratosthenes.o error.o steg-decode.o -o steg-decode $(LDLIBS)

# spusti ulohu b) s testovacim obrazkom
runsd: steg-decode
	./steg-decode $(IMG)

# odstrani vsetky subory vytvorene pri preklade
clean:
	rm -f *.o primes primes-i steg-decode

# vytvori skomprimovany subor
zip: 
	zip xbalog06.zip *.h *.c Makefile
