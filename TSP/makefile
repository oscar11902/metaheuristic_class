all:TSP

TSP: main.o ACO.o GA.o Common.o 
	g++ -ggdb -Wall -o TSP -O3  main.o ACO.o GA.o Common.o

main.o: main.cpp ACO.h GA.h
	g++ -ggdb -Wall -O3 -c main.cpp

Common.o:Common.h Common.cpp
	g++ -ggdb -Wall -O3 -c Common.cpp

ACO.o:ACO.cpp ACO.h Common.h 
	g++ -ggdb -Wall -O3 -c ACO.cpp

GA.o:GA.cpp GA.h Common.h 
	g++ -ggdb -Wall -O3 -c GA.cpp

clean: 
	rm -f *.o *.gch TSP *.txt