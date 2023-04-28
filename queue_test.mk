CC = gcc
CFLAGS = -Wall -g -Wpedantic
LDFLAGS = -g
LBLIBS = 
SRC = quicker/queue.c queue_test.c
OBJ = $(SRC:.c=.o)
EXEC = queue_test

all: $(EXEC)
	rm -rf $(OBJ) 

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) 