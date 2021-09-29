CC = gcc 

TARGET = roap

CFLAGS = -Wall -std=c11 -O3

all:
		$(CC) $(CFLAGS) -o $(TARGET) 

clear:
		rm $(TARGET)