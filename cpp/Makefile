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

key.o: setup 
	$(C) -c $(FLAGS) src/key.cpp -o $(DIRO)/$@

test: key.o test.o
	$(C) $(DIRO)/key.o $(DIRO)/test.o -o $(DIRBIN)/$@ 