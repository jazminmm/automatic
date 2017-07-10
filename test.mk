# Makefile for tests

test : default
	./$(INST) pa1
	make spotless

listtest : List.o ListTest.o
	$(LINK) $(LFLAGS) ListTest $^
	./ListTest
	make spotless
	rm -f ListTest ListTest.o

error : default
	$(INST) swagger

extern : default
	$(INST) cmps012a-pt.w16 lab1

.PHONY : test error extern
