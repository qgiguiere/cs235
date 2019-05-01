CFLAGS = -std=c++11
lab1: lab1.cpp
	g++ $(CFLAGS) lab1.cpp -o lab1
debug: lab1.cpp
	g++ $(CFLAGS) -g lab1.cpp -o lab1
	valgrind --tool=memcheck --leak-check=yes ./lab1 inputFile.txt outputFile.txt
clean:
	rm lab1;
