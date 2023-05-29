CC = gcc
CFLAGS = -Wall -g -Wpedantic
LDFLAGS = -g
LBLIBS = 
SRC = quicker/stack.c stack.test.c
OBJ = $(SRC:.c=.o)
EXEC = stack_test

all: $(EXEC)
	rm -rf $(OBJ) 

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) 