# Compiler
CC = gcc
# File EXTENSION
EXTENSION = .c
# Compiler flags
CFLAGS = -lm
#############################################################
#		Don't edit below this line
#############################################################
SRC = $(wildcard *$(EXTENSION))
main: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f main *~
