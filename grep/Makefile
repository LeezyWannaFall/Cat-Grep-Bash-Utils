FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
FILE := test1.txt
FILE_ALL := *.txt
all: s21_grep tests

s21_grep: Makefile s21_grep.h s21_grep.c 
	gcc $(FLAGS) s21_grep.c -o s21_grep

check:
	clang-format -style=Google -n *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -f s21_grep

tests:
	@bash -c 'diff -w <(./s21_grep -e test $(FILE)) <(grep -e test $(FILE))'
	@bash -c 'diff -w <(./s21_grep -i test $(FILE)) <(grep -i test $(FILE))'
	@bash -c 'diff -w <(./s21_grep -v test $(FILE)) <(grep -v test $(FILE))'
	@bash -c 'diff -w <(./s21_grep -c test $(FILE)) <(grep -c test $(FILE))'
	@bash -c 'diff -w <(./s21_grep -l test $(FILE)) <(grep -l test $(FILE))'
	@bash -c 'diff -w <(./s21_grep -n test $(FILE)) <(grep -n test $(FILE))'
	@bash -c 'diff -w <(./s21_grep -h test $(FILE)) <(grep -h test $(FILE))'
	@bash -c 'diff -w <(./s21_grep -s test $(FILE)) <(grep -s test $(FILE))'
	@bash -c 'diff -w <(./s21_grep -e test $(FILE_ALL)) <(grep -e test $(FILE_ALL))'
	@bash -c 'diff -w <(./s21_grep -i test $(FILE_ALL)) <(grep -i test $(FILE_ALL))'
	@bash -c 'diff -w <(./s21_grep -v test $(FILE_ALL)) <(grep -v test $(FILE_ALL))'
	@bash -c 'diff -w <(./s21_grep -c test $(FILE_ALL)) <(grep -c test $(FILE_ALL))'
	@bash -c 'diff -w <(./s21_grep -l test $(FILE_ALL)) <(grep -l test $(FILE_ALL))'
	@bash -c 'diff -w <(./s21_grep -n test $(FILE_ALL)) <(grep -n test $(FILE_ALL))'
	@bash -c 'diff -w <(./s21_grep -h test $(FILE_ALL)) <(grep -h test $(FILE_ALL))'
	@bash -c 'diff -w <(./s21_grep -s test $(FILE_ALL)) <(grep -s test $(FILE_ALL))'

