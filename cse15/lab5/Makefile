#------------------------------------------------------------------------------
# Makefile for any C program
#------------------------------------------------------------------------------

ASSIGNMENT    = lab5
PROGRAM_NAME = SortStrings
FLAGS        = -std=c99 -Wall
SOURCE       = $(PROGRAM_NAME).c
OBJECT       = $(PROGRAM_NAME).o
EXEBIN       = $(PROGRAM_NAME)
SUBMIT       = submit cse015-pt.f19 $(ASSIGNMENT)
FILES        = README Makefile $(SOURCE)

$(EXEBIN) : $(OBJECT)
	gcc -o $(EXEBIN) $(OBJECT)

$(OBJECT) : $(SOURCE)
	gcc -c $(FLAGS) $(SOURCE)

clean :
	rm $(EXEBIN) $(OBJECT)

memcheck : $(EXEBIN)
	valgrind --leak-check=full $(EXEBIN) in myout
submit: $(FILES)
	$(SUBMIT) $(FILES)
format:
	clang-format -i $(SOURCE)
check:
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/$(ASSIGNMENT)/jgrauper
