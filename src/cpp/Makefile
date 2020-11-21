#opzione -g: per il debug
#opzione -c: non fare il link, compila e basta

all: macchina citta dio main
main:
	g++ -g -o main main.cpp macchina.o citta.o dio.o

macchina:
	g++ -c -g -o macchina.o Macchina.cpp
citta:
	g++ -c -g -o citta.o Citta.cpp
dio:
	g++ -c -g -o dio.o Dio.cpp macchina.o citta.o

clean:
	rm *.o main
