OBJS	= timestamp.o secure.o permissions.o filedata.o file.o f.o argparse.o
SOURCE = src/timestamp.c src/secure.c src/permissions.c src/filedata.c src/file.c src/f.c src/argparse.c
HEADER = include/argparse.h include/file.h include/filedata.h include/permissions.h include/secure.h include/timestamp.h
OUT = 
CC = gcc
FLAGS = -g -c
LFLAGS = 

all: $(OBJS)
	$(CC) -g $(OBJS) $(LFLAGS) -o f

timestamp.o: src/timestamp.c
	$(CC) $(FLAGS) src/timestamp.c

secure.o: src/secure.c
	$(CC) $(FLAGS) src/secure.c 

permissions.o: src/permissions.c
	$(CC) $(FLAGS) src/permissions.c 

filedata.o: src/filedata.c
	$(CC) $(FLAGS) src/filedata.c 

file.o: src/file.c
	$(CC) $(FLAGS) src/file.c 

f.o: src/f.c
	$(CC) $(FLAGS) src/f.c 

argparse.o: src/argparse.c
	$(CC) $(FLAGS) src/argparse.c 

clean:
	rm -f $(OBJS) $(OUT)
