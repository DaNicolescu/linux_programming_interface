CC = gcc
CFLAG = -Wall -g
SRC = my_cp.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = my_cp

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
