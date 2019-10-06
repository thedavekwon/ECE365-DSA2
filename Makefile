useHeap.exe: useHeap.o heap.o hash.o
	g++ -o useHeap.exe useHeap.o heap.o hash.o
	
run:
	./useHeap.exe < file/sampleIn.txt

useHeap.o: src/useHeap.cpp
	g++ -c src/useHeap.cpp

heap.o: src/heap.cpp include/heap.h
	g++ -c src/heap.cpp

hash.o: src/hash.cpp include/hash.h src/functions.cpp include/functions.h
	g++ -c src/hash.cpp src/functions.cpp

debug:
	g++ -g -o useHeapDebug.exe src/useHeap.cpp src/heap.cpp src/hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
