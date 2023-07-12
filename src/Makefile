CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17 -D_GNU_SOURCE
TEST_FLAGS = -lgtest -lgmock -pthread

#	== ВЫПОЛНИТЬ ВСЕ ДЕЙСТВИЯ ==
all: clean uninstall dist install tests dvi

#	== УСТАНОВКА ПРОГРАММЫ ==
install:
	@echo -------------------- INSTALL --------------------
	make uninstall --quiet
	mkdir build
	cd ./view/ && qmake && make && make clean && rm -rf Makefile && mv view.app ../build/
	@echo -------------------- SUCCESS --------------------

#	== ЗАПУСК ПРОГРАММЫ ==
run:
	cd ./build && open view.app
	
#	== УДАЛЕНИЕ ПРОГРАММЫ ==
uninstall:
	@echo ------------------- UNINSTALL -------------------
	rm -rf build
	@echo -------------------- SUCCESS --------------------

#	== ОЧИСТКА ФАЙЛОВ ==
clean:
	rm -rf SmartCalc.tar.gz
	cd ./tests && rm -rf unit_tests
	
#	== ОТКРЫТИЕ README ПРОЕКТА ==
dvi:
	open readme.html

#	== СОЗДАНИЕ АРХИВА ПРОЕКТА ==
dist:
	tar czvf SmartCalc.tar.gz .

#	== ЗАПУСК UNIT-ТЕСТОВ ==
test:
	@echo --------------------- START ---------------------
	cd ./tests/ && $(CC) $(FLAGS) unit_tests.cc model_test.cc -o unit_tests $(TEST_FLAGS)
	cd ./tests/ && ./unit_tests
	@echo -------------------- SUCCESS --------------------
