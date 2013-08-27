#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game_start (game);
  setup_board_every_gem_different (game);

  int **old_board = copy_board (game);

  int m = game->n_rows;
  int n = game->n_cols;

  replace_gem (game, 2, 2, 999999);
  replace_gem (game, 3, 2, 1999999);
  replace_gem (game, 4, 2, 999999);

  int i;
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  for (i = 0; i < m; ++i)
    {
      fail_if (game->board[3][i] == old_board[3][i]);
    }
  for (i = 0; i < n; ++i)
    {
      if (i == 3) continue;
      fail_if (game->board[i][1] != old_board[i][0]);
      fail_if (game->board[i][0] == old_board[i][0]);
    }

  setup_board_every_gem_different (game);

  old_board = copy_board (game);

  replace_gem (game, 2, 2, 999999);
  replace_gem (game, 2, 3, 1999999);
  replace_gem (game, 2, 4, 999999);

  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }
  for (i = 0; i < m; ++i)
    {
      fail_if (game->board[2][i] == old_board[2][i]);
    }
  for (i = 0; i < n; ++i)
    {
      if (i == 2) continue;
      fail_if (game->board[i][1] != old_board[i][0]);
      fail_if (game->board[i][0] == old_board[i][0]);
    }

  game_destroy (game);
  return 0;
}
