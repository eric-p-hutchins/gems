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
  setup_board_every_gem_different (game);

  int **old_board = copy_board (game);

  game->n_gem_types = 1000000;

  game->board[0][n-1] = 999999;
  game->board[1][n-1] = 999999;
  game->board[2][n-1] = 999999;
  game->board[3][n-1] = 999999;

  bool old_ones_dropped = false;
  int special_index = -1;
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
      if (game->board[1][n-1] == 1999999)
        {
          special_index = 1;
        }
      if (game->board[2][n-1] == 1999999)
        {
          special_index = 2;
        }
      if (!old_ones_dropped)
        {
          old_ones_dropped = true;
          for (k = 0; k < 4; ++k)
            {
              for (j = 1; j < n; ++j)
                {
                  if (k != special_index && game->board[k][j] != old_board[k][j-1])
                    {
                      old_ones_dropped = false;
                    }
                }
            }
        }
      if (old_ones_dropped)
        {
          break;
        }
    }
  fail_if (!old_ones_dropped);
  bool new_gems = false;
  for (i = 0; i < 50 * 2; ++i)
    {
      if (game->board[0][0] != old_board[0][0]
          || game->board[3][0] != old_board[3][0]
          || (special_index != 1 && game->board[1][0] != old_board[1][0])
          || (special_index != 2 && game->board[2][0] != old_board[2][0]))
        {
          new_gems = true;
        }
      if (new_gems)
        {
          break;
        }
      game_loop (game);
    }
  fail_if (!new_gems);

  game_destroy (game);
  return 0;
}
