CC=gcc
CFLAGS=-std=c99 -pipe -pedantic-errors -Wall -Werror -Wextra -Wcast-align -O2
LDFLAGS=-lm
C_FILES=solver.c
BINARY=./solver

solver: $(C_FILES)
	$(CC) $(C_FILES) $(CFLAGS) $(LDFLAGS) -o $(BINARY)

.PHONY: clean
clean:
	@rm -v $(BINARY) || echo "couldn't remove binary. not found."
