#include <stdlib.h>

#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  if (game->state != SPLASH_STATE)
    {
      exit (1);
    }
  game_destroy (game);
  return 0;
}
