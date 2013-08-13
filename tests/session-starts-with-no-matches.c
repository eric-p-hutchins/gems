#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main ()
{
  game_t *game = game_create ();
  game_start (game);

  int i;
  int j;
  for (i = 0; i < game->n_cols; ++i)
    {
      for (j = 0; j < game->n_rows - 3; ++j)
        {
          fail_if (game->board[i][j] == game->board[i][j+1]
                   && game->board[i][j] == game->board[i][j+2]);
        }
    }

  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols - 3; ++j)
        {
          fail_if (game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i]);
        }
    }

  game_destroy (game);
  return 0;
}
