#--------------------------------
# Makefile for IntegerStack ADT
# ------------------------------
ASSIGNMENT     = lab3
CLIENT         = IntegerStackTest
ADT            = IntegerStack
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT_SOURCE     = $(ADT).c
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full
SUBMIT         = submit cse015-pt.f19 $(ASSIGNMENT)
FILES          = README Makefile $(ADT_SOURCE) $(SOURCE) $(ADT_HEADER)
$(CLIENT) : $(OBJECT) $(ADT_OBJECT) 
	$(LINK) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT_HEADER) 
	$(COMPILE) $(SOURCE)
$(ADT_OBJECT) : $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT_OBJECT) 

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)

submit: $(FILES)
	$(SUBMIT) $(FILES)
check:
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/$(ASSIGNMENT)/jgrauper
format:
	clang-format -i $(ADT_SOURCE)
