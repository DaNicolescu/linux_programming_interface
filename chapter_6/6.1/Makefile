CC = gcc
CFLAG = -Wall -g
SRC = mem_segments.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = mem_segments

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
