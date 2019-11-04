all:TSP

TSP: main.o ACO.o Common.o
	g++ -ggdb -o TSP -O2  main.o ACO.o Common.o

main.o: main.cpp ACO.h
	g++ -ggdb -c main.cpp

Common.o:
	g++ -ggdb -c Common.cpp

ACO.o:ACO.cpp Common.h 
	g++ -ggdb -c ACO.cpp

clean: 
	rm -f *.o *.gch TSP *.txt