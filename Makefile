CFLAGS := -O3 -Wall -Wextra
OBJECTS := game.o
BINS := life drawlife

all: $(BINS) talk

talk:
	$(MAKE) -C talk

game.o: game.c
	$(CC) -c $(CFLAGS) -o $@ $^

%: %.c $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS) $(BINS)
	$(MAKE) -C talk clean

.PHONY: all talk
