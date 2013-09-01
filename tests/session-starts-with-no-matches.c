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
  for (i = 0; i < game->n_cols; ++i)
    {
      for (j = 0; j < game->n_rows - 3; ++j)
        {
          fail_if (gem_type (game, i, j) == gem_type (game, i, j + 1)
                   && gem_type (game, i, j) == gem_type (game, i, j + 2));
        }
    }

  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols - 3; ++j)
        {
          fail_if (gem_type (game, j, i) == gem_type (game, j + 1, i)
                   && gem_type (game, j, i) == gem_type (game, j + 2, i));
        }
    }

  game_destroy (game);
  return 0;
}
