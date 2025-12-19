CC = gcc
CFLAG = -Wall -g
SRC = env.c
OBJS = $(SRC:.c=.o)
LIBS =
TARGET = env

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
