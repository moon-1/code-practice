scheduler: myscheduler.o Queue.o
	gcc -lm -o scheduler myscheduler.o Queue.o
myscheduler.o : myscheduler.c Queue.c Queue.h
	gcc -c myscheduler.c
