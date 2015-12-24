# Initial Makefile - please consider improving

# Makefile for compiling the automatic grading utility called Auto

SRC = Auto.java List.java
CLASSES = *.class
MAINCLASS = Auto.class
JARFILE = Auto
MAN = Manifest
DIR = pa1
CFLAGS = -Xlint
COMP = javac
LFLAGS = cvfm
LINK = jar

$(JARFILE) : $(CLASSES)
	echo "Main-class: $(MAINCLASS)" > $(MAN)
	$(LINK) $(LFLAGS) $(JARFILE) $(MAN) $^
	rm $(MAN)
	chmod +x $(JARFILE)

$(CLASSES) : $(SRC)
	$(COMP) $(FLAGS) $^

#Email students their grades
-m : $(JARFILE)
	$^ -m $(DIR)

#Compile all grades in an organized fashion
-g : $(JARFILE)
	$^ -g $(DIR)

#Run tests on all programs
-t : $(JARFILE)
	$^ -t $(DIR)

#Actual grading utility where you type n, p etc. to move through a list.
#Specifics of operation not yet confirmed
-r : $(JARFILE)
	$^ -r $(DIR)

clean :
	rm -f $(CLASSES)

spotless : clean
	rm -f $(JARFILE)

.PHONY: clean spotless

