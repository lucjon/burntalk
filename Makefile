CFLAGS := -O3 -Wall -Wextra
OBJECTS := game.o
BINS := life drawlife

all: $(BINS)

game.o: game.c
	$(CC) -c $(CFLAGS) -o $@ $^

%: %.c $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS) $(BINS)

.PHONY: all
