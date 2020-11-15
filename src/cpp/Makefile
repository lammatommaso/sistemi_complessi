

all: macchina citta main
main:
	g++ -g -o main main.cpp macchina.o citta.o

macchina:
	g++ -g -o macchina.o -c Macchina.cpp
citta:
	g++ -g -o citta.o -c Citta.cpp

clean:
	rm *.o main
