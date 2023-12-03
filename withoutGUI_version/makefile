# Purpose: makefile for proj5		Assignment 5	
# ----------------------------------------------------------------------------------- #
# if the make file is giving an error like...
# make: *** No rule to make target `hashtable.h', needed by `hashtable.h.gch'.  Stop.
# ...then you need to run the following command:
# 'touch hashtable.h'
# ...and then try running make again
# or just 'make clean' and then make
# ----------------------------------------------------------------------------------- #

CC = g++
CFLAGS = -std=c++11 # or 14, but linprog doesnt support

all: proj5.x

hashtable.h.gch: hashtable.h
	$(CC) $(CFLAGS) -c hashtable.h

spellcheck.o: spellcheck.cpp
	$(CC) $(CFLAGS) -c spellcheck.cpp

proj5.x: hashtable.h.gch spellcheck.o
	$(CC) $(CFLAGS) -o proj5.x hashtable.h.gch spellcheck.o

clean:
	rm -f proj5.x hashtable.h.gch spellcheck.o
