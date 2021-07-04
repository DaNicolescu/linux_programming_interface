CC = gcc
CFLAG = -Wall -g
SRC = login.c
OBJS = $(SRC:.c=.o)
LIBS = -lcrypt
TARGET = login

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
