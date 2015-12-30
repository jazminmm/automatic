# Initial Makefile - please consider improving

# Makefile for compiling the automatic grading utility called Auto

SRC = Auto.c List.c
DEP = List.h Extra.h
OBJ = Auto.o List.o
EXE = Auto
EFLAGS = valgrind
DIR = pa1
CFLAGS = -c -Wall -Werror -Wextra -std=c99
COMP = gcc
LFLAGS = -o -lm
LINK = gcc

#compile the executable
$(EXE) : $(OBJ)
	$(LINK) $(LFLAGS) $@ $(MAN) $^
	#chmod +x $@

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

.PHONY: clean spotless

