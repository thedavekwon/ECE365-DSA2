spell.exe: spellcheck.o hash.o functions.o
	g++ -o spell.exe spellcheck.o hash.o functions.o

spellcheck.o: src/spellcheck.cpp include/hash.h
	g++ -c src/spellcheck.cpp

hash.o: src/hash.cpp include/hash.h
	g++ -c src/hash.cpp

functions.o: src/functions.cpp include/functions.h
	g++ -c src/functions.cpp

debug:
	g++ -g -o spellDebug.exe src/spellcheck.cpp src/hash.cpp src/functions.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups