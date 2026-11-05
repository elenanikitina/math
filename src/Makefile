CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -I.
OBJ = s21_abs.o s21_ceil.o s21_floor.o s21_exp.o s21_fabs.o s21_sqrt.o s21_utils.o s21_log.o s21_fmod.o s21_sin.o s21_cos.o s21_tan.o s21_asin.o s21_acos.o s21_atan.o s21_pow.o 

TEST_SRC = test/test_abs.c test/test_ceil.c test/test_floor.c test/test_exp.c test/test_fabs.c test/test_sqrt.c test/test_main.c test/test_log.c test/test_fmod.c test/test_sin.c test/test_cos.c test/test_tan.c test/test_asin.c test/test_acos.c test/test_atan.c test/test_pow.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_EXE = test/test_exp

LDFLAGS = -lcheck -lm -pthread -lsubunit
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage

all: s21_math.a

s21_math.a: $(OBJ)
	ar rcs s21_math.a $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

test: CFLAGS += $(GCOV_FLAGS)
test: $(TEST_OBJ) $(OBJ)
	$(CC) $(GCOV_FLAGS) $(TEST_OBJ) $(OBJ) -o $(TEST_EXE) $(LDFLAGS)
	./$(TEST_EXE)

gcov_report: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
#	open coverage_report/index.html


clean:
	rm -rf $(TEST_EXE) program *.o test/*.o test/*.gcda test/*.gcno test/*.info *.gch *.out coverage_report *.gcda *.gcno *.info
 
.PHONY: all clean test gcov_report