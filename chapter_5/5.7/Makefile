CC = gcc
CFLAG = -Wall -g
SRC = scatter_gather.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = scatter_gather

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
