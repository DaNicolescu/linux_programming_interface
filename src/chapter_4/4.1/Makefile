CC = gcc
CFLAGS = -Wall -g
SRC = my_tee.c
OBJS = $(SRC:.c=.o)
LIBS =
OUTDIR = out
TARGET = $(OUTDIR)/my_tee

build: $(OUTDIR) $(TARGET)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(TARGET): $(OBJS) | $(OUTDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	-rm -f *.o core *.core $(TARGET)
 
