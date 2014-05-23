CC=g++
CFLAGS=-c -Wall
SFLAGS=-shared
LDFLAGS=-Wall -Llib -Wl,-rpath=$(shell pwd)/lib

all: bin/main

bin/main: bin lib obj lib/libGemino.so
	$(CC) $(LDFLAGS) src/main.cpp -o $@ -lGemino
bin:
	mkdir bin
lib:
	mkdir lib
obj:
	mkdir obj
lib/libGemino.so: obj/Gemino/Socket.o
	$(CC) $(SFLAGS) obj/Gemino/Socket.o -o $@
obj/Gemino/Socket.o: obj/Gemino src/lib/Gemino/Socket.cpp
	$(CC) $(CFLAGS) -fpic src/lib/Gemino/Socket.cpp -o $@
obj/Gemino:
	mkdir obj/Gemino
clean:
	rm -rf bin obj lib
