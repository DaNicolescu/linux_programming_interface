CC = gcc
CFLAG = -Wall -g
SRC = dup.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = dup

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
