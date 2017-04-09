CC = gcc
CFLAGS = -pedantic -Wall -g -ansi
COOBJ = CompareSchedulers.o LinkedList.o
RROBJ = RRScheduler.o LinkedList.o
SJFOBJ = SJFScheduler.o LinkedList.o
EXEC = CompareSchedulers RRScheduler SJFScheduler

all : $(EXEC)

CompareSchedulers : $(COOBJ)
	$(CC) -o CompareSchedulers $(COOBJ) $(CFLAGS) -pthread

RRScheduler : $(RROBJ)
	$(CC) $(CFLAGS) -o RRScheduler $(RROBJ)

SJFScheduler : $(SJFOBJ)
	$(CC) $(CFLAGS) -o SJFScheduler $(SJFOBJ)

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c

CompareSchedulers.o : CompareSchedulers.c CompareSchedulers.h LinkedList.h
	$(CC) -c CompareSchedulers.c $(CFLAGS) -pthread

RRScheduler.o : RRScheduler.c RRScheduler.h LinkedList.h
	$(CC) $(CFLAGS) -c RRScheduler.c

SJFScheduler.o : SJFScheduler.c SJFScheduler.h LinkedList.h
	$(CC) $(CFLAGS) -c SJFScheduler.c

clean :
	rm -f $(EXEC) $(RROBJ) $(SJFOBJ)
