CC=gcc
CFLAGS=-c -Wall -I. -fpic -g -fbounds-check

OBJS=src/main.o

%.o:	src/%.c include/%.h
	$(CC) $(CFLAGS) $< -o $@

piton:	$(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) piton