FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
FILE := test1.txt
FILE2 := test2.txt
all: s21_cat tests

s21_cat: Makefile s21_cat.h s21_cat.c 
	gcc $(FLAGS) s21_cat.c -o s21_cat

check:
	clang-format -style=Google -n *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -f s21_cat

tests:
	@bash -c 'diff -w <(./s21_cat $(FILE)) <(cat $(FILE))'
	@bash -c 'diff -w <(./s21_cat -s $(FILE)) <(cat -s $(FILE))'
	@bash -c 'diff -w <(./s21_cat -b $(FILE)) <(cat -b $(FILE))'
	@bash -c 'diff -w <(./s21_cat -n $(FILE)) <(cat -n $(FILE))'
	@bash -c 'diff -w <(./s21_cat -t $(FILE)) <(cat -t $(FILE))'
	@bash -c 'diff -w <(./s21_cat -e $(FILE)) <(cat -e $(FILE))'
	@bash -c 'diff -w <(./s21_cat $(FILE) $(FILE2)) <(cat $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat -s $(FILE) $(FILE2)) <(cat -s $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat -b $(FILE) $(FILE2)) <(cat -b $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat -n $(FILE) $(FILE2)) <(cat -n $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat -t $(FILE) $(FILE2)) <(cat -t $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat -e $(FILE) $(FILE2)) <(cat -e $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat --number $(FILE) $(FILE2)) <(cat --number $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat --number-nonblank $(FILE) $(FILE2)) <(cat --number-nonblank $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat --squeeze-blank $(FILE) $(FILE2)) <(cat --squeeze-blank $(FILE) $(FILE2))'
	@bash -c 'diff -w <(./s21_cat --number $(FILE)) <(cat --number $(FILE))'
	@bash -c 'diff -w <(./s21_cat --number-nonblank $(FILE)) <(cat --number-nonblank $(FILE))'
	@bash -c 'diff -w <(./s21_cat --squeeze-blank $(FILE)) <(cat --squeeze-blank $(FILE))'
