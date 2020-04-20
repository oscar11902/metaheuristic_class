all:SingleObjective

SingleObjective: main.o HC.o ES.o SA.o TS.o GA.o Common.o Recorder.o
	g++ -ggdb -o SingleObjective  main.o HC.o SA.o ES.o TS.o GA.o Common.o

main.o: HC.h ES.h SA.h
	g++ -ggdb -c main.cpp
HC.o:Common.h 
	g++ -ggdb -c HC.cpp
ES.o:Common.h 
	g++ -ggdb -c ES.cpp
Common.o: Common.h Common.cpp
	g++ -ggdb -c Common.cpp
SA.o:Common.h 
	g++ -ggdb -c SA.cpp
TS.o:Common.h
	g++ -ggdb -c TS.cpp
GA.o:GA.cpp GA.h Common.h
	g++ -ggdb -c GA.cpp
Recorder.o:Recorder.h Recorder.cpp
	g++ -ggdb -c Recorder.cpp
clean: 
	rm -f *.o *.gch OneMax