CC = gcc
CFLAGS = -Wall -g
INCLUDE_DIR = ./include

SRC_DIR = ./src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

TARGET_LIB = libcstring.a
TARGET_TEST = test

all: $(TARGET_LIB) $(TARGET_TEST)

$(TARGET_LIB): $(OBJ)
	ar rcs $@ $^

$(TARGET_TEST): $(TARGET_LIB) test.c
	$(CC) $(CFLAGS) -o $@ test.c -I$(INCLUDE_DIR) -L. -lcstring

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

clean:
	rm -f $(OBJ) $(TARGET_LIB) $(TARGET_TEST)
