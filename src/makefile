GCC=gcc -Wall -Werror -Wextra
FLAGS=--std=c++17 -lstdc++ -lm -lgtest -lgcov

all: clean gcov_report

s21_matrix_oop.a: clean
	$(GCC) --coverage -c s21_matrix_oop.cpp
	ar rc s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

test: s21_matrix_oop.a
	$(GCC) tests.cpp s21_matrix_oop.a $(FLAGS) -g -o test
	./test

gcov_report: test
	lcov -t test -o rep.info -c -d ./
	genhtml -o report rep.info
	open report/index.html

valgrind: test
	docker build -t image_matrix .
	docker run --name container_matrix image_matrix

clang:
	clang-format -i --style=google *.h *.cpp

check_clang:
	clang-format -n --style=google *.h *.cpp

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM
	
clear:
	docker rm container_matrix
	docker rmi image_matrix