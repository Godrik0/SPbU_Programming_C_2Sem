CC = gcc
CFLAGS = 
OBJ = main.o divider_tree.o divider_tree_print.o binary_tree.o
TARGET = project.exe

release: CFLAGS += -O3
release: all

debug: CFLAGS += -Wall -g -O0
debug: all

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $@ -lm

$(OBJ):%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm *.o *.exe
