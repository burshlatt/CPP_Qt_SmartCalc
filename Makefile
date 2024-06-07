CXX = g++
FLAGS = -Wall -Wextra -Werror
TEST_FLAGS = -lgtest -pthread

OS := $(shell uname)
ifeq ($(OS), Linux)
    TEST_FLAGS += -lgtest_main
else ifeq ($(OS), Darwin) 
    TEST_FLAGS += -lgmock
endif

.PHONY: build install run uninstall clean test

build: uninstall
	@echo --------------------- BUILD ---------------------
	make uninstall --quiet
	mkdir build
	cd build && cmake ..
	@echo -------------------- SUCCESS --------------------

install:
	@echo -------------------- INSTALL --------------------
	cd build && make
	cd build && rm -rf CMakeFiles SmartCalc_autogen cmake_install.cmake CMakeCache.txt Makefile
	@echo -------------------- SUCCESS --------------------

ifeq ($(OS), Linux)
run:
	@echo ---------------------- RUN ----------------------
	cd build && ./SmartCalc
	@echo -------------------- SUCCESS --------------------
else ifeq ($(OS), Darwin) 
run:
	@echo ---------------------- RUN ----------------------
	cd build && open SmartCalc.app
	@echo -------------------- SUCCESS --------------------
endif
	
uninstall:
	@echo ------------------- UNINSTALL -------------------
	rm -rf build
	@echo -------------------- SUCCESS --------------------

clean: uninstall
	@echo --------------------- START ---------------------
	cd ./tests && rm -rf unit_tests
	@echo -------------------- SUCCESS --------------------
	
test:
	@echo --------------------- START ---------------------
	cd ./tests/ && $(CXX) $(FLAGS) unit_tests.cc ../src/model/calc/model_calc.cc -o unit_tests $(TEST_FLAGS)
	cd ./tests/ && ./unit_tests
	@echo -------------------- SUCCESS --------------------
