#include <stdlib.h>

#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  if (game->frame != 0)
    {
      exit (1);
    }
  game_destroy (game);
  return 0;
}
