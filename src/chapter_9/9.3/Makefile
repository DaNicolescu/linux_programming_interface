CC = gcc
CFLAG = -Wall -g
SRC = initgroups.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = initgroups

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
