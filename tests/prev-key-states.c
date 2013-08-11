#include <stdlib.h>

#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  game->key_states[SDLK_a] = true;
  game->key_states[SDLK_b] = false;
  game_loop (game);
  if (!game->prev_key_states[SDLK_a])
    {
      exit (1);
    }
  if (game->prev_key_states[SDLK_b])
    {
      exit (1);
    }
  game_destroy (game);
  return 0;
}
