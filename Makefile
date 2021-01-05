# Usage
# make 			# Compile all binaries
# make clean	# Clean all objects
# make mrproper	# Clean all binaries and objects
# make run 		# Complie all binaries and run final executable

CC=gcc
CFLAGS= -g -W -Wall -ansi -pedantic -std=c99
LDFLAGS=
DEBUGGER=gdb
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

compile: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	$(RM_COM) $(RM_FLAGS) $(OBJS_RM)
	$(RM_COM) $(RM_FLAGS) $(GCHS_RM)

mrproper: clean
	$(RM_COM) $(RM_FLAGS) $(EXEC)

recompile: mrproper compile

run: recompile
	$(EXEC)

debug: recompile
	$(DEBUGGER) $(EXEC)
