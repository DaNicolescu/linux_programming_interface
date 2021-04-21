CC = gcc
CFLAG = -Wall -g
SRC = my_tee.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = my_tee

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
