CC = g++
CC_FLAGS = -Wall -g


all: parkmiller.x path_gen.x

parkmiller.x: park_miller_rand.o test_park_miller_rand.o rand_generator.o
	$(CC) $^ -o $@

path_gen.x: test_path_generation.o rand_generator.o park_miller_rand.o market_parameters.o path_generation.o
	$(CC) $^ -o $@

%.o: %.cc
	$(CC) $(CC_FLAGS) -c $< -o $@
