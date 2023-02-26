# Makefile - Quad-Tree Mapper
# Name: Jude Thaddeau Data
# GitHub: https://github.com/jtd-117
# -------------------------------------------------------------------------- #

# DEFINITIONS:
CC = gcc
CFLAGS = -Wall -g

EXE3 = mode1
EXE4 = mode2

SRC = src/main.c src/cmp.c src/data.c src/coordinates.c src/dynamic-array.c src/quad-tree.c src/sll.c
OBJ = $(SRC:.c=.o)

# -------------------------------------------------------------------------- #

# COMPILATIONS:

compile: $(EXE3) $(EXE4)

$(EXE3): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE3) $(OBJ)

$(EXE4): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE4) $(OBJ)

main.o: main.c cmp.h data.h coordinates.h dynamic-array.h quad-tree.h sll.h

cmp.o: cmp.c cmp.h

data.o: cmp.h data.c data.h

coordinates.o: cmp.h coordinates.c coordinates.h

quad-tree.o: data.h array.h quad-tree.h quad-tree.c

sll.o: data.h sll.h sll.c

dynamic-array.o: data.h dynamic-array.c dynamic-array.h

# -------------------------------------------------------------------------- #

# PROGRAM EXECUTIONS - MODE 1
m1-d1:
	./dict3 3 tests/dataset_1.csv output.out 144.969 -37.7975 144.971 -37.7955 < tests/test1.s3.in > output.stdout.out

m1-d2:
	./dict3 3 tests/dataset_1.csv output.out 144.969 -37.7965 144.971 -37.795 < tests/test2.s3.in > output.stdout.out

m1-d3:
	./dict3 3 tests/dataset_1.csv output.out 144.969 -37.7965 144.9725 -37.7945 < tests/test3.s3.in > output.stdout.out

m1-d4:
	./dict3 3 tests/dataset_1.csv output.out 144.969 -37.7965 144.976 -37.7925 < tests/test4.s3.in > output.stdout.out

m1-d5:
	./dict3 3 tests/dataset_2.csv output.out 144.968 -37.797 144.977 -37.79 < tests/test5.s3.in > output.stdout.out

m1-d6:
	./dict3 3 tests/dataset_20.csv output.out 144.952 -37.81 144.978 -37.79 < tests/test6.s3.in > output.stdout.out

m1-d7:
	./dict3 3 tests/dataset_100.csv output.out 144.9538 -37.812 144.9792 -37.784 < tests/test7.s3.in > output.stdout.out

m1-d8:
	./dict3 3 tests/dataset_1000.csv output.out 144.9375 -37.8750 145.0000 -37.6875 < tests/test8.s3.in > output.stdout.out

# -------------------------------------------------------------------------- #

# PROGRAM EXECUTIONS - MODE 2

m2-d1:
	./dict4 4 tests/dataset_1.csv output.out 144.969 -37.7975 144.971 -37.7955 < tests/test9.s4.in > output.stdout.out

m2-d2:
	./dict4 4 tests/dataset_1.csv output.out 144.969 -37.7965 144.9725 -37.7945 < tests/test10.s4.in > output.stdout.out

m2-d3:
	./dict4 4 tests/dataset_2.csv output.out 144.968 -37.797 144.977 -37.79 < tests/test11.s4.in > output.stdout.out

m2-d4:
	./dict4 4 tests/dataset_20.csv output.out 144.952 -37.81 144.978 -37.79 < tests/test12.s4.in > output.stdout.out

m2-d5:
	./dict4 4 tests/dataset_100.csv output.out 144.9375 -37.8750 145.0000 -37.6875 < tests/test13.s4.in > output.stdout.out

m2-d6:
	./dict4 4 tests/dataset_1000.csv output.out 144.9375 -37.8750 145.0000 -37.6875 < tests/test14.s4.in > output.stdout.out

# -------------------------------------------------------------------------- #

# VALGRIND DEBUGGING - MODE 1

v-m1-d1:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict3 3 tests/dataset_1.csv output.out 144.969 -37.7975 144.971 -37.7955 < tests/test1.s3.in > output.stdout.out

v-m1-d2:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict3 3 tests/dataset_1.csv output.out 144.969 -37.7965 144.971 -37.795 < tests/test2.s3.in > output.stdout.out

v-m1-d3:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict3 3 tests/dataset_1.csv output.out 144.969 -37.7965 144.9725 -37.7945 < tests/test3.s3.in > output.stdout.out

v-m1-d4:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict3 3 tests/dataset_1.csv output.out 144.969 -37.7965 144.976 -37.7925 < tests/test4.s3.in > output.stdout.out

v-m1-d5:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict3 3 tests/dataset_2.csv output.out 144.968 -37.797 144.977 -37.79 < tests/test5.s3.in > output.stdout.out

v-m1-d6:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict3 3 tests/dataset_20.csv output.out 144.952 -37.81 144.978 -37.79 < tests/test6.s3.in > output.stdout.out

v-m1-d7:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict3 3 tests/dataset_100.csv output.out 144.9538 -37.812 144.9792 -37.784 < tests/test7.s3.in > output.stdout.out

v-m1-d8:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict3 3 tests/dataset_1000.csv output.out 144.9375 -37.8750 145.0000 -37.6875 < tests/test8.s3.in > output.stdout.out

# -------------------------------------------------------------------------- #

# VALGRIND DEBUGGING - MODE 2

v-m2-d1:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict4 4 tests/dataset_1.csv output.out 144.969 -37.7975 144.971 -37.7955 < tests/test9.s4.in > output.stdout.out

v-m2-d2:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict4 4 tests/dataset_1.csv output.out 144.969 -37.7965 144.9725 -37.7945 < tests/test10.s4.in > output.stdout.out

v-m2-d3:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict4 4 tests/dataset_2.csv output.out 144.968 -37.797 144.977 -37.79 < tests/test11.s4.in > output.stdout.out

v-m2-d4:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict4 4 tests/dataset_20.csv output.out 144.952 -37.81 144.978 -37.79 < tests/test12.s4.in > output.stdout.out

v-m2-d5:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict4 4 tests/dataset_100.csv output.out 144.9375 -37.8750 145.0000 -37.6875 < tests/test13.s4.in > output.stdout.out

v-m2-d6:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes -s ./dict4 4 tests/dataset_1000.csv output.out 144.9375 -37.8750 145.0000 -37.6875 < tests/test14.s4.in > output.stdout.out

# -------------------------------------------------------------------------- #

# DIFF COMMANDS - MODE 1

d-m1-d1-p1:
	diff -y output.out tests/test1.s3.out
d-m1-d1-p2:	
	diff -y output.stdout.out tests/test1.s3.stdout.out

d-m1-d2-p1:
	diff -y output.out tests/test2.s3.out
d-m1-d2-p2:
	diff -y output.stdout.out tests/test2.s3.stdout.out

d-m1-d3-p1:
	diff -y output.out tests/test3.s3.out
d-m1-d3-p2:
	diff -y output.stdout.out tests/test3.s3.stdout.out

d-m1-d4-p1:
	diff -y output.out tests/test4.s3.out
d-m1-d4-p2:
	diff -y output.stdout.out tests/test4.s3.stdout.out

d-m1-d5-p1:
	diff -y output.out tests/test5.s3.out
d-m1-d5-p2:
	diff -y output.stdout.out tests/test5.s3.stdout.out

d-m1-d6-p1:
	diff -y output.out tests/test6.s3.out
d-m1-d6-p2:
	diff -y output.stdout.out tests/test6.s3.stdout.out

d-m1-d7-p1:
	diff -y output.out tests/test7.s3.out
d-m1-d7-2:
	diff -y output.stdout.out tests/test7.s3.stdout.out

d-m1-d8-p1:
	diff -y output.out tests/test8.s3.out
d-m1-d8-p2:
	diff -y output.stdout.out tests/test8.s3.stdout.out

# -------------------------------------------------------------------------- #

# DIFF COMMANDS - MODE 2

d-m2-d1-p1:
	diff -y output.out tests/test9.s4.out
d-m2-d1-p2:
	diff -y output.stdout.out tests/test9.s4.stdout.out

d-m2-d2-p1:
	diff -y output.out tests/test10.s4.out
d-m2-d2-p2:
	diff -y output.stdout.out tests/test10.s4.stdout.out

d-m2-d3-p1:
	diff -y output.out tests/test11.s4.out
d-m2-d3-p2:
	diff -y output.stdout.out tests/test11.s4.stdout.out

d-m2-d4-p1:
	diff -y output.out tests/test12.s4.out
d-m2-d4-p2:
	diff -y output.stdout.out tests/test12.s4.stdout.out

d-m2-d5-p1:
	diff -y output.out tests/test13.s4.out
d-m2-d5-p2:
	diff -y output.stdout.out tests/test13.s4.stdout.out

d-m2-d6-p1:
	diff -y output.out tests/test14.s4.out
d-m2-d6-p2:
	diff -y output.stdout.out tests/test14.s4.stdout.out


# -------------------------------------------------------------------------- #

# UTILITY COMMANDS:

clean1:
	rm -f $(OBJ) $(EXE3)

clean2:
	rm -f $(OBJ) $(EXE4)

clean3:
	rm -f *.out

clean: clean1 clean2 clean3