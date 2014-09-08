CC=g++
CFLAGS=-c -Wall
SFLAGS=-shared
LDFLAGS=-Wall -Llib -Wl,-rpath=$(shell pwd)/lib

all: bin/fcgi

#bin/main: bin lib obj lib/libGeminoCore.so
#	$(CC) $(LDFLAGS) src/main.cpp -o $@ -lGeminoCore

bin/fcgi: bin lib obj lib/libGeminoCore.so
	$(CC) $(LDFLAGS) src/fcgi.cpp -lfcgi -lfcgi++ -lGeminoCore -o $@

bin:
	mkdir bin
lib:
	mkdir lib
obj:
	mkdir obj

lib/libGeminoCore.so: obj/Gemino/Core obj/Gemino/Core/App.o
	$(CC) $(SFLAGS) obj/Gemino/Core/App.o -o $@
obj/Gemino/Core:
	mkdir -p $@
obj/Gemino/Core/App.o: src/lib/Gemino/Core/App.cpp
	$(CC) $(CFLAGS) -fpic src/lib/Gemino/Core/App.cpp -o $@

clean:
	rm -rf bin obj lib
