COMPILER = gcc -std=c99 -Wall -g
EXEC_PROG = b+tree
BINARIES = $(EXEC_PROG)

SOURCES := $(shell find -name '*.c')

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(COMPILER) -c -o $@ $< -w

all: $(EXEC_PROG)
	@echo TP1 Build Completed

$(EXEC_PROG): $(OBJECTS)
	$(COMPILER) -o $(EXEC_PROG) $(OBJECTS)

run:
	./$(EXEC_PROG)

.PHONY : clean 
clean:
	rm $(BINARIES) $(OBJECTS)

clean-files:
	rm saida/*