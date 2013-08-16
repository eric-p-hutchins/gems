#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game->key_states[SDLK_a] = true;
  game->key_states[SDLK_b] = false;
  game_loop (game);
  fail_if (!game->prev_key_states[SDLK_a]);
  fail_if (game->prev_key_states[SDLK_b]);
  game_destroy (game);
  return 0;
}
