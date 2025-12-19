CC = gcc
CFLAG = -Wall -g
SRC = long_jmp_after_return.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = long_jmp_after_return

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
