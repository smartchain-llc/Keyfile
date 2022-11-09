C=g++
DIRBUILD=build
DIRO=$(DIRBUILD)/objects
DIRBIN=$(DIRBUILD)/bin
FLAGS=-Wall -std=c++17

setup:
	@mkdir $(DIRBUILD)
	@mkdir $(DIRBIN) $(DIRO)

clean:
	@rm -rf $(DIRBUILD)

%.o: setup src/%.cpp
	$(C) -c src/$*.cpp -o $(DIRO)/%.o

test.o: src/test.cpp
	$(C) -c $(FLAGS) src/test.cpp -o $(DIRO)/$@

keyfile.o: setup 
	$(C) -c $(FLAGS) src/keyfile.cpp -o $(DIRO)/$@

test: keyfile.o test.o
	$(C) $(DIRO)/keyfile.o $(DIRO)/test.o -o $(DIRBIN)/$@ 