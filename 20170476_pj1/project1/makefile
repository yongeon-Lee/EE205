# makefile
CC = g++

all: student_manage_system

clobber: clean
	rm -f core

# remove all object(.o) and executable binary files
clean:
	rm -f student_manage_system
	rm -f *.o

# make executable binary file
student.o: student.h student.cpp
	$(CC) -c student.cpp

main.o: student.h main.cpp
	$(CC) -c main.cpp

student_manage_system: student.o main.o
	$(CC) student.o main.o -o student_manage_system


