#include <stdio.h>
#include <stdlib.h>
#include "life.h"

int main(int argc, char *argv[]) {
	int w, h;
	game g;

	if (argc < 3) {
		printf( "usage: %s W H\n"
				"takes a board configuration on standard input\n"
				"produces a configuration of the next turn on standard output\n",
				argv[0]);
		return 1;
	}

	w = atoi(argv[1]);
	h = atoi(argv[2]);

	new_game(&g, w, h, RULES_LIFE);
	read_board(&g, stdin);
	next_turn(&g);
	print_current_state(&g, stdout);
	destroy_game(&g);

	return 0;
}
