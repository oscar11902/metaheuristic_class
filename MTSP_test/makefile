all:TSP

TSP: main.o ACO.o PSO.o Common.o Ant.o
	g++ -ggdb -Wall -o TSP -std=c++11 -O3  main.o ACO.o PSO.o Common.o Ant.o

main.o: main.cpp ACO.h PSO.h Ant.h
	g++ -ggdb -Wall -std=c++11 -O3 -c main.cpp

Common.o:Common.h Common.cpp
	g++ -ggdb -Wall -std=c++11 -O3 -c Common.cpp

ACO.o:ACO.cpp ACO.h Common.h Ant.h
	g++ -ggdb -Wall -std=c++11 -O3 -c ACO.cpp

PSO.o:PSO.cpp PSO.h Common.h 
	g++ -ggdb -Wall -std=c++11 -O3 -c PSO.cpp

Ant.o:Ant.cpp Ant.h Common.h 
	g++ -ggdb -Wall -std=c++11 -O3 -c Ant.cpp	

clean: 
	rm -f *.o *.gch TSP *.txt