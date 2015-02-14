#include <stdio.h>
#include <stdlib.h>
#include "life.h"

int main(int argc, char *argv[]) {
	int w, h;
	game g;

	if (argc < 3) {
		printf( "usage: %s W H\n"
				"takes a board configuration on standard input\n"
				"produces a board image on standard output\n",
				argv[0]);
		return 1;
	}

	w = atoi(argv[1]);
	h = atoi(argv[2]);

	new_game(&g, w, h, RULES_LIFE);
	read_board(&g, stdin);
	draw_current_state(&g, (graphics_format) {PPM, 32, 32, 2, 2, 0, 255, 128}, stdout);
	destroy_game(&g);

	return 0;
}
