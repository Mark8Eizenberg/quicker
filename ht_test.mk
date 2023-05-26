CC = gcc
CFLAGS = -Wall -g -Wpedantic
LDFLAGS = -g
LBLIBS = 
SRC = quicker/hash_table.c ht_test.c
OBJ = $(SRC:.c=.o)
EXEC = list_test

all: $(EXEC)
	rm -rf $(OBJ) 

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) 