# Jason Chen 23642753
CXXFLAGS=-std=c++11

all: main.o cpu.o process.o harddisk.o ram.o 
	g++ -Wall -g -o all main.o cpu.o process.o harddisk.o ram.o

run: 
	./all

main.o: main.cpp

cpu.o: cpu.cpp cpu.h

process.o: process.cpp process.h

harddisk.o: harddisk.cpp harddisk.h

ram.o: ram.cpp ram.h

clean:
	rm -f main.o cpu.o process.o harddisk.o ram.o all
