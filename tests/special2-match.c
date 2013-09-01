#include "test.h"

#include "game.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game_start (game);
  setup_board_every_gem_different (game);
  replace_gems (game, "\n\
@=$\n\
   \n\
.#.\n\
   ");
  game_loop_n (game, 100);
  fail_if (game->board[0][0] == TESTGEM_AT);
  fail_if (game->board[1][0] == TESTGEM_EQUALS);
  fail_if (game->board[2][0] == TESTGEM_DOLLAR);
  fail_if (game->board[0][3] != TESTGEM_AT);
  fail_if (game->board[1][3] != TESTGEM_EQUALS);
  fail_if (game->board[2][3] != TESTGEM_DOLLAR);

  game_destroy (game);

  return 0;
}
