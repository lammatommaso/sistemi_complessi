all: car road node city simulator main

main:
	g++ -std=c++11 -pthread -g -o main main.cpp car.o road.o node.o city.o simulator.o 

car:
	g++ -c -g -o car.o car.cpp

road:
	g++ -c -g -o road.o road.cpp

node:
	g++ -c -g -o node.o node.cpp

city:
	g++ -c -g -o city.o city.cpp

simulator:
	g++ -c -g -o simulator.o simulator.cpp 

clean:
	rm *.o main
