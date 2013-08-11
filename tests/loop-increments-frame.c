#include <stdlib.h>

#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  int frame = game->frame;
  game_loop (game);
  if (game->frame != frame + 1)
    {
      exit (1);
    }
  game_destroy (game);
  return 0;
}
