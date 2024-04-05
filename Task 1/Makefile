CC = gcc
CFLAGS = -Wall
OBJ = array.o
TARGET = array.exe

release: CFLAGS += -O3
release: all

debug: CFLAGS += -g -O0
debug: all

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ):%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm *.o *.exe