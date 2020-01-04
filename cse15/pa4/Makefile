#------------------------------------------------------------------------------
#Makefile for any client of any two ADTs in C
#------------------------------------------------------------------------------
ASSIGNMENT	= pa4
CLIENT		= Simulation
QUEUECLIENT     = IntegerQueueTest
ADT1            = IntegerQueue
ADT2            = Job
SOURCE          = $(CLIENT).c
OBJECT          = $(CLIENT).o
CLIENTSOURCE	= $(QUEUECLIENT).c
CLIENTOBJECT	= $(QUEUECLIENT).o
ADT1_SOURCE     = $(ADT1).c
ADT1_OBJECT     = $(ADT1).o
ADT1_HEADER     = $(ADT1).h
ADT2_SOURCE     = $(ADT2).c
ADT2_OBJECT     = $(ADT2).o
ADT2_HEADER     = $(ADT2).h
COMPILE         = gcc -c -std=c99 -Wall
LINK            = gcc -o
REMOVE          = rm -f
SUBMIT          = submit cse015-pt.f19 $(ASSIGNMENT)
FILES           = README Makefile $(ADT1_SOURCE) $(SOURCE) $(ADT1_HEADER) $(ADT2_SOURCE) $(ADT2_HEADER) $(CLIENTSOURCE)
MEMCHECK        = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) 

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)
format:
	clang-format -i $(ADT1_SOURCE) $(SOURCE) $(ADT2_SOURCE) $(CLIENTSOURCE)
linktest:
	$(LINK) $(QUEUECLIENT) $(CLIENTOBJECT) $(ADT1_OBJECT)

compiletest:
	$(COMPILE) $(CLIENTSOURCE)

cleantest:
	$(REMOVE) $(QUEUECLIENT) $(CLIENTOBJECT) $(ADT1_OBJECT)
clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) 

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT) testIn

submit: $(FILES)
	$(SUBMIT) $(FILES)

check:
	ls  /afs/cats.ucsc.edu/class/cse015-pt.f19/$(ASSIGNMENT)/jgrauper
