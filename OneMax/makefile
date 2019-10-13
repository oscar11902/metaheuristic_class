all:OneMax

OneMax: main.o HC.o ES.o SA.o Common.o
	g++ -Wall -o OneMax  main.o HC.o SA.o ES.o Common.o

main.o: main.cpp  HC.h ES.h SA.h
	g++ -c main.cpp

HC.o: HC.cpp HC.h Common.h 
	g++ -c HC.cpp

ES.o:ES.cpp ES.h Common.h 
	g++ -c ES.cpp

Common.o:Common.cpp Common.h 
	g++ -c Common.cpp

SA.o:SA.cpp SA.h Common.h 
	g++ -c SA.cpp 

clean: 
	rm -f *.o *.gch OneMax