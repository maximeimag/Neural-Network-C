# Usage
# make 			# Compile all binaries
# make clean	# Clean all binaries and objects

# Compiler and flags
CC = gcc
LINKERFLAGS = -lm

# Sources and binaries
SRCS := $(wildcard src/*.c)
OBJFILES := $(CFILES:.c=.o)
OUT = main.exe

# Compiler tasks
%.o: %.c
	$(CC) -c -o $@ $^

$(OUT): $(OBJFILES)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)
