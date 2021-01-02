# Usage
# make 			# Compile all binaries
# make clean	# Clean all objects
# make mrproper	# Clean all binaries and objects

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
LDFLAGS=
EXEC=test.exe
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)

# remove commands
RM_COM=
RM_FLAGS=
OBJS_RM=
GCHS_RM=
ifeq ($(OS),Windows_NT)
	RM_COM+=del
	OBJS_RM+=src\*.o
	GCHS_RM+=src\*.gch
else
	RM_COM+=rm
	RM_FLAGS+=-rf
	OBJS_RM+=src/*.o
	GCHS_RM+=src/*.gch
endif


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	$(RM_COM) $(RM_FLAGS) $(OBJS_RM)
	$(RM_COM) $(RM_FLAGS) $(GCHS_RM)

mrproper: clean
	rm -rf $(EXEC)
