demo: main.o userMap.o prodUser.o cmdParser.o
	g++ -g main.o userMap.o prodUser.o cmdParser.o -o $@

main.o: main.cpp util.hpp
	g++ -g -c main.cpp

userMap.o: userMap.cpp userMap.hpp
	g++ -g -c userMap.cpp

prodUser.o: prodUser.cpp prodUser.hpp
	g++ -g -c prodUser.cpp

cmdParser.o: cmdParser.cpp cmdParser.hpp
	g++ -g -c cmdParser.cpp



clean:
	rm -f *.o demo
