 .PHONY: clean build all

# compilation settings
CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g
LDLIBS= -lm # for log operation

# directory paths
INCLUDE_DIR = ./
SRC_DIR = ./
OBJ_DIR = ./

# file lists
CFILES = hashmap.c main.c calc.c search_retrieval.c training.h
OBJS = hashmap.o main.o calc.o search_retrieval.o training.o

# binary
BIN = main

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDLIBS)

clean:
	rm -f $(OBJS) $(BIN) *~
