CC = g++
CC_FLAGS = -std=c++11 -O3 -Wall
#CC_FLAGS += -D INTERACTIVE
#CC_FLAGS += -pg

OBJS = func_generation.o least_square_mc.o market_parameters.o matrix2d.o park_miller_rand.o path_generation.o rand_generator.o vanilla_option.o test_least_square.o
all: pricer.x

pricer.x: $(OBJS) 
	$(CC) $(CC_FLAGS) $^ -o $@

%.o: %.cc
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm *.o *.h.gch *.x
