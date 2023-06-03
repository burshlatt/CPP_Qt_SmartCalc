CC = clang++
FLAGS = -Wall -Werror -Wextra -std=c++17

main: clean
	$(CC) $(FLAGS) model/model.cc controller/controller.cc test.cc
	clear
	./a.out

clean:
	rm -rf a.out
