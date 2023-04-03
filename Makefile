.PHONY: all build static install uninstall rebuild dist test gcov_report clean
CC=gcc
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c11
FLAGS_TEST_LIBS = -lcheck -lm -lpthread

SRC=backend_calc.c

NAME=backend_calc.a
OBJ=$(patsubst %.c, %.o, $(SRC))
OS = $(shell uname)

all: build static

build:
	cd Rabotaet && $(CC) $(CFLAGS) -c $(SRC)

static:
	cd Rabotaet && ar rc backend_calc.a $(OBJ)
	cd Rabotaet && ranlib backend_calc.a

test: clean 
	cd Rabotaet && gcc  backend_calc.c test.c  -o test -lcheck
	cd Rabotaet && ./test

gcov_report: all
	cd Rabotaet && $(CC) $(CFLAGS) --coverage test.c $(SRC) $(NAME) $(FLAGS_TEST_LIBS) -o gcov_test
	cd Rabotaet && chmod +x *
	cd Rabotaet && ./gcov_test
	cd Rabotaet && lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	cd Rabotaet && genhtml -o report/ gcov_test.info
	cd Rabotaet && open ./report/index.html


install:
	make clean
	mkdir build
	cd Rabotaet && qmake && make && make clean && rm Makefile && cd ../ && mv Rabotaet/Rabotaet.app build

uninstall:
	rm -rf build*

dvi:
	open README.txt

dist: install
	rm -rf Dist_SmartCalc/
	mkdir Dist_SmartCalc/
	mkdir Dist_SmartCalc/src
	mv ./build/Rabotaet.app Dist_SmartCalc/src/
	tar cvzf Dist_SmartCalc.tgz Dist_SmartCalc/
	rm -rf Dist_SmartCalc/
	rmdir build

clean:
	cd Rabotaet && rm -rf *.a && rm -rf *.o  && rm -rf *.dSYM && rm -rf *.out && rm -rf $(EXECUTABLE) && rm -rf gcov_report && rm -rf report && rm -rf CPPLINT.cfg && rm -rf *.gcda 
	cd Rabotaet && rm -rf *.gcno && rm -rf *.info && rm -rf test && rm -rf Dist_SmartCalc && rm -rf *tgz && rm -rf build && rm -rf SC_test && rm -rf gcov_test && rm -rf .qmake.stash

rebuild: clean all
	
style:
	cd Rabotaet && clang-format -style=Google -n *.c *.h *.cpp

