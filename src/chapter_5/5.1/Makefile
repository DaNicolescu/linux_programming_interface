CC = gcc
CFLAG = -Wall -g
SRC = large_file.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = large_file

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
