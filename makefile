CC = gcc 

TARGET = roap

CFLAGS = -Wall -std=c99 -O3

all:
		$(CC) $(CFLAGS) -o $(TARGET) Roap_main.c

clear:
		rm $(TARGET)