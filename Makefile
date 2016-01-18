# Initial Makefile - please consider improving

# Makefile for compiling the automatic grading utility called Auto

SRC = Auto.c Extra.c List.c Stack.c Table.c
DEP = $(SRC:.c=.h)
OBJ = $(SRC:.c=.o)
EXE = Auto
INST = ../$(EXE)
EFLAGS = valgrind --leak-check=full --show-leak-kinds=all
#DIR = pa1
CFLAGS = -c -Wall -Wno-format-extra-args -std=c99 #-Werror #-Wextra 
COMP = gcc
LFLAGS = -o
ELFLAGS = -lm
LINK = gcc

default : install spotless

install : $(EXE)
	cp $< $(INST)

#compile the executable
$(EXE) : $(OBJ)
	$(LINK) $(LFLAGS) $@ $(MAN) $^ $(ELFLAGS)

#compile the object files
%.o : %.c $(DEP)
	$(COMP) $(CFLAGS) $<

#Email students their grades
-m : $(EXE)
	$(EFLAGS) $^ -m $(DIR)

#Compile all grades in an organized fashion
-g : $(EXE)
	$(EFLAGS) $^ -g $(DIR)

#Run tests on all programs
-t : $(EXE)
	$(EFLAGS) $^ -t $(DIR)

#Actual grading utility where you type n, p etc. to move through a list.
#Specifics of operation not yet confirmed
-r : $(EXE)
	$(EFLAGS) $^ -r $(DIR)

clean :
	rm -f $(OBJ)

spotless : clean
	rm -f $(EXE)

.PHONY: default install clean spotless -m -g -t -r

include git.mk
include test.mk
