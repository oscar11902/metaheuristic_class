all:OneMax

OneMax: main.o HC.o ES.o SA.o TS.o Common.o
	g++ -Wall -o OneMax  main.o HC.o SA.o ES.o TS.o Common.o

main.o: main.cpp  HC.h ES.h SA.h

HC.o:HC.cpp HC.h Common.h 

ES.o:ES.cpp ES.h Common.h 

Common.o:Common.cpp Common.h 

SA.o:SA.cpp SA.h Common.h 

TS.o:TS.cpp TS.h Common.h

clean: 
	rm -f *.o *.gch OneMax