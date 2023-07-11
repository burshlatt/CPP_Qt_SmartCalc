CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++17 -D_GNU_SOURCE
TEST_FLAGS = -lgtest -lgmock -pthread

#	== ВЫПОЛНИТЬ ВСЕ ДЕЙСТВИЯ ==
all: clean uninstall dist install gcov_report dvi

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

#	== УСТАНОВКА LCOV ==
lcov:
	cd && brew install lcov

#	== СОЗДАНИЕ GCOV ОТЧЕТА ==
#	Для корректной работы нужно установить lcov: make lcov
gcov_report: tests
#	cd ./CFiles/ && $(CC) $(FLAGS) --coverage ../test/test.c s21_3dViewer.c s21_affins.c s21_3dViewer.a $(TEST_LIBS) -o gcov_test
#	cd ./CFiles/ && ./gcov_test
#	cd ./CFiles/ && lcov -t "3dviewer" -o 3dviewer.info -c -d .
#	cd ./CFiles/ && genhtml -o report 3dviewer.info
#	cd ./CFiles/ && open ./report/index.html
	
#	== ОТКРЫТИЕ README ПРОЕКТА ==
dvi:
	open readme.html

#	== СОЗДАНИЕ АРХИВА ПРОЕКТА ==
dist:
	tar czvf SmartCalc.tar.gz .

#	== ЗАПУСК UNIT-ТЕСТОВ ==
tests:
	@echo --------------------- START ---------------------
	cd ./test/ && $(CC) $(FLAGS) unit_tests.cc ../model/model.cc -o unit_tests $(TEST_FLAGS)
	cd ./test/ && ./unit_tests
	@echo -------------------- SUCCESS --------------------
