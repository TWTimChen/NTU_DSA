printer: main.o deap.o
	g++ -g main.o deap.o -o $@

main.o: main.cpp
	g++ -g -c main.cpp

deap.o: deap.cpp deap.h
	g++ -g -c deap.cpp

clean:
	rm -f *.o printer
