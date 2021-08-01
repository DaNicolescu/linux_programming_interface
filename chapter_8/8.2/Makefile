CC = gcc
CFLAG = -Wall -g
SRC = getpwnam.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = getpwnam

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
