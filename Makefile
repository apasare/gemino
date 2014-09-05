CC=g++
CFLAGS=-c -Wall
SFLAGS=-shared
LDFLAGS=-Wall -Llib -Wl,-rpath=$(shell pwd)/lib

all: bin/fcgi

#bin/main: bin lib obj lib/libGeminoCore.so
#	$(CC) $(LDFLAGS) src/main.cpp -o $@ -lGeminoCore

bin/fcgi: bin lib obj obj/fcgi.o
	$(CC) $(LDFLAGS) obj/fcgi.o -lfcgi -lfcgi++ -o $@

bin:
	mkdir bin
lib:
	mkdir lib
obj:
	mkdir obj

obj/fcgi.o: src/fcgi.cpp
	$(CC) $(CFLAGS) src/fcgi.cpp -o $@

# lib/libGeminoCore.so: obj/Gemino/Core obj/Gemino/Core/Socket.o obj/Gemino/Core/Http.o
	# $(CC) $(SFLAGS) obj/Gemino/Core/Socket.o obj/Gemino/Core/Http.o -o $@
# obj/Gemino/Core/Socket.o: src/lib/Gemino/Core/Socket.cpp
# 	$(CC) $(CFLAGS) -fpic src/lib/Gemino/Core/Socket.cpp -o $@
# obj/Gemino/Core/Http.o: src/lib/Gemino/Core/Http.cpp
# 	$(CC) $(CFLAGS) -fpic src/lib/Gemino/Core/Http.cpp -o $@
# obj/Gemino/Core:
	# mkdir -p $@

clean:
	rm -rf bin obj lib
