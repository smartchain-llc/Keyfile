C=g++
DIRBUILD=build
DIRO=$(DIRBUILD)/objects
DIRBIN=$(DIRBUILD)/bin
FLAGS=-Wall -cstd=c++20

setup:
	@mkdir $(DIRBUILD)
	@mkdir $(DIRBIN) $(DIRO)

clean:
	@rm -rf $(DIRBUILD)

test.o: setup src/test.cpp
	$(C) -c src/test.cpp -o $(DIRO)

test: test.o
	$(C) $(DIRO)/$< -o $(DIRBIN)/$@ 