CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
TEST_LIBS = -lcheck -lm -lpthread

smartcalc.a: clean_test
	$(CC) $(CFLAGS) -c ../CFiles/s21_*.c ../CFiles/help_functions.c
	ar rcs smartcalc.a *.o
	ranlib smartcalc.a

test: smartcalc.a
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
	$(CC) unit_test.o smartcalc.a $(TEST_LIBS) -o calc_test
	rm -rf test/*.o
	./calc_test

gcov_report: smartcalc.a
	cp ../CFiles/s21_*.* .
	$(CC) $(FLAGS) --coverage unit_test.c s21_*.c smartcalc.a $(TEST_LIBS) -o gcov_test
	./gcov_test
	lcov -t "smartcalc" -o smartcalc.info -c -d .
	genhtml -o report smartcalc.info
	open ./report/index.html

clean_test:
	rm -rf s21_*.* calc_test *.o *.a *.gcno *.gcda *.info report gcov_test

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm .clang-format
