#include <stdlib.h>

#include "game.h"

void
session_start (game_t *game)
{
  srand (time (NULL));
  game->state = SESSION_STATE;
  game->n_rows = 8;
  game->n_cols = 8;
  game->n_gem_types = 4;
  game->board = (int**)malloc (sizeof (int*) * game->n_cols);
  int i;
  for (i = 0; i < game->n_cols; ++i)
    {
      game->board[i] = (int*)malloc (sizeof (int) * game->n_rows);
    }
  int match_list[2];
  int j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          match_list[0] = match_list[1] = -1;
          if (j >= 2 && game->board[j-2][i] == game->board[j-1][i])
            {
              match_list[0] = game->board[j-2][i];
            }
          if (i >= 2 && game->board[j][i-2] == game->board[j][i-1])
            {
              match_list[1] = game->board[j][i-2];
            }
          game->board[j][i] = rand () % game->n_gem_types;
          while (game->board[j][i] == match_list[0]
                 || game->board[j][i] == match_list[1])
            {
              ++(game->board[j][i]);
            }
        }
    }
}

void
session_loop (game_t *game)
{
  int i;
  int j;
  int k;
  int l;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (i >= 3
              && game->board[j][i] == game->board[j][i-1]
              && game->board[j][i] == game->board[j][i-2]
              && game->board[j][i] == game->board[j][i-3])
            {
              game->board[j][i-1] = game->board[j][i]
                + game->n_gem_types;
              game->board[j][i] = -1;
              game->board[j][i-2] = -1;
              game->board[j][i-3] = -1;
            }
          else if (j < game->n_cols - 3
              && game->board[j][i] == game->board[j+1][i]
              && game->board[j][i] == game->board[j+2][i]
              && game->board[j][i] == game->board[j+3][i])
            {
              game->board[j+1][i] = game->board[j][i]
                + game->n_gem_types;
              game->board[j][i] = -1;
              game->board[j+2][i] = -1;
              game->board[j+3][i] = -1;
            }
        }
    }
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (i >= 2
              && game->board[j][i] == game->board[j][i-1]
              && game->board[j][i] == game->board[j][i-2])
            {
              game->board[j][i] = -1;
              game->board[j][i-1] = -1;
              game->board[j][i-2] = -1;
            }
          else if (j < game->n_cols - 2
              && game->board[j][i] == game->board[j+1][i]
              && game->board[j][i] == game->board[j+2][i])
            {
              game->board[j][i] = -1;
              game->board[j+1][i] = -1;
              game->board[j+2][i] = -1;
            }
        }
    }
  for (i = 0; i < game->n_cols; ++i)
    {
      for (j = game->n_rows - 1; j >= 0; --j)
        {
          if (game->board[i][j] == -1)
            {
              for (k = j; k > 0; --k)
                {
                  game->board[i][k] = game->board[i][k-1];
                }
              game->board[i][0] = rand () % game->n_gem_types;
              break;
            }
        }
    }
}
