CC = gcc
CFLAGS = -Wall -Wextra -O2
OBJ = main.o readConfig.o constraint.o task.o

task_generator: $(OBJ)
	$(CC) $(CFLAGS) -o task_generator $(OBJ)

main.o: main.c readConfig.h
	$(CC) $(CFLAGS) -c main.c

readConfig.o: readConfig.c readConfig.h
	$(CC) $(CFLAGS) -c readConfig.c

constraint.o: constraint.c constraint.h
	$(CC) $(CFLAGS) -c constraint.c

task.o: task.c task.h
	$(CC) $(CFLAGS) -c task.c

clean:
	rm -f *.o task_generator


