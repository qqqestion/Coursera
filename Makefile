all:
	g++ -std=c++17 server_stats.cpp stats.cpp -o main

fo: main.o stats.o
	g++ main.o stats.o -o main

main.o: server_stats.cpp
	g++ -c server_stats.cpp -o main.o

stats.o: stats.cpp
	g++ -c stats.cpp

clean:
	rm -rf *.o main
