all: codec

codec: main.cpp Makefile
	g++ -Wall -O3 -o codec main.cpp

clean:
	rm -f codec *.o