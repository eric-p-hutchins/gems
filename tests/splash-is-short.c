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
  bool splash_is_short = false;
  int i;
  for (i = 0; i < 50 * 30; ++i)
    {
      game_loop (game);
      if (game->state != SPLASH_STATE)
        {
          splash_is_short = true;
          break;
        }
    }
  game_destroy (game);
  return splash_is_short?0:1;
}
