CC = gcc 

TARGET = roap

CFLAGS = -Wall -std=c99 -O3

all:
		$(CC) $(CFLAGS) -o $(TARGET) RoaP_main.c RoaP_fase1.c RoaP_fase2.c RoaP_grafo.c RoaP_heap.c RoaP_DFS_tabela_fase2.c RoaP_DFS_lista_fase1.c

clear:
		rm $(TARGET)