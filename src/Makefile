CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17
TEST_FLAGS = -lgtest -lstdc++ -lgmock -pthread

#	== ВЫПОЛНИТЬ ВСЕ ДЕЙСТВИЯ ==
.PHONY: all
all: clean uninstall dist install test dvi

#	== УСТАНОВКА ПРОГРАММЫ ==
.PHONY: install
install:
	@echo -------------------- INSTALL --------------------
	make uninstall --quiet
	mkdir build
	cp Makefile build && qmake && make && make clean && rm -rf Makefile .qmake.stash && mv build/Makefile . && mv SmartCalc.app build
	@echo -------------------- SUCCESS --------------------

#	== ЗАПУСК ПРОГРАММЫ ==
.PHONY: open
open:
	@echo --------------------- OPEN ----------------------
	cd build && open SmartCalc.app
	@echo -------------------- SUCCESS --------------------
	
#	== УДАЛЕНИЕ ПРОГРАММЫ ==
.PHONY: uninstall
uninstall:
	@echo ------------------- UNINSTALL -------------------
	rm -rf build
	@echo -------------------- SUCCESS --------------------

#	== ОЧИСТКА ФАЙЛОВ ==
.PHONY: clean
clean:
	@echo --------------------- START ---------------------
	rm -rf SmartCalc.tar.gz
	cd ./tests && rm -rf unit_tests
	@echo -------------------- SUCCESS --------------------
	
#	== ОТКРЫТИЕ README ПРОЕКТА ==
.PHONY: dvi
dvi:
	@echo --------------------- OPEN ----------------------
	open info.html
	@echo -------------------- SUCCESS --------------------

#	== СОЗДАНИЕ АРХИВА ПРОЕКТА ==
.PHONY: dist
dist:
	@echo --------------------- START ---------------------
	tar czvf SmartCalc.tar.gz .
	@echo -------------------- SUCCESS --------------------

#	== ЗАПУСК UNIT-ТЕСТОВ ==
.PHONY: test
test:
	@echo --------------------- START ---------------------
	cd ./tests/ && $(CC) $(FLAGS) unit_tests.cc model_test.cc -o unit_tests $(TEST_FLAGS)
	cd ./tests/ && ./unit_tests
	@echo -------------------- SUCCESS --------------------

#   === Стиль ===
.PHONY: style
style:
	@echo --------------------- STYLE ---------------------
	cp ../materials/linters/.clang-format ./
	clang-format -n */*.cc */*.h
	rm -rf .clang-format
	@echo -------------------- SUCCESS --------------------
