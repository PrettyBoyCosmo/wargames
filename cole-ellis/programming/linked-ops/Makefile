CC=gcc
BINS=linked-ops.c ll.c

all: $(BINS)
		$(CC) -o linked-ops $(BINS)
		./linked-ops

poc: poc.c
	$(CC) -o poc poc.c ll.c
	./poc

clean:
		rm -rf linked-ops
