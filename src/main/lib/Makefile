CC = g++
CC_FLAGS = -Wall -g


all: parkmiller.x

parkmiller.x: park_miller_rand.o test_park_miller_rand.o 
	$(CC)  park_miller_rand.o test_park_miller_rand.o -o parkmiller.x

park_miller_rand.o: park_miller_rand.cc
	$(CC) $(CC_FLAGS) -c park_miller_rand.cc -o park_miller_rand.o

test_park_miller_rand.o: test_park_miller_rand.cc
	$(CC) $(CC_FLAGS) -c test_park_miller_rand.cc -o test_park_miller_rand.o
