CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17
TEST_FLAGS = -lgtest -lstdc++ -lgmock -pthread

.PHONY: all install open uninstall clean dist test

all: clean uninstall dist install test

install:
	@echo -------------------- INSTALL --------------------
	make uninstall --quiet
	mkdir build
	cp Makefile build && qmake && make && make clean && rm -rf Makefile .qmake.stash && mv build/Makefile . && mv SmartCalc.app build
	@echo -------------------- SUCCESS --------------------

open:
	@echo --------------------- OPEN ----------------------
	cd build && open SmartCalc.app
	@echo -------------------- SUCCESS --------------------
	
uninstall:
	@echo ------------------- UNINSTALL -------------------
	rm -rf build
	@echo -------------------- SUCCESS --------------------

clean:
	@echo --------------------- START ---------------------
	rm -rf SmartCalc.tar.gz
	cd ./tests && rm -rf unit_tests
	@echo -------------------- SUCCESS --------------------
	
dist:
	@echo --------------------- START ---------------------
	tar czvf SmartCalc.tar.gz .
	@echo -------------------- SUCCESS --------------------

test:
	@echo --------------------- START ---------------------
	cd ./tests/ && $(CC) $(FLAGS) unit_tests.cc ../model/model_calculator.cc -o unit_tests $(TEST_FLAGS)
	cd ./tests/ && ./unit_tests
	@echo -------------------- SUCCESS --------------------
