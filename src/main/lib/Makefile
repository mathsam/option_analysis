CC = g++
CC_FLAGS = -Wall -g

EXEC = parkmiller.x
SRCS = park_miller_rand.cc test_park_miller_rand.cc
OBJS = $(SRCS:.c=.o)

all: $(EXEC) 

$(EXEC): $(OBJS) 
	$(CC) -o $(EXEC) $(OBJS)
%.o: %.cc
	$(CC) -c $(CC_FLAGS) &< -o $@ 
