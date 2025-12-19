CC = gcc
CFLAG = -Wall -g
SRC = atomic_append.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = atomic_append

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
