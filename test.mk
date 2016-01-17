# Makefile for tests

test : default
	$(INST) lab1

error : default
	$(INST) swagger

extern : default
	$(INST) cmps012a-pt.w16 lab1

.PHONY : test error extern
