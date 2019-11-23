run: run.exe
	./run.exe

run.exe: src/TogetherToTheEnd.cpp
	g++ -o run.exe src/TogetherToTheEnd.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

# run: run.exe
# 	./run.exe
#
# run.exe: findShortestPath.o dijkstra.o functions.o heap.o hash.o
# 	g++ -o run.exe findShortestPath.o dijkstra.o functions.o heap.o hash.o
#
# findShortestPath.o: src/findShortestPath.cpp
# 	g++ -c src/findShortestPath.cpp
#
# dijkstra.o: src/dijkstra.cpp include/dijkstra.h
# 	g++ -c src/dijkstra.cpp
#
# functions.o: src/functions.cpp include/functions.h
# 	g++ -c src/functions.cpp
#
# heap.o: src/heap.cpp include/heap.h
# 	g++ -c src/heap.cpp
#
# hash.o: src/hash.cpp include/hash.h src/functions.cpp include/functions.h
# 	g++ -c src/hash.cpp src/functions.cpp
#
# debug:
# 	g++ -g -o useHeapDebug.exe src/useHeap.cpp src/heap.cpp src/hash.cpp
#
# clean:
# 	rm -f *.exe *.o *.stackdump *~
#
# backup:
# 	test -d backups || mkdir backups
# 	cp *.cpp backups
# 	cp *.h backups
# 	cp Makefile backups
