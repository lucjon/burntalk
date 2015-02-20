#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "life.h"

/* standard Life is B3/S23 */
ruleset RULES_LIFE = {
	.B = {0, 0, 0, 1, 0, 0, 0, 0, 0},
	.S = {0, 0, 1, 1, 0, 0, 0, 0, 0}
};

#define COLOUR_TABLE_ENTRIES 4
char colour_table[] = {
	'.', '*', '#', '!'
};

void new_game(game *g, int w, int h, ruleset rules) {
	g->w = w;
	g->h = h;
	g->turn = 0;
	g->rules = rules;
	g->board = malloc(sizeof(cell) * (w * h));
}

void next_turn(game *g) {
	int x, y, neighbours;
	size_t size;
	cell new_board[g->w * g->h];

	size = sizeof(cell) * (g->w * g->h);
	memcpy(new_board, g->board, size);

/* gives 1 if (r, s) is inside the board and non-zero; otherwise 0 */
#define CELL(r, s) (!!(((r) >= 0 && (s) >= 0 && (r) < g->w && (s) < g->h) ? g->board[(r) + (s) * g->w] : 0))
	for (y = 0; y < g->h; y++) {
		for (x = 0; x < g->w; x++) {
			/* count the living neighbours */
			neighbours =  CELL(x - 1, y - 1) + CELL(x, y - 1) + CELL(x + 1, y - 1)
						+ CELL(x - 1, y)     +        0       + CELL(x + 1, y)
						+ CELL(x - 1, y + 1) + CELL(x, y + 1) + CELL(x + 1, y + 1);

			new_board[y * g->w + x] = (CELL(x, y) ? g->rules.S : g->rules.B)[neighbours];
		}
	}
#undef CELL

	memcpy(g->board, new_board, size);
	g->turn++;
}

void draw_current_state(game *g, graphics_format fmt, FILE *out) {
	int col, line, x, y, w, h;
	colour value;
	cell state;

	w = g->w * (fmt.cell_width + fmt.grid_thickness) - fmt.grid_thickness;
	h = g->h * (fmt.cell_height + fmt.grid_thickness) - fmt.grid_thickness;

	assert(fmt.format == PPM);
	fprintf(out, "P2\n%d %d\n%d\n", w, h, 255);

	/* for each row on the board, */
	for (line = 0; line < g->h; line++) {
		/* first, draw the next (cell_height) rows of the image*/
		for (y = 0; y < fmt.cell_height; y++) {
			/* this means iterating over every cell in that row */
			for (col = 0; col < g->w; col++) {
				/* fill in (cell_width) solid pixels corresponding to the value
				 * of the cell */
				for (x = 0; x < fmt.cell_width; x++) {
					state = g->board[g->w * line + col];
					if (!state)
						value = fmt.off_colour;
					else if (fmt.colour_count > 0 && state < fmt.colour_count)
						value = fmt.state_colours[state];
					else
						value = fmt.on_colour;

					fprintf(out, "%d ", value);
				}

				/* if we're not on the last column, fill in solid pixels for
				 * the vertical grid */
				if (col != g->w - 1) {
					for (x = 0; x < fmt.grid_thickness; x++) {
						value = (y % fmt.grid_skip == 0) ? fmt.grid_colour : fmt.off_colour;
						fprintf(out, "%d ", value);
					}
				}
			}

			fprintf(out, "\n");
		}

		/* if we're not on the last line, draw a whole (thickness) lines of
		 * solid grid_colour for the horizontal grid */
		if (line != g->h - 1) {
			for (y = 0; y < fmt.grid_thickness; y++) {
				for (x = 0; x < w; x++) {
					value = (x % fmt.grid_skip == 0) ? fmt.grid_colour : fmt.off_colour;
					fprintf(out, "%d ", value);
				}
				fprintf(out, "\n");
			}
		}
	}
}

void read_board(game *g, FILE *in) {
	int x, y, i, succeeded;
	char c;

	for (y = 0; y < g->h; y++) {
		for (x = 0; x < g->w; x++) {
			c = getc(in);
			succeeded = 0;

			for (i = 0; i < COLOUR_TABLE_ENTRIES; i++) {
				if (colour_table[i] == c) {
					g->board[y * g->w + x] = i;
					succeeded = 1;
					break;
				}
			}

			if (!succeeded)
				g->board[y * g->w + x] = c != EMPTY_CHAR;
		}
		assert(getc(in) == '\n');
	}
}

void print_current_state(game *g, FILE *out) {
	int x, y;
	cell state;

	for (y = 0; y < g->h; y++) {
		for (x = 0; x < g->w; x++) {
			state = g->board[y * g->w + x];

			if (state < COLOUR_TABLE_ENTRIES)
				putc(colour_table[state], out);
			else
				putc(state ? FULL_CHAR : EMPTY_CHAR, out);
		}
		putc('\n', out);
	}
}

void destroy_game(game *g) {
	free(g->board);
}
