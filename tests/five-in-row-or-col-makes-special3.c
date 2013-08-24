#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game_start (game);

  int n = game->n_rows;
  int m = game->n_cols;

  int i;

  game->n_gem_types = 1000000;

  // #@$%&*#    ###%###
  // #.....# -> #@$.&*#
  // #######    #######

  setup_board_every_gem_different (game);
  int **old_board = copy_board (game);

  replace_gem (game, 1, 1, 999999);
  replace_gem (game, 2, 1, 999999);
  replace_gem (game, 3, 1, 999999);
  replace_gem (game, 4, 1, 999999);
  replace_gem (game, 5, 1, 999999);

  bool old_ones_dropped = false;
  bool special_created = false;
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
      if (game->board[3][1] == 3999999)
        {
          special_created = true;
        }
      if (!old_ones_dropped)
        {
          if (game->board[1][1] == old_board[1][0]
              && game->board[2][1] == old_board[2][0]
              && game->board[3][0] == old_board[3][0]
              && game->board[4][1] == old_board[4][0]
              && game->board[5][1] == old_board[5][0]
              && game->board[1][0] != old_board[1][0]
              && game->board[2][0] != old_board[2][0]
              && game->board[4][0] != old_board[4][0]
              && game->board[5][0] != old_board[5][0])
            {
              old_ones_dropped = true;
            }
        }
      if (old_ones_dropped && special_created)
        {
          break;
        }
    }
  fail_if (!old_ones_dropped || !special_created);

  // #@#    ###
  // #$#    ###
  // #%#    ###
  // #&#    ###
  // #.# -> #@#
  // #.#    #$#
  // #.#    #%#
  // #.#    #&#
  // #.#    #.#
  // ###    ###

  setup_board_every_gem_different (game);
  old_board = copy_board (game);

  replace_gem (game, 0, n-1, 999999);
  replace_gem (game, 0, n-2, 999999);
  replace_gem (game, 0, n-3, 999999);
  replace_gem (game, 0, n-4, 999999);
  replace_gem (game, 0, n-5, 999999);

  old_ones_dropped = false;
  special_created = false;
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
      if (game->board[0][n-1] == 3999999)
        {
          special_created = true;
        }
      if (!old_ones_dropped)
        {
	  old_ones_dropped = true;
	  int j;
	  for (j = n-2; j >= 0; --j)
	    {
	      if (game->board[0][j] == old_board[0][j])
		{
		  old_ones_dropped = false;
		  break;
		}
	    }
        }
      if (old_ones_dropped && special_created)
        {
          break;
        }
    }
  fail_if (!old_ones_dropped || !special_created);

  game_destroy (game);
  return 0;
}
