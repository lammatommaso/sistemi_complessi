#opzione -g: per il debug
#opzione -c: non fare il link, compila e basta
# nella riga di dio ho tolto a caso citta.o e macchina.o
# solo per togliere i warning che magari servivano

all: macchina citta dio main
main:
	g++ -g -o main main.cpp macchina.o citta.o dio.o

macchina:
	g++ -c -g -o macchina.o Macchina.cpp
citta:
	g++ -c -g -o citta.o Citta.cpp
dio:
	g++ -c -g -o dio.o Dio.cpp 

clean:
	rm *.o main
