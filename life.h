#define EMPTY_CHAR '.'
#define FULL_CHAR  '*'

typedef unsigned char cell;

typedef struct {
	/* these are indexed by the cell's living neighbour count; if they are
	 * true, the cell is alive next turn; otherwise it is not. */

	/* this array is used for cells that were dead at the end of the last turn */
	unsigned char B[9];
	/* and this one for cells that were alive */
	unsigned char S[9];
} ruleset;

typedef struct {
	int w, h, turn;
	ruleset rules;
	cell *board;
} game;

typedef unsigned char colour;
typedef struct {
	enum { PPM } format;
	int cell_width,
		cell_height,
		grid_thickness,
		/* set to 0 not to use different colours for different cell values */
		colour_count,
		/* for making the grid lines dashed; put to 1 for solid lines */
		grid_skip;
	colour on_colour,
		   off_colour,
		   grid_colour,
		   *state_colours;
} graphics_format;

void new_game(game *g, int w, int h, ruleset rules);
void read_board(game *g, FILE *in);
void draw_current_state(game *g, graphics_format fmt, FILE *out);
void print_current_state(game *g, FILE *out);
void next_turn(game *g);
void destroy_game(game *g);

extern ruleset RULES_LIFE;

