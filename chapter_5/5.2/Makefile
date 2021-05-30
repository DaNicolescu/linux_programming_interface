CC = gcc
CFLAG = -Wall -g
SRC = append_data.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = append_data

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
