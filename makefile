PROJ_NAME=ballAlg

C_SOURCE=$(wildcard *.c)

H_SOURCE=$(wildcard *.h)

OBJ=$(C_SOURCE:.c=.o)

CC=gcc

CC_FLAGS=-c			\
         -W			\
         -Wall		\
         -ansi		\
         -O3		\
         -pedantic

all: $(PROJ_NAME)
 
$(PROJ_NAME): main.o heap.o
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)
	
main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

heap.o: ./lib/heap_modules/Heap.c ./lib/heap_modules/Heap.h
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~