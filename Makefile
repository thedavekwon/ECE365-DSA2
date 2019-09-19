spell.exe: spellcheck.o hash.o
	g++ -o spell.exe spellcheck.o hash.o

spellcheck.o: src/spellcheck.cpp include/hash.h
	g++ -c src/spellcheck.cpp

hash.o: hash.cpp hash.h
	g++ -c src/hash.cpp

debug:
	g++ -g -o spellDebug.exe src/spellcheck.cpp src/hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups