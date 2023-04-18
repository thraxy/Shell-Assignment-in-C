# Makefile for assignment 3

# the compiler to use
CC = gcc

# the target executable file
TARGET = shell

# the default target
all: $(TARGET)

# the target dependencies and commands to build it
$(TARGET): 176002999_shell_assignment3.c
	$(CC) -o $(TARGET) 176002999_shell_assignment3.c

# the command to clean the directory
clean:

# remove the target executable file
	rm -f $(TARGET)

