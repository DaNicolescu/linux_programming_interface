CC = gcc
CFLAG = -Wall -g
SRC = malloc_free_and_sbrk.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = malloc_free_and_sbrk

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
