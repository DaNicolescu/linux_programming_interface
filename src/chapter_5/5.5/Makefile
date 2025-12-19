CC = gcc
CFLAG = -Wall -g
SRC = shared_fd.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = shared_fd

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
