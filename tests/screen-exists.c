#include <stdlib.h>

#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  if (game->screen == NULL)
    {
      exit (1);
    }
  if (game->screen->w != 320)
    {
      exit (1);
    }
  if (game->screen->h != 240)
    {
      exit (1);
    }
  game_destroy (game);
  return 0;
}
