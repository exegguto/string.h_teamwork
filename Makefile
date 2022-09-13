CC=gcc
DIRECTORY=pwd
CFLAGS=-std=c11 -Wall -Werror -Wextra
TC_FLAGS=
LEAK_CHECK=
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CC += -D LINUX -g
	TC_FLAGS += -lcheck -lsubunit -lm -lrt -lpthread
	LEAK_CHECK +=CK_FORK=no valgrind --trace-children=yes --track-fds=yes --leak-check=yes --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_log.txt ./test.out
endif
ifeq ($(UNAME_S),Darwin)
    CC += -D OSX
	TC_FLAGS += $(shell pkg-config --cflags check) $(shell pkg-config --libs check)
	LEAK_CHECK +=CK_FORK=no leaks -atExit -- ./test.out
endif

#-wall лучше снять перед вертером

FLAG1=-I src
FLAG2=-c

default: all

all: clean s21_string.a test

test: s21_string.a
	$(CC) test.c s21_string.a -o test.out $(TC_FLAGS)
	./test.out

s21_string.a: s21_string.o
	ar rcs s21_string.a s21_string.o
	ranlib s21_string.a

s21_string.o: s21_string.c
	$(CC) $(FLAG1) $(CFLAGS) $(FLAG2) s21_string.c -o s21_string.o

clean:
	rm -rf  *.a *.o *.out *.txt *.info *.gcno *.gcda report

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c
	python3 cpplint.py --extension=c *.c *.h
	$(LEAK_CHECK)

gcov_report:
	$(CC) --coverage test.c s21_string.c -o test.out $(TC_FLAGS)
	./test.out
	lcov -t "test.out" -o test.info -c -d .
	genhtml -o report test.info
