all:OneMax

OneMax: main.o HC.o ES.o Common.o
	g++ -o OneMax main.o HC.o ES.o Common.o

main.o: main.cpp 
	g++ -c main.cpp

HC.o: HC.h Common.o
	g++  -c HC.cpp

ES.o:ES.h Common.o
	g++ -c ES.cpp

Common.o:Common.h
	g++ -c Common.cpp

clean: 
	rm -f *.o *.gch OneMax