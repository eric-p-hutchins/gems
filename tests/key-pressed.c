#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game->prev_key_states[SDLK_a] = false;
  game->prev_key_states[SDLK_b] = false;
  game->prev_key_states[SDLK_c] = true;
  game->prev_key_states[SDLK_d] = true;
  game->key_states[SDLK_a] = false;
  game->key_states[SDLK_b] = true;
  game->key_states[SDLK_c] = false;
  game->key_states[SDLK_d] = true;
  fail_if (game_key_pressed (game, SDLK_a));
  fail_if (!game_key_pressed (game, SDLK_b));
  fail_if (game_key_pressed (game, SDLK_c));
  fail_if (game_key_pressed (game, SDLK_d));
  game_destroy (game);
  return 0;
}
