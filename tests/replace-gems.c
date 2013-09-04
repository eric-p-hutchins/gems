#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game_start (game);

  int i;
  int j;
  int k;
  setup_board_every_gem_different (game);

  int n = game->n_rows;
  int m = game->n_cols;

  int **old_board = copy_board (game);
  replace_gems (game, "");

  for (i = 0; i < m; ++i)
    {
      for (j = 0; j < n; ++j)
        {
          fail_if (game->board[i][j] != old_board[i][j]);
        }
    }

  setup_board_every_gem_different (game);
  old_board = copy_board (game);
  replace_gems (game, "\n\
");

  for (i = 0; i < m; ++i)
    {
      for (j = 0; j < n; ++j)
        {
          fail_if (game->board[i][j] != old_board[i][j]);
        }
    }

  setup_board_every_gem_different (game);
  old_board = copy_board (game);
  replace_gems (game, "\n\
 ");

  for (i = 0; i < m; ++i)
    {
      for (j = 0; j < n; ++j)
        {
          fail_if (game->board[i][j] != old_board[i][j]);
        }
    }

  setup_board_every_gem_different (game);
  old_board = copy_board (game);
  replace_gems (game, "\n\
 . ");

  fail_if (game->board[1][0] != 999999);
  for (i = 0; i < m; ++i)
    {
      for (j = 0; j < n; ++j)
        {
          if (j == 0 && i == 1) continue;
          fail_if (game->board[i][j] != old_board[i][j]);
        }
    }

  setup_board_every_gem_different (game);
  old_board = copy_board (game);
  replace_gems (game, "\n\
   \n\
   \n\
  .");

  fail_if (game->board[2][2] != 999999);
  for (i = 0; i < m; ++i)
    {
      for (j = 0; j < n; ++j)
        {
          if (j == 2 && i == 2) continue;
          fail_if (game->board[i][j] != old_board[i][j]);
        }
    }

  setup_board_every_gem_different (game);
  old_board = copy_board (game);
  replace_gems (game, "\n\
@=$\n\
%&!\n\
?+.");

  fail_if (game->board[0][0] != 999991);
  fail_if (game->board[1][0] != 999992);
  fail_if (game->board[2][0] != 999993);
  fail_if (game->board[0][1] != 999994);
  fail_if (game->board[1][1] != 999995);
  fail_if (game->board[2][1] != 999996);
  fail_if (game->board[0][2] != 999997);
  fail_if (game->board[1][2] != 999998);
  fail_if (game->board[2][2] != 999999);
  for (i = 3; i < m; ++i)
    {
      for (j = 3; j < n; ++j)
        {
          fail_if (game->board[i][j] != old_board[i][j]);
        }
    }

  replace_gems (game, "\n\
@=O\n\
%O!\n\
O+.");

  fail_if (game->board[0][0] != 999991);
  fail_if (game->board[1][0] != 999992);
  fail_if (game->board[2][0] != -1);
  fail_if (game->board[0][1] != 999994);
  fail_if (game->board[1][1] != -1);
  fail_if (game->board[2][1] != 999996);
  fail_if (game->board[0][2] != -1);
  fail_if (game->board[1][2] != 999998);
  fail_if (game->board[2][2] != 999999);
  for (i = 3; i < m; ++i)
    {
      for (j = 3; j < n; ++j)
        {
          fail_if (game->board[i][j] != old_board[i][j]);
        }
    }

  game_destroy (game);
  return 0;
}
