tree: main.o tree.o
	g++ -g main.o tree.o -o $@

tree_rand: main_rand.o tree_rand.o
	g++ -g main_rand.o tree_rand.o -o $@

main_rand.o: main_rand.cpp 
	g++ -g -c main_rand.cpp

main.o: main.cpp 
	g++ -g -c main.cpp

tree_rand.o: tree_rand.cpp tree_rand.h
	g++ -g -c tree_rand.cpp

tree.o: tree.cpp tree.h
	g++ -g -c tree.cpp

clean:
	rm -f *.o tree tree_rand
