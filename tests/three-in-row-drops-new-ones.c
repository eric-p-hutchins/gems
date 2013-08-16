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
  int j;
  int k;
  for (i = 0; i < m; ++i)
    {
      for (j = 0; j < n; ++j)
        {
          game->board[i][j] = j * m + i;
        }
    }

  int **old_board = (int**)malloc (sizeof (int*) * m);
  for (i = 0; i < m; ++i)
    {
      old_board[i] = (int*)malloc (sizeof (int) * n);
      for (j = 0; j < n; ++j)
        {
          old_board[i][j] = game->board[i][j];
        }
    }

  game->n_gem_types = 1000000;

  game->board[0][n-1] = 999999;
  game->board[1][n-1] = 999999;
  game->board[2][n-1] = 999999;

  game->board[m-1][n-1] = 999999;
  game->board[m-2][n-1] = 999999;
  game->board[m-3][n-1] = 999999;

  bool old_ones_dropped_1 = false;
  bool old_ones_dropped_2 = false;
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
      if (!old_ones_dropped_1)
        {
          old_ones_dropped_1 = true;
          for (k = 0; k < 3; ++k)
            {
              for (j = 1; j < n; ++j)
                {
                  if (game->board[k][j] != old_board[k][j-1])
                    {
                      old_ones_dropped_1 = false;
                    }
                }
            }
        }
      if (!old_ones_dropped_2)
        {
          old_ones_dropped_2 = true;
          for (k = m-3; k < m; ++k)
            {
              for (j = 1; j < n; ++j)
                {
                  if (game->board[k][j] != old_board[k][j-1])
                    {
                      old_ones_dropped_1 = false;
                    }
                }
            }
        }
      if (old_ones_dropped_1 && old_ones_dropped_2)
        {
          break;
        }
    }
  fail_if (!old_ones_dropped_1 || !old_ones_dropped_2);
  bool new_gems_1 = false;
  bool new_gems_2 = false;
  for (i = 0; i < 50 * 2; ++i)
    {
      if (game->board[0][0] != old_board[0][0]
          || game->board[1][0] != old_board[1][0]
          || game->board[2][0] != old_board[2][0])
        {
          new_gems_1 = true;
        }
      if (game->board[m-3][0] != old_board[m-3][0]
          || game->board[m-2][0] != old_board[m-2][0]
          || game->board[m-1][0] != old_board[m-1][0])
        {
          new_gems_2 = true;
        }
      if (new_gems_1 && new_gems_2)
        {
          break;
        }
      game_loop (game);
    }
  fail_if (!new_gems_1 || !new_gems_2);

  game_destroy (game);
  return 0;
}
