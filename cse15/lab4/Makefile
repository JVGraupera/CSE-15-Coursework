ASSIGNMENT = lab4
EXEBIN = ArithmeticOperations
SOURCES = $(EXEBIN).c
OBJECTS = $(EXEBIN).o
FLAGS = -std=c99 -Wall
FILES = $(SOURCES) Makefile README
SUBMIT = submit cse015-pt.f19 $(ASSIGNMENT)
$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)
$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)
clean :
	rm -f $(EXEBIN) $(OBJECTS)
submit: $(FILES)
	$(SUBMIT) $(FILES)
format:
	clang-format -i $(SOURCES)
check:
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/$(ASSIGNMENT)/jgrauper
memcheck:
	valgrind --leak-check=full $(EXEBIN) testIn
